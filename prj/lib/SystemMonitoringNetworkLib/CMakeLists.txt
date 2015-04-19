# ------- definicja zmiennych --------
set(SystemMonitoringNetworkLib_NAME SystemMonitoringNetworkLib)
set(SystemMonitoringNetworkLib_INC_DIRS inc/)

# ------- dodawanie źródeł biblioteki --------
file(GLOB SystemMonitoringNetworkLib_SOURCES src/*.cpp)

# ------- foldery plików nagłówkowych --------
include_directories(inc)

# ------- dodanie biblioteki do kompilacji ------
add_library(SystemMonitoringNetworkLib ${SystemMonitoringNetworkLib_SOURCES})