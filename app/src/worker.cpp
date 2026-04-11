#include "worker.h"

#include <QPoint>
#include <algorithm>

Worker::Worker(int y,
               int *sharedX,
               const QColor &color,
               int steps,
               qsizetype delayIterations,
               QObject *parent)
    : QObject(parent)
    , m_pX(sharedX)
    , m_Y(y)
    , m_color(color)
    , m_steps(std::max(0, steps))
    , m_delayIterations(std::max<qsizetype>(0, delayIterations))
{
}

//------------------------------------------------------------------------------------

int Worker::y() const noexcept
{
    return m_Y;
}

//------------------------------------------------------------------------------------

int *Worker::sharedX() const noexcept
{
    return m_pX;
}

//------------------------------------------------------------------------------------

const QColor &Worker::color() const noexcept
{
    return m_color;
}

//------------------------------------------------------------------------------------

int Worker::steps() const noexcept
{
    return m_steps;
}

//------------------------------------------------------------------------------------

qsizetype Worker::delayIterations() const noexcept
{
    return m_delayIterations;
}

//--------------------------------------------------------------------------

void Worker::setSteps(int steps) noexcept
{
    m_steps = std::max(0, steps);
}

//--------------------------------------------------------------------------

void Worker::setDelayIterations(qsizetype delayIterations) noexcept
{
    m_delayIterations = std::max<qsizetype>(0, delayIterations);
}

//--------------------------------------------------------------------------

void Worker::doWork()
{
    if (m_pX == nullptr) {
        emit endWork();
        return;
    }

    for (int step = 0; step < m_steps; ++step) {
        emit signalAddPoint(makeCurrentPoint());
        incrementSharedX();
        busyDelay();
    }

    emit endWork();
}

//--------------------------------------------------------------------------

MyPoint Worker::makeCurrentPoint() const
{
    return MyPoint(QPoint(*m_pX, m_Y), m_color);
}

//------------------------------------------------------------------------------------

void Worker::incrementSharedX() noexcept
{
    ++(*m_pX);
}

//------------------------------------------------------------------------------------

void Worker::busyDelay() const noexcept
{
    volatile int sink = 0;

    for (qsizetype i = 0; i < m_delayIterations; ++i) {
        sink += 1;
    }

    (void)sink;
}
