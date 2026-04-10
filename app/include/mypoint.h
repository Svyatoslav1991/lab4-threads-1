#ifndef MYPOINT_H
#define MYPOINT_H

#include <QColor>
#include <QPoint>
#include <QMetaType>

class QPainter;

/**
 * @brief Лёгкий объект-значение для хранения и отрисовки цветной точки.
 *
 * @details
 * Класс инкапсулирует:
 * - координату точки;
 * - цвет точки.
 *
 * В лабораторной работе экземпляры MyPoint будут формироваться рабочими
 * потоками и передаваться в главный поток для отображения.
 */
class MyPoint
{
public:
    /**
     * @brief Создаёт точку с заданными координатой и цветом.
     * @param pt Координата точки.
     * @param color Цвет точки.
     */
    explicit MyPoint(const QPoint &pt = QPoint(), const QColor &color = Qt::black);

    /**
     * @brief Отрисовывает точку.
     *
     * @details
     * Для наглядности рисуется вертикальная линия:
     * от верхней координаты точки до нижней границы viewport'а painter.
     *
     * Метод не оставляет после себя изменённое состояние painter:
     * используется save()/restore().
     *
     * @param painter Объект рисования Qt.
     */
    void draw(QPainter &painter) const;

    /**
     * @brief Возвращает координату точки.
     */
    const QPoint &point() const noexcept;

    /**
     * @brief Возвращает цвет точки.
     */
    const QColor &color() const noexcept;

    friend bool operator==(const MyPoint &lhs, const MyPoint &rhs) noexcept
    {
        return lhs.m_point == rhs.m_point && lhs.m_color == rhs.m_color;
    }

    friend bool operator!=(const MyPoint &lhs, const MyPoint &rhs) noexcept
    {
        return !(lhs == rhs);
    }

private:
    QPoint m_point;   ///< Координата точки.
    QColor m_color;   ///< Цвет точки.
};

Q_DECLARE_METATYPE(MyPoint)

#endif // MYPOINT_H
