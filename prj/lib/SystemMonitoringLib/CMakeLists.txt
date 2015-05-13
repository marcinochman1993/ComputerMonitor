# ------- definicja zmiennych --------
set(SystemMonitoringLib_NAME "SystemMonitoringLib")
set(SystemMonitoringLib_INC_DIRS inc/)

# -------- znalezienie dodatkowych bibliotek --------
if(UNIX)
  find_library(SENSORS_LIBS sensors)
  find_package(Boost COMPONENTS filesystem REQUIRED)
endif(UNIX)

# ------- ustawianie opcji kompilacji -----
if(UNIX)
  add_definitions("-std=c++11 -pedantic -Wall")
endif(UNIX)

# ------- dodawanie źródeł biblioteki --------
file(GLOB SystemMonitoringLib_SOURCES src/*.cpp)

# ------- foldery plików nagłówkowych --------
include_directories(${SystemMonitoringLib_INC_DIRS} ${Boost_INCLUDE_DIRS})

# ------- dodanie biblioteki do kompilacji ------
add_library(${SystemMonitoringLib_NAME} ${SystemMonitoringLib_SOURCES})

target_link_libraries(${SystemMonitoringLib_NAME} ${SENSORS_LIBS} ${Boost_LIBRARIES} -lboost_system) # błąd w wyszukiwaniu bibliotek do BOOST