file(GLOB SystemMonitoringNetworkLib_SOURCES src/*.cpp)
include_directories(inc)

add_library(SystemMonitoringNetworkLib ${SystemMonitoringNetworkLib_SOURCES})