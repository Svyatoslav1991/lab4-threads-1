#include <QtTest/QtTest>

#include <QSignalSpy>

#include "workerslauncher.h"
#include "workersrunsettings.h"

class TestWorkersLauncher : public QObject
{
    Q_OBJECT

private slots:
    void constructor_createsWorkersAndIsInitiallyIdle();
    void launchViaQtConcurrent_emitsPointsAndFinishSignal();
    void launchViaQRunnable_emitsPointsAndFinishSignal();
    void waitForFinished_afterLaunch_stopsRunningState();
};

//--------------------------------------------------------------------------

void TestWorkersLauncher::constructor_createsWorkersAndIsInitiallyIdle()
{
    WorkersLauncher launcher;

    QVERIFY(launcher.workerCount() >= 1);
    QVERIFY(!launcher.hasRunningTasks());
}

//--------------------------------------------------------------------------

void TestWorkersLauncher::launchViaQtConcurrent_emitsPointsAndFinishSignal()
{
    qRegisterMetaType<MyPoint>("MyPoint");

    WorkersLauncher launcher;

    QSignalSpy pointSpy(&launcher, &WorkersLauncher::signalAddPoint);
    QSignalSpy finishSpy(&launcher, &WorkersLauncher::signalAllWorkersFinished);

    constexpr int startX = 20;
    constexpr int stepsPerWorker = 3;
    constexpr qsizetype delayIterations = 0;

    WorkersRunSettings settings;
    settings.startX = startX;
    settings.stepsPerWorker = stepsPerWorker;
    settings.delayIterations = delayIterations;

    launcher.prepareForRun(settings);
    launcher.launchViaQtConcurrent();

    QTRY_COMPARE(finishSpy.count(), 1);
    QCOMPARE(pointSpy.count(), launcher.workerCount() * stepsPerWorker);
    QVERIFY(!launcher.hasRunningTasks());

    launcher.waitForFinished();
}

//--------------------------------------------------------------------------

void TestWorkersLauncher::launchViaQRunnable_emitsPointsAndFinishSignal()
{
    qRegisterMetaType<MyPoint>("MyPoint");

    WorkersLauncher launcher;

    QSignalSpy pointSpy(&launcher, &WorkersLauncher::signalAddPoint);
    QSignalSpy finishSpy(&launcher, &WorkersLauncher::signalAllWorkersFinished);

    constexpr int startX = 20;
    constexpr int stepsPerWorker = 2;
    constexpr qsizetype delayIterations = 0;

    WorkersRunSettings settings;
    settings.startX = startX;
    settings.stepsPerWorker = stepsPerWorker;
    settings.delayIterations = delayIterations;

    launcher.prepareForRun(settings);
    launcher.launchViaQRunnable();

    QTRY_COMPARE(finishSpy.count(), 1);
    QCOMPARE(pointSpy.count(), launcher.workerCount() * stepsPerWorker);
    QVERIFY(!launcher.hasRunningTasks());

    launcher.waitForFinished();
}

//--------------------------------------------------------------------------

void TestWorkersLauncher::waitForFinished_afterLaunch_stopsRunningState()
{
    WorkersLauncher launcher;

    constexpr int startX = 20;
    constexpr int stepsPerWorker = 5;
    constexpr qsizetype delayIterations = 0;

    WorkersRunSettings settings;
    settings.startX = startX;
    settings.stepsPerWorker = stepsPerWorker;
    settings.delayIterations = delayIterations;

    launcher.prepareForRun(settings);
    launcher.launchViaQtConcurrent();

    launcher.waitForFinished();

    QVERIFY(!launcher.hasRunningTasks());
}

QTEST_GUILESS_MAIN(TestWorkersLauncher)
#include "test_workerslauncher.moc"
