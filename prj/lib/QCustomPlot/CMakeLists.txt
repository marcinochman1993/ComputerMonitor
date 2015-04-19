# ------- definicja zmiennych --------
set(SystemMonitoringLib_NAME "SystemMonitoringLib")
set(SystemMonitoringLib_INC_DIRS inc/)

# ------- znalezienie biblioteki Qt5 i jej komponentów --------
find_package(Qt5 COMPONENTS Widgets Core PrintSupport)

# ------- dodanie aktualnego folderu do folderów plików nagłowkowych  --------
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ------- dodawanie źródeł biblioteki --------
add_library(QCustomPlot qcustomplot.cpp)

# ------- konsolidacja biblioteki ------
target_link_libraries(QCustomPlot Qt5::Widgets Qt5::Core Qt5::PrintSupport)