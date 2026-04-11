#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mypoint.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class PointsWidget;
class WorkersLauncher;

/**
 * @brief Главное окно первого приложения лабораторной работы по потокам.
 *
 * @details
 * Класс отвечает за:
 * - инициализацию UI;
 * - создание области отображения точек;
 * - делегирование запуска Worker через WorkersLauncher;
 * - приём точек и их отображение.
 */
class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    /**
     * @brief Способ запуска worker-объектов.
     */
    enum class LaunchMode
    {
        QtConcurrent,
        QRunnable
    };

private slots:
    /**
     * @brief Запускает Worker-объекты через QtConcurrent::run().
     */
    void slotQtConcurrent();

    /**
     * @brief Запускает Worker-объекты через QRunnable.
     */
    void slotQRunnable();

    /**
     * @brief Очищает область отображения.
     */
    void slotClear();

    /**
     * @brief Принимает новую точку и передаёт её в виджет отображения.
     * @param point Точка для добавления.
     */
    void slotAddPoint(MyPoint point);

    /**
     * @brief Обрабатывает завершение текущего запуска всех Worker.
     */
    void slotWorkersFinished();

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
     * @brief Создаёт и настраивает WorkersLauncher.
     */
    void setupWorkersLauncher();

    /**
     * @brief Запускает worker-объекты указанным способом.
     * @param mode Способ запуска.
     */
    void startWorkers(LaunchMode mode);

    /**
     * @brief Очищает область отображения без сообщения в status bar.
     */
    void clearPointsView();

    /**
     * @brief Вычисляет число шагов на один Worker по текущей ширине области рисования.
     */
    int calculateStepsPerWorker() const noexcept;

    /**
     * @brief Возвращает длину программной задержки.
     */
    qsizetype calculateDelayIterations() const noexcept;

private:
    Ui::MainWindow *ui = nullptr;                   ///< Сгенерированный интерфейс формы.
    PointsWidget *m_pointsWidget = nullptr;         ///< Область отображения точек.
    WorkersLauncher *m_workersLauncher = nullptr;   ///< Координатор запуска Worker.
};

#endif // MAINWINDOW_H
