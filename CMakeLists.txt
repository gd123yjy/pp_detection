cmake_minimum_required(VERSION 2.8)
project( PR_DETECTION )
find_package( OpenCV REQUIRED )

set (source_dir "src/")
set (include_dir "include/")
set (source_ext ".cpp")
set (target_ext ".app")

#Release Debug
set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to Debug")  

#/Od /Zi /arch /Og /Ot /Ox
list( APPEND CMAKE_CXX_FLAGS " -g ${CMAKE_CXX_FLAGS}")

include_directories(include)
#add_subdirectory(include)

#link_directories(${OpenCV_LIBS})

set(file_names 
    "main" )

#-----------------------target for main.app--------------------------
add_executable( main.app
 ${source_dir}HandDetector.cpp
 ${source_dir}ImageReader.cpp
 ${source_dir}ObjectDetector.cpp
 ${source_dir}palmprint_dectection.cpp
)
#msvcrt
#target_link_libraries( main.app ${OpenCV_LIBS} pdcurses json11)
target_link_libraries( main.app ${OpenCV_LIBS})