#include <QtTest/QtTest>

#include <QSignalSpy>
#include <QVariant>

#include "myrunnable.h"
#include "mypoint.h"
#include "worker.h"

class TestMyRunnable : public QObject
{
    Q_OBJECT

private slots:
    void constructor_enablesAutoDelete();
    void run_withValidWorker_delegatesToWorker();
    void run_withNullWorker_doesNothing();
};

//--------------------------------------------------------------------------

void TestMyRunnable::constructor_enablesAutoDelete()
{
    int sharedX = 0;
    Worker worker(10, &sharedX, Qt::red, 1, 0);

    MyRunnable runnable(&worker);

    QVERIFY(runnable.autoDelete());
}

//--------------------------------------------------------------------------

void TestMyRunnable::run_withValidWorker_delegatesToWorker()
{
    qRegisterMetaType<MyPoint>("MyPoint");

    int sharedX = 3;
    Worker worker(20, &sharedX, Qt::blue, 4, 0);

    QSignalSpy pointSpy(&worker, &Worker::signalAddPoint);
    QSignalSpy endSpy(&worker, &Worker::endWork);

    MyRunnable runnable(&worker);
    runnable.run();

    QCOMPARE(pointSpy.count(), 4);
    QCOMPARE(endSpy.count(), 1);
    QCOMPARE(sharedX, 7);

    const MyPoint firstPoint = pointSpy.at(0).at(0).value<MyPoint>();
    const MyPoint secondPoint = pointSpy.at(1).at(0).value<MyPoint>();
    const MyPoint thirdPoint = pointSpy.at(2).at(0).value<MyPoint>();
    const MyPoint fourthPoint = pointSpy.at(3).at(0).value<MyPoint>();

    QCOMPARE(firstPoint.point(), QPoint(3, 20));
    QCOMPARE(secondPoint.point(), QPoint(4, 20));
    QCOMPARE(thirdPoint.point(), QPoint(5, 20));
    QCOMPARE(fourthPoint.point(), QPoint(6, 20));

    QCOMPARE(firstPoint.color(), QColor(Qt::blue));
    QCOMPARE(secondPoint.color(), QColor(Qt::blue));
    QCOMPARE(thirdPoint.color(), QColor(Qt::blue));
    QCOMPARE(fourthPoint.color(), QColor(Qt::blue));
}

//--------------------------------------------------------------------------

void TestMyRunnable::run_withNullWorker_doesNothing()
{
    MyRunnable runnable(nullptr);

    runnable.run();

    QVERIFY(true);
}

QTEST_GUILESS_MAIN(TestMyRunnable)
#include "test_myrunnable.moc"
