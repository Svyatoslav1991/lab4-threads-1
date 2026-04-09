set(TEST_TARGET test_lab4_threads_1)
set(TEST_SOURCES
    test_mainwindow.cpp
)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test_mainwindow.cpp)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test Widgets Concurrent)

    add_executable(${TEST_TARGET}
        ${TEST_SOURCES}
    )

    target_link_libraries(${TEST_TARGET}
        PRIVATE
            lab4_threads_1_core
            Qt${QT_VERSION_MAJOR}::Test
            Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::Concurrent
    )

    add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})
else()
    message(STATUS "tests: файл test_mainwindow.cpp пока отсутствует, сборка тестов пропущена.")
endif()