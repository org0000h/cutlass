#CMakeLists.txt
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_C_FLAGS "-Wall -std=c99")
Project(cutlass)

add_subdirectory(libraries)

#header locations
include_directories(../../src/libraries
					../../src/libraries/dataStructure/api 
					../../src/libraries/console/api
					../../src/libraries/console/implement 
					../../src/libraries/console/interface 
					../../src/libraries/console/ 
					../../src/libraries/log/api
				    ../../src/libraries/mbedTLS/include/
					)

# which platform 
if(PLATFORM MATCHES "LINUX")
    add_definitions(-DPLATFORM_LINUX)
    set(SAMPLE_SRC  ../../src/app/sample.c)
    
    ADD_DEFINITIONS(-DON_UNIX=1)
elseif(PLATFORM MATCHES "WINDOWS")
    add_definitions(-DPLATFORM_WINDOWS)
else()
    add_definitions(-DPLATFORM_OTHER)
endif()


set(EXECUTABLE_OUTPUT_PATH ./)
link_directories(bin/)
add_executable(sample.out ${SAMPLE_SRC})
target_link_libraries(sample.out cutlass) # chose dynamic lib by default
