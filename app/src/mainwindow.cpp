#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QStatusBar>
#include <QVBoxLayout>

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
    connectActions();
    test();
}

//--------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

//--------------------------------------------------------------------------

void MainWindow::slotQtConcurrent()
{
    statusBar()->showMessage(
                QStringLiteral("Запуск через QtConcurrent будет добавлен следующим шагом."));
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
    m_x = 0;

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
    statusBar()->showMessage(QStringLiteral("Приложение готово к работе"));
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

void MainWindow::test()
{
    slotClear();

    constexpr int startX = 10;
    constexpr int workerY = 80;
    constexpr int stepsCount = 400;
    constexpr qsizetype delayIterations = 20000;
    const QColor workerColor = Qt::red;

    m_x = startX;

    Worker worker(workerY,
                  &m_x,
                  workerColor,
                  stepsCount,
                  delayIterations,
                  this);

    connect(&worker, &Worker::signalAddPoint,
            this, &MainWindow::slotAddPoint);

    worker.doWork();

    statusBar()->showMessage(
                QStringLiteral("Тестовый прогон Worker завершён, точек: %1")
                .arg(m_pointsWidget != nullptr ? m_pointsWidget->pointCount() : 0));
}
