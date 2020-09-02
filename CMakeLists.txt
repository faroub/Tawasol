cmake_minimum_required(VERSION 3.1.0)

project(TAWASOL)

# flags
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DQT_NO_DEBUG)
endif()

#  QT_MESSAGELOGCONTEXT

set(ENV{QT_MESSAGE_PATTERN} "[%{time yyyyMMdd h:mm:ss.zzz t} %{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}] %{file}:%{line} - %{message}")

find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

# include files
include_directories(${Qt5Widgets_INCLUDE_DIRS})

set(LIB_DIR "./src"
    CACHE PATH "The path to the Qt source files.")

set(RESOURCES_DIR "../resources"
    CACHE PATH "The path to the resources directory.")

include_directories(${LIB_DIR}/gui
                    ${LIB_DIR}/io
                    ${LIB_DIR}/utils)




add_subdirectory(${LIB_DIR}/gui)
add_subdirectory(${LIB_DIR}/io)
add_subdirectory(${LIB_DIR}/utils)





add_subdirectory(app)




