set(LIBNOISE_SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/noiseutils.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/noiseutils.cpp"
    PARENT_SCOPE)
IF(APPLE)
set(LIBNOISE_SRCS
    ${LIBNOISE_SRCS}
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/latlon.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/noisegen.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/model/cylinder.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/model/line.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/model/plane.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/model/sphere.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/abs.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/add.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/billow.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/blend.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/cache.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/checkerboard.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/clamp.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/const.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/curve.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/cylinders.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/displace.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/exponent.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/invert.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/max.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/min.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/modulebase.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/multiply.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/perlin.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/power.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/ridgedmulti.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/rotatepoint.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/scalebias.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/scalepoint.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/select.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/spheres.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/terrace.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/translatepoint.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/turbulence.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/src/module/voronoi.cpp"
    PARENT_SCOPE)
ENDIF()
source_group("libnoise" FILES ${LIBNOISE_SRCS})