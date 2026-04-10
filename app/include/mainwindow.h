#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "mypoint.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class PointsWidget;

/**
 * @brief Главное окно первого приложения лабораторной работы по потокам.
 *
 * @details
 * На текущем этапе класс отвечает за:
 * - инициализацию пользовательского интерфейса;
 * - создание области отображения точек;
 * - хранение общей координаты X;
 * - приём точек от Worker;
 * - очистку области отображения;
 * - тестовый запуск Worker в интерфейсном потоке.
 */
class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Создаёт главное окно приложения.
     * @param parent Родительский виджет.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Освобождает ресурсы главного окна.
     */
    ~MainWindow() override;

private slots:
    /**
     * @brief Заглушка под будущий запуск worker'ов через QtConcurrent.
     */
    void slotQtConcurrent();

    /**
     * @brief Заглушка под будущий запуск worker'ов через QRunnable.
     */
    void slotQRunnable();

    /**
     * @brief Очищает область отображения.
     */
    void slotClear();

    /**
     * @brief Принимает новую точку от Worker и передаёт её в виджет отображения.
     * @param point Точка для добавления.
     */
    void slotAddPoint(MyPoint point);

private:
    /**
     * @brief Выполняет базовую настройку UI.
     */
    void initializeUi();

    /**
     * @brief Подключает QAction из .ui к слотам MainWindow.
     */
    void connectActions();

    /**
     * @brief Создаёт и размещает виджет отображения точек в centralwidget.
     */
    void setupPointsWidget();

    /**
     * @brief Выполняет тестовый прогон Worker в интерфейсном потоке.
     *
     * @details
     * Метод соответствует первому этапу лабораторной работы:
     * создаётся Worker, настраивается соединение signal-slot и вызывается doWork()
     * без запуска отдельного потока.
     */
    void test();

private:
    Ui::MainWindow *ui = nullptr;              ///< Сгенерированный интерфейс формы.
    PointsWidget *m_pointsWidget = nullptr;    ///< Область отображения точек.
    int m_x = 0;                               ///< Общая для всех worker'ов координата X.
};

#endif // MAINWINDOW_H
