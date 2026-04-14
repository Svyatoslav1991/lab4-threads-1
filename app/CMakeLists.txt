set(APP_TARGET lab4_threads_1)
set(APP_CORE_TARGET lab4_threads_1_app)

add_library(${APP_CORE_TARGET} STATIC
    include/mainwindow.h
    include/myrunnable.h
    include/workerslauncher.h

    src/mainwindow.cpp
    src/myrunnable.cpp
    src/workerslauncher.cpp
    src/mainwindow.ui
)

target_include_directories(${APP_CORE_TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${APP_CORE_TARGET}
    PUBLIC
        workers_core
        workers_widgets
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Concurrent
)

add_executable(${APP_TARGET} WIN32
    src/main.cpp
)

target_link_libraries(${APP_TARGET}
    PRIVATE
        ${APP_CORE_TARGET}
)

if(WIN32 AND QT_VERSION_MAJOR EQUAL 5)
    target_link_libraries(${APP_TARGET} PRIVATE Qt5::WinMain)
endif()