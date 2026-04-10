#ifndef MYRUNNABLE_H
#define MYRUNNABLE_H

#include <QRunnable>

class Worker;

/**
 * @brief Обёртка над Worker для запуска через QThreadPool.
 *
 * @details
 * Класс соответствует заданию с QRunnable:
 * - хранит указатель на Worker;
 * - в методе run() вызывает Worker::doWork().
 *
 * Объект передаётся под управление QThreadPool и после start()
 * не должен использоваться напрямую.
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
    Worker *m_worker = nullptr; ///< Рабочий объект, не принадлежащий MyRunnable.
};

#endif // MYRUNNABLE_H
