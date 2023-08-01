set(SOURCE_FILES main.cpp)

add_executable(main_executable ${SOURCE_FILES})

add_subdirectory(solver)
add_subdirectory(data)
add_subdirectory(expression)
add_subdirectory(constrait)

target_link_libraries(main_executable PRIVATE 
data_lib 
expression_lib 
constrait_lib 
solver_lib)
add_subdirectory(tests)