cmake_minimum_required(VERSION 2.8.11)

project(shineGUI)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Network)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/libhue
)

file(GLOB_RECURSE shineGUI_SRCS *.cpp *.h *.ui)
file(GLOB_RECURSE shineGUI_UI *.ui)

qt5_wrap_ui(UI_SRCS ${shineGUI_UI})

# Tell CMake to create the executable
add_executable(shineGUI ${shineGUI_SRCS})

target_link_libraries(shineGUI hue Qt5::Core Qt5::Widgets Qt5::Network)

file(GLOB_RECURSE ICONS ../../icons/*.svg)

add_custom_target(shineGUI-icon ALL
    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/../../icons
    COMMAND cp ${ICONS} ${CMAKE_CURRENT_BINARY_DIR}/../../icons
)
