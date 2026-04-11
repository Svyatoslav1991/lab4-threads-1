#include "mypoint.h"

#include <QPainter>
#include <QPen>

namespace
{
constexpr int kLineWidth = 2;
constexpr int kLineHeight = 20;
}

//--------------------------------------------------------------------------

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
    pen.setWidth(kLineWidth);
    painter.setPen(pen);

    painter.drawLine(m_point.x(),
                     m_point.y(),
                     m_point.x(),
                     m_point.y() + kLineHeight);

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
