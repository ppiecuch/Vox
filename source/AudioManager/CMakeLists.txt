set(AUDIOMANAGER_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/AudioManager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/AudioManager.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/SoundEffects.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/SoundEffectsEnum.h"
    PARENT_SCOPE)

source_group("AudioManager" FILES ${AUDIOMANAGER_SRCS})
