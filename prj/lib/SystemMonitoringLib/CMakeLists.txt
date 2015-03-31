file(GLOB SystemMonitoringLib_SOURCES src/*.cpp)

include_directories(inc)

add_library(SystemMonitoringLib ${SystemMonitoringLib_SOURCES}) 