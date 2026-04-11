#include "pointswidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPalette>

namespace
{
constexpr int kMinimumWidth = 320;
constexpr int kMinimumHeight = 180;
}

//--------------------------------------------------------------------------

PointsWidget::PointsWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setAutoFillBackground(false);
    setMinimumSize(kMinimumWidth, kMinimumHeight);
}

//--------------------------------------------------------------------------

void PointsWidget::addPoint(const MyPoint &point)
{
    m_points.push_back(point);
    update();
}

//--------------------------------------------------------------------------

void PointsWidget::clearPoints()
{
    if (m_points.isEmpty()) {
        return;
    }

    m_points.clear();
    update();
}

//--------------------------------------------------------------------------

const QVector<MyPoint> &PointsWidget::points() const noexcept
{
    return m_points;
}

//--------------------------------------------------------------------------

int PointsWidget::pointCount() const noexcept
{
    return m_points.size();
}

//--------------------------------------------------------------------------

void PointsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);

    paintBackground(painter);
    paintPoints(painter);
}

//--------------------------------------------------------------------------

void PointsWidget::paintBackground(QPainter &painter) const
{
    painter.fillRect(rect(), palette().brush(QPalette::Window));
}

//--------------------------------------------------------------------------

void PointsWidget::paintPoints(QPainter &painter) const
{
    for (const MyPoint &point : m_points) {
        point.draw(painter);
    }
}
