#ifndef WORKERSLAUNCHER_H
#define WORKERSLAUNCHER_H

#include <QFuture>
#include <QColor>
#include <QObject>
#include <QVector>

#include "mypoint.h"

class Worker;

/**
 * @brief Координатор создания и запуска Worker-объектов.
 *
 * @details
 * Класс отвечает за:
 * - создание набора Worker;
 * - настройку их signal-slot соединений;
 * - подготовку worker-ов к новому запуску;
 * - запуск через QtConcurrent::run();
 * - запуск через QRunnable + QThreadPool;
 * - ожидание завершения запущенных задач.
 *
 * UI-логика в класс не входит.
 */
class WorkersLauncher final : public QObject
{
    Q_OBJECT

public:
    explicit WorkersLauncher(QObject *parent = nullptr);
    ~WorkersLauncher() override;

    /**
     * @brief Подготавливает worker-объекты к новому запуску.
     * @param startX Начальное значение общей координаты X.
     * @param stepsPerWorker Количество шагов на один Worker.
     * @param delayIterations Длина программной задержки.
     */
    void prepareForRun(int startX,
                       int stepsPerWorker,
                       qsizetype delayIterations) noexcept;

    /**
     * @brief Запускает worker-объекты через QtConcurrent::run().
     */
    void launchViaQtConcurrent();

    /**
     * @brief Запускает worker-объекты через QRunnable.
     */
    void launchViaQRunnable();

    /**
     * @brief Ожидает завершения всех запущенных задач.
     */
    void waitForFinished();

    /**
     * @brief Возвращает количество worker-объектов.
     */
    int workerCount() const noexcept;

    /**
     * @brief Проверяет, выполняется ли сейчас хотя бы одна задача.
     */
    bool hasRunningTasks() const noexcept;

signals:
    /**
     * @brief Пробрасывает новую точку наружу.
     * @param point Точка для отображения.
     */
    void signalAddPoint(MyPoint point);

    /**
     * @brief Сигнализирует, что все worker-объекты завершили текущий запуск.
     */
    void signalAllWorkersFinished();

private slots:
    /**
     * @brief Обрабатывает завершение одного Worker.
     */
    void slotWorkerFinished();

private:
    /**
     * @brief Создаёт набор Worker по умолчанию.
     */
    void createDefaultWorkers();

    /**
     * @brief Освобождает все Worker.
     */
    void destroyWorkers();

    /**
     * @brief Настраивает signal-slot соединения для одного Worker.
     * @param worker Рабочий объект.
     */
    void connectWorkerSignals(Worker *worker);

    /**
     * @brief Применяет параметры запуска ко всем Worker.
     * @param stepsPerWorker Количество шагов на один Worker.
     * @param delayIterations Длина программной задержки.
     */
    void configureWorkers(int stepsPerWorker,
                          qsizetype delayIterations) noexcept;

private:
    QVector<Worker *> m_workers;      ///< Рабочие объекты.
    QVector<QFuture<void>> m_futures; ///< Запуски через QtConcurrent.
    int m_sharedX = 0;                ///< Общая для всех Worker координата X.
    int m_activeWorkers = 0;          ///< Число Worker, активных в текущем запуске.
};

#endif // WORKERSLAUNCHER_H
