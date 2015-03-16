cmake_minimum_required(VERSION 2.8.11)
project("Computer Monitor")

find_package(Qt5 COMPONENTS Widgets Quick)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(inc)

file(GLOB SOURCES src/*.cpp)
file(GLOB FORMS ui/*.ui)

set(computer_monitor_BIN_PATH "${CMAKE_CURRENT_SOURCE_DIR}/app")
set(QOBJECT_HEADERS inc/ComputerMonitorMainWindow.hpp)

qt5_wrap_cpp(computer_monitor_HEADERS_MOC ${QOBJECT_HEADERS} )
qt5_wrap_ui(computer_monitor_FORMS_HEADERS ${FORMS} )

add_executable(computer_monitor ${SOURCES} ${computer_monitor_HEADERS_MOC}
	${computer_monitor_FORMS_HEADERS} )

#set_target_properties(computer_monitor PROPERTIES RUNTIME_OUTPUT_DIRECTORY 
#	${computer_monitor_BIN_PATH})

target_link_libraries(computer_monitor Qt5::Widgets Qt5::Quick)