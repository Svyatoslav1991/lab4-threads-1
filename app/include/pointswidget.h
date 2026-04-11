#ifndef POINTSWIDGET_H
#define POINTSWIDGET_H

#include <QVector>
#include <QWidget>

#include "mypoint.h"

/**
 * @brief Виджет для хранения и отображения набора объектов MyPoint.
 *
 * @details
 * Класс инкапсулирует:
 * - контейнер меток;
 * - добавление новых меток;
 * - очистку данных;
 * - отрисовку содержимого.
 *
 * Это позволяет не перегружать MainWindow логикой хранения
 * и рисования.
 */
class PointsWidget final : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Создаёт виджет отображения меток.
     * @param parent Родительский виджет.
     */
    explicit PointsWidget(QWidget *parent = nullptr);

    /**
     * @brief Добавляет метку и инициирует перерисовку.
     * @param point Метка для отображения.
     */
    void addPoint(const MyPoint &point);

    /**
     * @brief Очищает все метки и инициирует перерисовку.
     */
    void clearPoints();

    /**
     * @brief Возвращает все накопленные метки.
     */
    const QVector<MyPoint> &points() const noexcept;

    /**
     * @brief Возвращает количество накопленных меток.
     */
    int pointCount() const noexcept;

protected:
    /**
     * @brief Отрисовывает содержимое виджета.
     * @param event Событие перерисовки.
     */
    void paintEvent(QPaintEvent *event) override;

private:
    /**
     * @brief Отрисовывает фон виджета.
     * @param painter Объект рисования.
     */
    void paintBackground(QPainter &painter) const;

    /**
     * @brief Отрисовывает все накопленные метки.
     * @param painter Объект рисования.
     */
    void paintPoints(QPainter &painter) const;

private:
    QVector<MyPoint> m_points; ///< Контейнер меток для отображения.
};

#endif // POINTSWIDGET_H
