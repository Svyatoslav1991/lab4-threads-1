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

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_color));

    constexpr int pointSize = 4;
    const int halfSize = pointSize / 2;

    painter.drawEllipse(m_point.x() - halfSize,
                        m_point.y() - halfSize,
                        pointSize,
                        pointSize);

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
