#include "myrunnable.h"
#include "worker.h"


MyRunnable::MyRunnable(Worker *worker)
    : m_worker(worker)
{
    setAutoDelete(true);
}

//--------------------------------------------------------------------------

void MyRunnable::run()
{
    if (m_worker == nullptr) {
        return;
    }

    m_worker->doWork();
}
