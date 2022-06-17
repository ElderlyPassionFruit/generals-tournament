add_executable(afk_strategy afk_strategy.cpp)
add_executable(random_strategy random_strategy.cpp)

set_target_properties(afk_strategy random_strategy PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
