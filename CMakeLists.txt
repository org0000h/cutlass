#CMakeLists.txt
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_C_FLAGS "-Wall -std=c99")
Project(sample)
# add_subdirectory(app)
add_subdirectory(library)
if(PLATFORM MATCHES "LINUX")
    add_definitions(-DPLATFORM_LINUX)
    include_directories(library
						library/DataStructure/interface 
						library/console/interface 
						library/console/implement 
						library/console/adaptation 
						library/string/)
    set(MINICLIENT_SRC  app/app.c)
elseif(PLATFORM MATCHES "WINDOWS")
    add_definitions(-DPLATFORM_WINDOWS)
else()
    add_definitions(-DPLATFORM_OTHER)
endif()
set(EXECUTABLE_OUTPUT_PATH ./)
set(CMAKE_C_FLAGS "-Wall")
link_directories(library/bin)
add_executable(sample.out app/app.c)
target_link_libraries(sample.out cutlass)
