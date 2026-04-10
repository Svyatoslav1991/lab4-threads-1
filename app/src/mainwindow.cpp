#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QColor>
#include <QStatusBar>
#include <QThread>
#include <QVBoxLayout>
#include <QtConcurrent>

#include "pointswidget.h"
#include "worker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qRegisterMetaType<MyPoint>("MyPoint");

    initializeUi();
    setupPointsWidget();
    createWorkers();
    connectActions();
}

//--------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    waitForFutures();
    destroyWorkers();
    delete ui;
}

//--------------------------------------------------------------------------

//--------------------------------------------------------------------------

void MainWindow::slotQtConcurrent()
{
    if (hasRunningFutures()) {
        statusBar()->showMessage(
            QStringLiteral("Предыдущий запуск ещё не завершён."));
        return;
    }

    if (m_pointsWidget == nullptr || m_workers.isEmpty()) {
        statusBar()->showMessage(
            QStringLiteral("Нет доступной области рисования или worker-объектов."));
        return;
    }

    slotClear();
    m_x = 0;
    m_futures.clear();

    const int workerCount = m_workers.size();
    const int availableWidth = qMax(1, m_pointsWidget->width() - 20);

    constexpr int xStep = 1;
    const int totalPointsThatFit = qMax(1, availableWidth / xStep);
    const int stepsPerWorker = qMax(1, totalPointsThatFit / workerCount);

    constexpr qsizetype delayIterations = 3'000'000;

    for (Worker *worker : m_workers) {
        worker->setSteps(stepsPerWorker);
        worker->setDelayIterations(delayIterations);

        m_futures.push_back(QtConcurrent::run(worker, &Worker::doWork));
    }

    statusBar()->showMessage(
        QStringLiteral("QtConcurrent запущен: workers=%1, stepsPerWorker=%2, totalPoints≈%3")
            .arg(workerCount)
            .arg(stepsPerWorker)
            .arg(workerCount * stepsPerWorker));
}

//--------------------------------------------------------------------------

void MainWindow::slotQRunnable()
{
    statusBar()->showMessage(
        QStringLiteral("Запуск через QRunnable будет добавлен следующим шагом."));
}

//--------------------------------------------------------------------------

void MainWindow::slotClear()
{
    if (m_pointsWidget == nullptr) {
        return;
    }

    m_pointsWidget->clearPoints();
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

void MainWindow::createWorkers()
{
    const int workerCount = qMax(1, QThread::idealThreadCount());

    const QVector<QColor> colors = {
        Qt::red,
        Qt::blue,
        Qt::darkGreen,
        Qt::magenta,
        Qt::darkYellow,
        Qt::cyan,
        Qt::black,
        Qt::darkRed
    };

    constexpr int startY = 40;
    constexpr int deltaY = 25;
    constexpr int stepsCount = 400;
    constexpr qsizetype delayIterations = 20000;

    m_workers.reserve(workerCount);

    for (int index = 0; index < workerCount; ++index) {
        const int y = startY + index * deltaY;
        const QColor color = colors.at(index % colors.size());

        Worker *worker = new Worker(y,
                                    &m_x,
                                    color,
                                    stepsCount,
                                    delayIterations);

        connect(worker, &Worker::signalAddPoint,
                this, &MainWindow::slotAddPoint,
                Qt::QueuedConnection);

        m_workers.push_back(worker);
    }
}

//--------------------------------------------------------------------------

void MainWindow::destroyWorkers()
{
    qDeleteAll(m_workers);
    m_workers.clear();
}

//--------------------------------------------------------------------------

void MainWindow::waitForFutures()
{
    for (QFuture<void> &future : m_futures) {
        future.waitForFinished();
    }

    m_futures.clear();
}

//--------------------------------------------------------------------------

bool MainWindow::hasRunningFutures() const
{
    for (const QFuture<void> &future : m_futures) {
        if (!future.isFinished()) {
            return true;
        }
    }

    return false;
}
