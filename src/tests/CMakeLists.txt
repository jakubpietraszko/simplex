project(tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


file(GLOB TEST_SOURCES *.cpp *.cc *.c)

add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${SOURCES_WITHOUT_MAIN})
target_link_libraries(${PROJECT_NAME} gtest gtest_main data_lib expression_lib
    constrait_lib solver_lib)