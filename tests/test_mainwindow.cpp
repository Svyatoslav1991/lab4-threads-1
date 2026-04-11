#include <QtTest/QtTest>

#include <QAction>
#include <QMetaObject>
#include <QStatusBar>

#include "mainwindow.h"
#include "mypoint.h"
#include "pointswidget.h"
#include "workerslauncher.h"

class TestMainWindow : public QObject
{
    Q_OBJECT

private slots:
    void constructor_initializesWindowTitleStatusBarAndChildObjects();
    void slotAddPoint_addsPointToPointsWidget();
    void slotClear_removesPointsAndUpdatesStatusBar();
    void slotWorkersFinished_updatesStatusBarMessage();
    void actionClear_triggered_clearsPoints();
};

//--------------------------------------------------------------------------

void TestMainWindow::constructor_initializesWindowTitleStatusBarAndChildObjects()
{
    MainWindow window;

    QCOMPARE(window.windowTitle(), QStringLiteral("Потоки + worker"));
    QVERIFY(window.statusBar() != nullptr);
    QCOMPARE(window.statusBar()->currentMessage(),
             QStringLiteral("QThread::idealThreadCount()=%1")
                 .arg(QThread::idealThreadCount()));

    auto *pointsWidget = window.findChild<PointsWidget *>();
    QVERIFY(pointsWidget != nullptr);

    auto *workersLauncher = window.findChild<WorkersLauncher *>();
    QVERIFY(workersLauncher != nullptr);
}

//--------------------------------------------------------------------------

void TestMainWindow::slotAddPoint_addsPointToPointsWidget()
{
    qRegisterMetaType<MyPoint>("MyPoint");

    MainWindow window;
    auto *pointsWidget = window.findChild<PointsWidget *>();
    QVERIFY(pointsWidget != nullptr);

    const MyPoint point(QPoint(10, 25), Qt::red);

    const bool invoked = QMetaObject::invokeMethod(&window,
                                                   "slotAddPoint",
                                                   Q_ARG(MyPoint, point));
    QVERIFY(invoked);

    QCOMPARE(pointsWidget->pointCount(), 1);
    QCOMPARE(pointsWidget->points().size(), 1);
    QCOMPARE(pointsWidget->points().front(), point);
}

//--------------------------------------------------------------------------

void TestMainWindow::slotClear_removesPointsAndUpdatesStatusBar()
{
    qRegisterMetaType<MyPoint>("MyPoint");

    MainWindow window;
    auto *pointsWidget = window.findChild<PointsWidget *>();
    QVERIFY(pointsWidget != nullptr);

    QVERIFY(QMetaObject::invokeMethod(&window,
                                      "slotAddPoint",
                                      Q_ARG(MyPoint, MyPoint(QPoint(5, 10), Qt::blue))));
    QVERIFY(QMetaObject::invokeMethod(&window,
                                      "slotAddPoint",
                                      Q_ARG(MyPoint, MyPoint(QPoint(15, 20), Qt::green))));

    QCOMPARE(pointsWidget->pointCount(), 2);

    const bool invoked = QMetaObject::invokeMethod(&window, "slotClear");
    QVERIFY(invoked);

    QCOMPARE(pointsWidget->pointCount(), 0);
    QVERIFY(pointsWidget->points().isEmpty());
    QCOMPARE(window.statusBar()->currentMessage(),
             QStringLiteral("Область отображения очищена"));
}

//--------------------------------------------------------------------------

void TestMainWindow::slotWorkersFinished_updatesStatusBarMessage()
{
    MainWindow window;

    const bool invoked = QMetaObject::invokeMethod(&window, "slotWorkersFinished");
    QVERIFY(invoked);

    QCOMPARE(window.statusBar()->currentMessage(),
             QStringLiteral("Все worker-объекты завершили работу"));
}

//--------------------------------------------------------------------------

void TestMainWindow::actionClear_triggered_clearsPoints()
{
    qRegisterMetaType<MyPoint>("MyPoint");

    MainWindow window;
    auto *pointsWidget = window.findChild<PointsWidget *>();
    QVERIFY(pointsWidget != nullptr);

    QVERIFY(QMetaObject::invokeMethod(&window,
                                      "slotAddPoint",
                                      Q_ARG(MyPoint, MyPoint(QPoint(7, 14), Qt::magenta))));
    QCOMPARE(pointsWidget->pointCount(), 1);

    QAction *clearAction = nullptr;
    const QList<QAction *> actions = window.findChildren<QAction *>();
    for (QAction *action : actions) {
        if (action != nullptr && action->objectName() == QStringLiteral("actionClear")) {
            clearAction = action;
            break;
        }
    }

    QVERIFY(clearAction != nullptr);
    clearAction->trigger();

    QCOMPARE(pointsWidget->pointCount(), 0);
    QVERIFY(pointsWidget->points().isEmpty());
    QCOMPARE(window.statusBar()->currentMessage(),
             QStringLiteral("Область отображения очищена"));
}

QTEST_MAIN(TestMainWindow)
#include "test_mainwindow.moc"
