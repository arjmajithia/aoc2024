cmake_minimum_required(VERSION 3.14)
project(day14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

option(PART1 "PART1" ${PART1})

find_package(Boost)

add_executable(day14 src/main.cpp)

if("${PART1}")
  target_compile_options(${PROJECT_NAME} PRIVATE -DPART1)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "out")

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()
