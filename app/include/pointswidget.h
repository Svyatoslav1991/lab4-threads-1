#ifndef POINTSWIDGET_H
#define POINTSWIDGET_H

#include <QVector>
#include <QWidget>

#include "mypoint.h"

/**
 * @brief Виджет для хранения и отображения набора точек MyPoint.
 *
 * @details
 * Класс инкапсулирует:
 * - контейнер точек;
 * - добавление новых точек;
 * - очистку данных;
 * - отрисовку содержимого.
 *
 * Это позволяет не перегружать MainWindow логикой рисования.
 */
class PointsWidget final : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Создаёт виджет отображения точек.
     * @param parent Родительский виджет.
     */
    explicit PointsWidget(QWidget *parent = nullptr);

    /**
     * @brief Добавляет точку и инициирует перерисовку.
     * @param point Точка для отображения.
     */
    void addPoint(const MyPoint &point);

    /**
     * @brief Очищает все точки и инициирует перерисовку.
     */
    void clearPoints();

    /**
     * @brief Возвращает все накопленные точки.
     */
    const QVector<MyPoint> &points() const noexcept;

    /**
     * @brief Возвращает количество накопленных точек.
     */
    int pointCount() const noexcept;

protected:
    /**
     * @brief Отрисовывает все накопленные точки.
     * @param event Событие перерисовки.
     */
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<MyPoint> m_points; ///< Контейнер точек для отображения.
};

#endif // POINTSWIDGET_H
