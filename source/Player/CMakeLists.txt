set(PLAYER_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Player.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/PlayerCombat.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/PlayerStats.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/PlayerStats.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/PlayerClass.h"
    PARENT_SCOPE)

source_group("Player" FILES ${PLAYER_SRCS})
