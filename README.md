# lab4_threads_1

Первое приложение лабораторной работы по Qt-многопоточности.

## Описание

Проект демонстрирует запуск рабочих объектов `Worker` двумя способами:

- через `QtConcurrent::run()`;
- через `QRunnable` + `QThreadPool`.

Каждый `Worker` формирует последовательность цветных меток (`MyPoint`) и передаёт их в GUI-поток через механизм сигналов и слотов Qt. На экране метки отображаются в `PointsWidget` в виде коротких вертикальных линий, движущихся по общей координате `X`.

## Цель проекта

- изучить высокоуровневый запуск задач через `QtConcurrent`;
- изучить запуск задач через `QRunnable`;
- отработать передачу пользовательского типа `MyPoint` между потоками;
- подготовить переиспользуемую архитектуру для следующих приложений лабораторной работы.

## Архитектура

Проект разделён на приложение и две статические библиотеки.

### `workers_core`

Библиотека содержит core-слой без widget-зависимостей:

- `MyPoint` — value object с координатой и цветом;
- `Worker` — рабочий объект, формирующий точки;
- `WorkersRunSettings` — параметры одного запуска worker-объектов.

### `workers_widgets`

Библиотека содержит UI-слой:

- `PointsWidget` — виджет для хранения и отрисовки набора `MyPoint`.

### Приложение `lab4_threads_1`

Приложение содержит:

- `MainWindow` — главное окно;
- `MyRunnable` — обёртку над `Worker` для запуска через `QThreadPool`;
- `WorkersLauncher` — координатор создания и запуска `Worker`.

## Основные сценарии работы

### Запуск через `QtConcurrent`

По нажатию action `QtConcurrent`:

1. вычисляются параметры запуска;
2. подготавливаются worker-объекты;
3. каждый `Worker` запускается через `QtConcurrent::run()`;
4. точки передаются в GUI-поток и отображаются в `PointsWidget`.

### Запуск через `QRunnable`

По нажатию action `QRunnable`:

1. вычисляются параметры запуска;
2. подготавливаются worker-объекты;
3. для каждого `Worker` создаётся `MyRunnable`;
4. `MyRunnable` передаётся в `QThreadPool::globalInstance()->start(...)`.

### Очистка

Action `Clear` очищает область отображения.

## Структура проекта

```text
lab4_threads_1/
├─ CMakeLists.txt
├─ app/
│  ├─ CMakeLists.txt
│  ├─ include/
│  │  ├─ mainwindow.h
│  │  ├─ myrunnable.h
│  │  └─ workerslauncher.h
│  └─ src/
│     ├─ main.cpp
│     ├─ mainwindow.cpp
│     ├─ myrunnable.cpp
│     ├─ workerslauncher.cpp
│     └─ mainwindow.ui
├─ libs/
│  ├─ workers_core/
│  │  ├─ CMakeLists.txt
│  │  ├─ include/
│  │  │  ├─ mypoint.h
│  │  │  ├─ worker.h
│  │  │  └─ workersrunsettings.h
│  │  └─ src/
│  │     ├─ mypoint.cpp
│  │     └─ worker.cpp
│  └─ workers_widgets/
│     ├─ CMakeLists.txt
│     ├─ include/
│     │  └─ pointswidget.h
│     └─ src/
│        └─ pointswidget.cpp
└─ tests/
   ├─ CMakeLists.txt
   ├─ test_mainwindow.cpp
   ├─ test_mypoint.cpp
   ├─ test_myrunnable.cpp
   ├─ test_pointswidget.cpp
   ├─ test_worker.cpp
   └─ test_workerslauncher.cpp
```

## Сборка

### Требования

- CMake 3.16+
- Qt 5 или Qt 6
- компилятор с поддержкой C++17

### Сборка проекта

```bash
cmake -S . -B build
cmake --build build
```

### Запуск приложения

```bash
./build/app/lab4_threads_1
```

На Windows путь к исполняемому файлу зависит от генератора и конфигурации сборки.

## Запуск тестов

```bash
ctest --test-dir build --output-on-failure
```

Либо из Qt Creator через вкладку тестов.

## Что покрыто тестами

В проекте есть unit-тесты для:

- `MyPoint`;
- `Worker`;
- `PointsWidget`;
- `MyRunnable`;
- `WorkersLauncher`;
- `MainWindow`.

## Особенности реализации

- пользовательский тип `MyPoint` зарегистрирован через `qRegisterMetaType<MyPoint>("MyPoint")`;
- для межпоточного взаимодействия используются queued connections;
- общий `X` разделяется между worker-объектами в соответствии с методичкой;
- в `main.cpp` для Windows используется `SetProcessAffinityMask(GetCurrentProcess(), 1)`, чтобы сделать визуализацию работы потоков нагляднее.

## Дальнейшее развитие

Эти библиотеки можно переиспользовать в следующих приложениях лабораторной работы:

- приложение с `QThread`;
- приложение с наследованием от `QThread`;
- приложение с `QMutex`, `QSemaphore`, `QSystemSemaphore`.

## Автор

Мышковский Святослав
Myshkovskiy Svyatoslav