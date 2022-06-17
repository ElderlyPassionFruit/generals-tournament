set(MAIN_HEADERS Cell.h Config.h Game.h Map.h Player.h)
set(MAIN_SOURCES main.cpp Cell.cpp Config.cpp Game.cpp Map.cpp Player.cpp)
add_executable(generals-tournament ${MAIN_HEADERS} ${MAIN_SOURCES})

set(GEN_HEADERS Cell.h)
set(GEN_SOURCES GenMap.cpp)
add_executable(map-generator ${GEN_HEADERS} ${GEN_SOURCES})

set_target_properties(generals-tournament map-generator PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BIN_DIR})
