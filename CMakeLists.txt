cmake_minimum_required(VERSION 2.8.3)
project(cslibs_time)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(cmake/cslibs_time_enable_c++17.cmake)

find_package(catkin REQUIRED COMPONENTS roscpp)
catkin_package(
    INCLUDE_DIRS
        include
    CFG_EXTRAS
        cslibs_time_enable_c++17.cmake
    CATKIN_DEPENDS
        roscpp
)

add_library(${PROJECT_NAME}
    INTERFACE
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        include
        ${roscpp_INCLUDE_DIRS}
)

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

