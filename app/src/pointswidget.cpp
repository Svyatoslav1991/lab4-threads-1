#include "pointswidget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPalette>

PointsWidget::PointsWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setAutoFillBackground(false);
    setMinimumSize(320, 180);
}

void PointsWidget::addPoint(const MyPoint &point)
{
    m_points.push_back(point);
    update();
}

void PointsWidget::clearPoints()
{
    if (m_points.isEmpty()) {
        return;
    }

    m_points.clear();
    update();
}

const QVector<MyPoint> &PointsWidget::points() const noexcept
{
    return m_points;
}

int PointsWidget::pointCount() const noexcept
{
    return m_points.size();
}

void PointsWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.fillRect(rect(), palette().brush(QPalette::Base));

    for (const MyPoint &point : m_points) {
        point.draw(painter);
    }
}
