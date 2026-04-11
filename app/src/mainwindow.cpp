#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QStatusBar>
#include <QThread>
#include <QVBoxLayout>

#include "pointswidget.h"
#include "workerslauncher.h"

namespace
{
constexpr int kStartX = 20;
constexpr int kRightPadding = 20;
constexpr int kXAdvancePerPoint = 1;
}

//--------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<MyPoint>("MyPoint");

    initializeUi();
    setupPointsWidget();
    setupWorkersLauncher();
    connectActions();
}

//--------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

//--------------------------------------------------------------------------

void MainWindow::slotQtConcurrent()
{
    startWorkers(LaunchMode::QtConcurrent);
}

//--------------------------------------------------------------------------

void MainWindow::slotQRunnable()
{
    startWorkers(LaunchMode::QRunnable);
}

//--------------------------------------------------------------------------

void MainWindow::slotClear()
{
    clearPointsView();
    statusBar()->showMessage(QStringLiteral("Область отображения очищена"));
}

//--------------------------------------------------------------------------

void MainWindow::slotAddPoint(MyPoint point)
{
    if (m_pointsWidget == nullptr) {
        return;
    }

    m_pointsWidget->addPoint(point);
}

//--------------------------------------------------------------------------

void MainWindow::slotWorkersFinished()
{
    statusBar()->showMessage(QStringLiteral("Все worker-объекты завершили работу"));
}

//--------------------------------------------------------------------------

void MainWindow::initializeUi()
{
    setWindowTitle(QStringLiteral("Потоки + worker"));
    statusBar()->showMessage(
                QStringLiteral("QThread::idealThreadCount()=%1")
                .arg(QThread::idealThreadCount()));
}

//--------------------------------------------------------------------------

void MainWindow::connectActions()
{
    connect(ui->actionQtConcurrent, &QAction::triggered,
            this, &MainWindow::slotQtConcurrent);

    connect(ui->actionQRunnable, &QAction::triggered,
            this, &MainWindow::slotQRunnable);

    connect(ui->actionClear, &QAction::triggered,
            this, &MainWindow::slotClear);
}

//--------------------------------------------------------------------------

void MainWindow::setupPointsWidget()
{
    auto *layout = new QVBoxLayout(ui->centralwidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_pointsWidget = new PointsWidget(ui->centralwidget);
    layout->addWidget(m_pointsWidget);
}

//--------------------------------------------------------------------------

void MainWindow::setupWorkersLauncher()
{
    m_workersLauncher = new WorkersLauncher(this);

    connect(m_workersLauncher, &WorkersLauncher::signalAddPoint,
            this, &MainWindow::slotAddPoint,
            Qt::QueuedConnection);

    connect(m_workersLauncher, &WorkersLauncher::signalAllWorkersFinished,
            this, &MainWindow::slotWorkersFinished,
            Qt::QueuedConnection);
}

//--------------------------------------------------------------------------

void MainWindow::startWorkers(LaunchMode mode)
{
    if (m_workersLauncher == nullptr) {
        statusBar()->showMessage(QStringLiteral("WorkersLauncher не инициализирован"));
        return;
    }

    if (m_workersLauncher->hasRunningTasks()) {
        statusBar()->showMessage(
                    QStringLiteral("Предыдущий запуск ещё не завершён."));
        return;
    }

    clearPointsView();

    const WorkersRunSettings settings = createRunSettings();
    m_workersLauncher->prepareForRun(settings);

    switch (mode) {
    case LaunchMode::QtConcurrent:
        m_workersLauncher->launchViaQtConcurrent();
        statusBar()->showMessage(
                    QStringLiteral("QtConcurrent запущен, worker-объектов: %1")
                    .arg(m_workersLauncher->workerCount()));
        break;

    case LaunchMode::QRunnable:
        m_workersLauncher->launchViaQRunnable();
        statusBar()->showMessage(
                    QStringLiteral("QRunnable запущен, worker-объектов: %1")
                    .arg(m_workersLauncher->workerCount()));
        break;
    }
}

//--------------------------------------------------------------------------

void MainWindow::clearPointsView()
{
    if (m_pointsWidget == nullptr) {
        return;
    }

    m_pointsWidget->clearPoints();
}

//--------------------------------------------------------------------------

WorkersRunSettings MainWindow::createRunSettings() const noexcept
{
    WorkersRunSettings settings;
    settings.startX = kStartX;
    settings.stepsPerWorker = calculateStepsPerWorker();
    settings.delayIterations = calculateDelayIterations();
    return settings;
}

//--------------------------------------------------------------------------

int MainWindow::calculateStepsPerWorker() const noexcept
{
    if (m_pointsWidget == nullptr ||
            m_workersLauncher == nullptr ||
            m_workersLauncher->workerCount() <= 0) {
        return 1;
    }

    const int drawableWidth =
            qMax(1, m_pointsWidget->width() - kStartX - kRightPadding);

    const int totalPointSlots =
            qMax(1, drawableWidth / kXAdvancePerPoint);

    return qMax(1, totalPointSlots / m_workersLauncher->workerCount());
}

//--------------------------------------------------------------------------

qsizetype MainWindow::calculateDelayIterations() const noexcept
{
    return 3'000'000;
}
