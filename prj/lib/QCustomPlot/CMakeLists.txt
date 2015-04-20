# ------- definicja zmiennych --------
set(SystemMonitoringLib_NAME "SystemMonitoringLib")
set(SystemMonitoringLib_INC_DIRS inc/)

# ------- znalezienie biblioteki Qt5 i jej komponentów --------
find_package(Qt5 COMPONENTS Widgets Core PrintSupport)

# ------- dodanie aktualnego folderu do folderów plików nagłowkowych  --------
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ------- wywołanie moc ---------
qt5_wrap_cpp(qcustomplot_HEADERS_MOC qcustomplot.h)

# ------- dodawanie źródeł biblioteki --------
add_library(QCustomPlot qcustomplot.cpp ${qcustomplot_HEADERS_MOC})

# ------- konsolidacja biblioteki ------
target_link_libraries(QCustomPlot Qt5::Widgets Qt5::Core Qt5::PrintSupport)