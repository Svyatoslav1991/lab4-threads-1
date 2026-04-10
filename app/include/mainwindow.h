#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Главное окно первого приложения лабораторной работы по потокам.
 *
 * @details
 * На текущем этапе класс отвечает за:
 * - инициализацию пользовательского интерфейса;
 * - подключение QAction из меню и toolbar;
 * - базовые слоты-команды приложения.
 *
 * Логика отображения точек и запуска рабочих объектов будет добавлена
 * на следующих шагах.
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
     * @brief Заглушка под будущую очистку области отображения.
     */
    void slotClear();

private:
    /**
     * @brief Выполняет базовую настройку UI.
     */
    void initializeUi();

    /**
     * @brief Подключает QAction из .ui к слотам MainWindow.
     */
    void connectActions();

private:
    Ui::MainWindow *ui = nullptr; ///< Сгенерированный интерфейс формы.
};

#endif // MAINWINDOW_H
