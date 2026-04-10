#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initializeUi();
    connectActions();
}

//----------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

//----------------------------------------------------------------------------

void MainWindow::slotQtConcurrent()
{
    statusBar()->showMessage(
        QStringLiteral("Запуск через QtConcurrent будет добавлен следующим шагом."));
}

//----------------------------------------------------------------------------

void MainWindow::slotQRunnable()
{
    statusBar()->showMessage(
        QStringLiteral("Запуск через QRunnable будет добавлен следующим шагом."));
}

//----------------------------------------------------------------------------

void MainWindow::slotClear()
{
    statusBar()->showMessage(
        QStringLiteral("Очистка области отображения будет добавлена следующим шагом."));
}

//----------------------------------------------------------------------------

void MainWindow::initializeUi()
{
    setWindowTitle(QStringLiteral("Потоки + worker"));
    statusBar()->showMessage(QStringLiteral("Приложение готово к работе"));
}

//----------------------------------------------------------------------------

void MainWindow::connectActions()
{
    connect(ui->actionQtConcurrent, &QAction::triggered,
            this, &MainWindow::slotQtConcurrent);

    connect(ui->actionQRunnable, &QAction::triggered,
            this, &MainWindow::slotQRunnable);

    connect(ui->actionClear, &QAction::triggered,
            this, &MainWindow::slotClear);
}
