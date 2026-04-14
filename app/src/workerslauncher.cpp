#include "workerslauncher.h"

#include <QThread>
#include <QThreadPool>
#include <QtConcurrent>

#include "myrunnable.h"
#include "worker.h"

namespace
{
constexpr int kStartY = 40;
constexpr int kDeltaY = 35;

const QVector<QColor> kWorkerColors = {
    Qt::red,
    Qt::blue,
    Qt::darkGreen,
    Qt::magenta,
    Qt::darkYellow,
    Qt::cyan,
    Qt::black,
    Qt::darkRed
};
}

//--------------------------------------------------------------------------

WorkersLauncher::WorkersLauncher(QObject *parent)
    : QObject(parent)
{
    createDefaultWorkers();
}

//--------------------------------------------------------------------------

WorkersLauncher::~WorkersLauncher()
{
    waitForFinished();
    destroyWorkers();
}

//--------------------------------------------------------------------------

void WorkersLauncher::prepareForRun(const WorkersRunSettings &settings) noexcept
{
    m_sharedX = settings.startX;
    m_activeWorkers = m_workers.size();
    m_futures.clear();

    configureWorkers(settings);
}

//--------------------------------------------------------------------------

void WorkersLauncher::launchViaQtConcurrent()
{
    m_futures.clear();

    for (Worker *worker : m_workers) {
        m_futures.push_back(QtConcurrent::run([worker]()
        {
            if (worker != nullptr) {
                worker->doWork();
            }
        }));
    }
}

//--------------------------------------------------------------------------

void WorkersLauncher::launchViaQRunnable()
{
    for (Worker *worker : m_workers) {
        MyRunnable *runnable = new MyRunnable(worker);
        QThreadPool::globalInstance()->start(runnable);
    }
}

//--------------------------------------------------------------------------

void WorkersLauncher::waitForFinished()
{
    for (QFuture<void> &future : m_futures) {
        future.waitForFinished();
    }

    m_futures.clear();
    QThreadPool::globalInstance()->waitForDone();
    m_activeWorkers = 0;
}

//--------------------------------------------------------------------------

int WorkersLauncher::workerCount() const noexcept
{
    return m_workers.size();
}

//--------------------------------------------------------------------------

bool WorkersLauncher::hasRunningTasks() const noexcept
{
    return m_activeWorkers > 0;
}

//--------------------------------------------------------------------------

void WorkersLauncher::slotWorkerFinished()
{
    if (m_activeWorkers <= 0) {
        return;
    }

    --m_activeWorkers;

    if (m_activeWorkers == 0) {
        emit signalAllWorkersFinished();
    }
}

//--------------------------------------------------------------------------

void WorkersLauncher::createDefaultWorkers()
{
    const int workerCount = qMax(1, QThread::idealThreadCount());
    m_workers.reserve(workerCount);

    for (int index = 0; index < workerCount; ++index) {
        const int y = kStartY + index * kDeltaY;
        const QColor color = kWorkerColors.at(index % kWorkerColors.size());

        Worker *worker = new Worker(y,
                                    &m_sharedX,
                                    color,
                                    0,
                                    0);

        connectWorkerSignals(worker);
        m_workers.push_back(worker);
    }
}

//--------------------------------------------------------------------------

void WorkersLauncher::destroyWorkers()
{
    qDeleteAll(m_workers);
    m_workers.clear();
}

//--------------------------------------------------------------------------

void WorkersLauncher::connectWorkerSignals(Worker *worker)
{
    if (worker == nullptr) {
        return;
    }

    connect(worker, &Worker::signalAddPoint,
            this, &WorkersLauncher::signalAddPoint,
            Qt::QueuedConnection);

    connect(worker, &Worker::endWork,
            this, &WorkersLauncher::slotWorkerFinished,
            Qt::QueuedConnection);
}

//--------------------------------------------------------------------------

void WorkersLauncher::configureWorkers(const WorkersRunSettings &settings) noexcept
{
    for (Worker *worker : m_workers) {
        worker->setSteps(settings.stepsPerWorker);
        worker->setDelayIterations(settings.delayIterations);
    }
}
