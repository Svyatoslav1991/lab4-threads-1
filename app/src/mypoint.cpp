#include "mypoint.h"

#include <QPainter>
#include <QPen>
#include <QRect>

MyPoint::MyPoint(const QPoint &pt, const QColor &color)
    : m_point(pt)
    , m_color(color)
{
}

//----------------------------------------------------------------------

void MyPoint::draw(QPainter &painter) const
{
    painter.save();

    QPen pen(m_color);
    pen.setWidth(1);
    painter.setPen(pen);

    const QRect viewport = painter.viewport();
    const int bottomY = viewport.bottom();

    painter.drawLine(m_point.x(), m_point.y(), m_point.x(), bottomY);

    painter.restore();
}

//----------------------------------------------------------------------

const QPoint &MyPoint::point() const noexcept
{
    return m_point;
}

//----------------------------------------------------------------------

const QColor &MyPoint::color() const noexcept
{
    return m_color;
}
