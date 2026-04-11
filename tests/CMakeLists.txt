find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test Widgets Concurrent)

add_executable(test_mypoint
    test_mypoint.cpp
)

target_link_libraries(test_mypoint
    PRIVATE
        lab4_threads_1_core
        Qt${QT_VERSION_MAJOR}::Test
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Concurrent
)

add_test(NAME test_mypoint COMMAND test_mypoint)

add_executable(test_worker
    test_worker.cpp
)

target_link_libraries(test_worker
    PRIVATE
        lab4_threads_1_core
        Qt${QT_VERSION_MAJOR}::Test
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Concurrent
)

add_test(NAME test_worker COMMAND test_worker)

add_executable(test_pointswidget
    test_pointswidget.cpp
)

target_link_libraries(test_pointswidget
    PRIVATE
        lab4_threads_1_core
        Qt${QT_VERSION_MAJOR}::Test
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Concurrent
)

add_test(NAME test_pointswidget COMMAND test_pointswidget)

add_executable(test_myrunnable
    test_myrunnable.cpp
)

target_link_libraries(test_myrunnable
    PRIVATE
        lab4_threads_1_core
        Qt${QT_VERSION_MAJOR}::Test
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Concurrent
)

add_test(NAME test_myrunnable COMMAND test_myrunnable)

add_executable(test_workerslauncher
    test_workerslauncher.cpp
)

target_link_libraries(test_workerslauncher
    PRIVATE
        lab4_threads_1_core
        Qt${QT_VERSION_MAJOR}::Test
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Concurrent
)

add_test(NAME test_workerslauncher COMMAND test_workerslauncher)
