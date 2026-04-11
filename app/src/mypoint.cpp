#include "mypoint.h"

#include <QBrush>
#include <QPainter>
#include <QPen>

MyPoint::MyPoint(const QPoint &pt, const QColor &color)
    : m_point(pt)
    , m_color(color)
{
}

//--------------------------------------------------------------------------

void MyPoint::draw(QPainter &painter) const
{
    painter.save();

    QPen pen(m_color);
    pen.setWidth(2);
    painter.setPen(pen);

    constexpr int lineHeight = 20;

    painter.drawLine(m_point.x(),
                     m_point.y(),
                     m_point.x(),
                     m_point.y() + lineHeight);

    painter.restore();
}

//--------------------------------------------------------------------------

const QPoint &MyPoint::point() const noexcept
{
    return m_point;
}

//--------------------------------------------------------------------------

const QColor &MyPoint::color() const noexcept
{
    return m_color;
}
