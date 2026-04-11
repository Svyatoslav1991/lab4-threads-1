#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFuture>
#include <QMainWindow>
#include <QVector>

#include "mypoint.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class PointsWidget;
class Worker;

/**
 * @brief Главное окно первого приложения лабораторной работы по потокам.
 *
 * @details
 * На текущем этапе класс отвечает за:
 * - инициализацию UI;
 * - создание области отображения точек;
 * - создание рабочих объектов Worker;
 * - запуск Worker через QtConcurrent::run();
 * - запуск Worker через QRunnable + QThreadPool;
 * - приём точек от Worker и их отображение.
 */
class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

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
     * @brief Принимает новую точку от Worker и передаёт её в виджет отображения.
     * @param point Точка для добавления.
     */
    void slotAddPoint(MyPoint point);

    /**
     * @brief Обрабатывает завершение одного Worker.
     */
    void slotWorkerFinished();

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
     * @brief Создаёт рабочие объекты Worker и настраивает их соединения.
     */
    void createWorkers();

    /**
     * @brief Освобождает рабочие объекты Worker.
     */
    void destroyWorkers();

    /**
     * @brief Ожидает завершения всех задач QtConcurrent.
     */
    void waitForFutures();

    /**
     * @brief Проверяет, выполняется ли сейчас хотя бы одна задача.
     */
    bool hasRunningTasks() const noexcept;

    /**
     * @brief Подготавливает Worker-объекты к новому запуску.
     *
     * @details
     * Метод:
     * - очищает область отображения;
     * - сбрасывает общую координату X;
     * - рассчитывает число шагов на один Worker по ширине окна;
     * - задаёт программную задержку.
     */
    void prepareWorkersForRun();

    /**
     * @brief Вычисляет число шагов на один Worker по текущей ширине области рисования.
     */
    int calculateStepsPerWorker() const noexcept;

    /**
     * @brief Возвращает длину программной задержки.
     */
    qsizetype calculateDelayIterations() const noexcept;

private:
    Ui::MainWindow *ui = nullptr;           ///< Сгенерированный интерфейс формы.
    PointsWidget *m_pointsWidget = nullptr; ///< Область отображения точек.
    QVector<Worker *> m_workers;            ///< Рабочие объекты.
    QVector<QFuture<void>> m_futures;       ///< Запуски через QtConcurrent.
    int m_X = 0;                            ///< Общая для всех worker-ов координата X.
    int m_activeWorkers = 0;                ///< Число worker'ов, работающих в текущем запуске.
};

#endif // MAINWINDOW_H
