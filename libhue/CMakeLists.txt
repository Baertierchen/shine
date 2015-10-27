include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

file(GLOB_RECURSE libhue_SRCS *.cpp *.h)

add_library(hue ${libhue_SRCS})

if(HARMATTAN_BUILD)
    target_link_libraries(hue qjson)
else()
    find_package(Qt5Core)
    find_package(Qt5Gui)
    find_package(Qt5Network)
    target_link_libraries(hue Qt5::Core Qt5::Gui Qt5::Network)
endif()

