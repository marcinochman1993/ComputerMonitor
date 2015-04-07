
find_package(Qt5 COMPONENTS Widgets Core PrintSupport)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(QCustomPlot qcustomplot.cpp)

target_link_libraries(QCustomPlot Qt5::Widgets Qt5::Core Qt5::PrintSupport)