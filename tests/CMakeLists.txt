find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test Widgets Concurrent)

set(MYPOINT_TEST_TARGET test_mypoint)

add_executable(${MYPOINT_TEST_TARGET}
    test_mypoint.cpp
)

target_link_libraries(${MYPOINT_TEST_TARGET}
    PRIVATE
        lab4_threads_1_core
        Qt${QT_VERSION_MAJOR}::Test
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Concurrent
)

add_test(NAME ${MYPOINT_TEST_TARGET} COMMAND ${MYPOINT_TEST_TARGET})
