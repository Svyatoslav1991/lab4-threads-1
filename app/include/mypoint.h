#ifndef MYPOINT_H
#define MYPOINT_H

#include <QColor>
#include <QMetaType>
#include <QPoint>

class QPainter;

/**
 * @brief Лёгкий объект-значение для хранения и отрисовки цветной метки.
 *
 * @details
 * Класс инкапсулирует:
 * - координату метки;
 * - её цвет.
 *
 * В лабораторной работе экземпляры MyPoint формируются рабочими
 * потоками и передаются в главный поток для отображения.
 *
 * Текущее визуальное представление метки — короткая вертикальная линия,
 * движущаяся по оси X.
 */
class MyPoint
{
public:
    /**
     * @brief Создаёт метку с заданными координатой и цветом.
     * @param pt Координата метки.
     * @param color Цвет метки.
     */
    explicit MyPoint(const QPoint &pt = QPoint(), const QColor &color = Qt::black);

    /**
     * @brief Отрисовывает метку.
     *
     * @details
     * Для наглядности рисуется короткий вертикальный отрезок
     * фиксированной длины, начинающийся в координате точки.
     *
     * Метод не оставляет после себя изменённое состояние painter:
     * используется save()/restore().
     *
     * @param painter Объект рисования Qt.
     */
    void draw(QPainter &painter) const;

    /**
     * @brief Возвращает координату метки.
     */
    const QPoint &point() const noexcept;

    /**
     * @brief Возвращает цвет метки.
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
    QPoint m_point;   ///< Координата метки.
    QColor m_color;   ///< Цвет метки.
};

Q_DECLARE_METATYPE(MyPoint)

#endif // MYPOINT_H
