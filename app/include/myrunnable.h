#ifndef MYRUNNABLE_H
#define MYRUNNABLE_H

#include <QRunnable>

class Worker;

/**
 * @brief Тонкая обёртка над Worker для запуска через QThreadPool.
 *
 * @details
 * Класс:
 * - хранит указатель на Worker, которым не владеет;
 * - в методе run() делегирует выполнение в Worker::doWork().
 *
 * После передачи объекта в QThreadPool через start() сам runnable
 * удаляется пулом автоматически.
 */
class MyRunnable final : public QRunnable
{
public:
    /**
     * @brief Создаёт runnable-объект.
     * @param worker Рабочий объект, метод doWork() которого будет вызван.
     */
    explicit MyRunnable(Worker *worker);

    /**
     * @brief Выполняет полезную работу в потоке пула.
     */
    void run() override;

private:
    Worker *m_worker = nullptr; ///< Рабочий объект, которым MyRunnable не владеет.
};

#endif // MYRUNNABLE_H
