find_package(Qt5 COMPONENTS Widgets Quick Core)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)
file(GLOB FORMS ui/*.ui)
file(GLOB RSRCS rsrc/*.qrc)
file(GLOB QML_SRCS rsrc/qml/*.qml)

#set(computer_monitor_BIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/app")
set(QOBJECT_HEADERS inc/ComputerMonitorMainWindow.hpp)

qt5_wrap_cpp(computer_monitor_HEADERS_MOC ${QOBJECT_HEADERS} )
qt5_wrap_ui(computer_monitor_FORMS_HEADERS ${FORMS} )
qt5_add_resources(computer_monitor_RSRCS ${RSRCS})


add_executable(computer_monitor ${SOURCES} ${computer_monitor_HEADERS_MOC}
        ${computer_monitor_FORMS_HEADERS} ${computer_monitor_RSRCS} ${QML_SRCS})

target_link_libraries(computer_monitor Qt5::Widgets Qt5::Quick Qt5::Core)
