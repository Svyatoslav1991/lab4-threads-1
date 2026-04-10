set(APP_TARGET lab4_threads_1)
set(CORE_TARGET lab4_threads_1_core)

set(CORE_SOURCES
    include/mainwindow.h
    include/mypoint.h
    include/worker.h

    src/mainwindow.cpp
    src/mypoint.cpp
    src/mainwindow.ui
    src/worker.cpp
)

set(APP_SOURCES
    src/main.cpp
)

add_library(${CORE_TARGET} STATIC
    ${CORE_SOURCES}
)

target_include_directories(${CORE_TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${CORE_TARGET}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Concurrent
)

add_executable(${APP_TARGET} WIN32
    ${APP_SOURCES}
)

target_link_libraries(${APP_TARGET}
    PRIVATE
        ${CORE_TARGET}
)

if(WIN32 AND QT_VERSION_MAJOR EQUAL 5)
    target_link_libraries(${APP_TARGET} PRIVATE Qt5::WinMain)
endif()
