# -------- definicja zmiennych  ---------
set(UI_INC_DIR ${CMAKE_CURRENT_BINARY_DIR}/ui/inc/)
set(INC_DIR inc/ inc/gui/ inc/models inc/data inc/delegates
  ${CMAKE_CURRENT_BINARY_DIR}/${UI_INC_DIR}
  lib/SystemMonitoringLib/inc
  lib/SystemMonitoringNetworkLib/inc
  lib/QCustomPlot/)
set(QT5_COMPONENTS Widgets Quick Core PrintSupport)
set(ADDITIONAL_LIBS Qt5::Widgets Qt5::Quick Qt5::Core Qt5::PrintSupport
  QCustomPlot SystemMonitoringNetworkLib
  SystemMonitoringLib)
# -------- dodanie podkatalogu  ---------
add_subdirectory(lib)

# -------- znajdowanie potrzebnych bibliotek ---------
find_package(Qt5 COMPONENTS ${QT5_COMPONENTS})
find_package(Boost COMPONENTS system REQUIRED)
# -------- ustawienia kompilacji  ---------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT5_WRAP_UI_DIR ${UI_INC_DIR})
if(UNIX)
  add_definitions("-std=c++11 -pedantic -Wall")
endif(UNIX)

include_directories(${INC_DIR})

# -------- pliki potrzebne do kompilacji  ---------
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE FORMS ui/*.ui)
file(GLOB_RECURSE RSRCS rsrc/*.qrc)
file(GLOB QOBJECT_HEADERS inc/gui/*.hpp inc/data/*.hpp inc/models/*.hpp inc/delegates/*.hpp)

# -------- uruchomienie moc, uic, rcc  ---------
qt5_wrap_cpp(computer_monitor_HEADERS_MOC ${QOBJECT_HEADERS} )
qt5_wrap_ui(computer_monitor_FORMS_HEADERS ${FORMS})
qt5_add_resources(computer_monitor_RSRCS ${RSRCS})

# -------- niestety nie da się zmusić makra qt5_wrap_cpp -------
# -------- aby wygenerował pliki do odpowiedniego folderu -------

# -------- ustawienia kompilacji  ---------
add_executable(computer_monitor ${SOURCES} ${computer_monitor_HEADERS_MOC}
  ${computer_monitor_FORMS_HEADERS} ${computer_monitor_RSRCS} ${QML_SRCS})

# -------- konsolidacja  ---------
target_link_libraries(computer_monitor ${ADDITIONAL_LIBS} ${Boost_LIBRARIES})