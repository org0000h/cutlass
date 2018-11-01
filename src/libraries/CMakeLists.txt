
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_C_FLAGS "-Wall -std=c99")
# headers
include_directories(
					dataStructure/api/
					console/api/
					console/implement/
					console/portable/
					classString/
					)

aux_source_directory(classString/ STRING_LIB_SRCS)
aux_source_directory(dataStructure/implement DATAST_LIB_SRCS)
aux_source_directory(console CONSOLE1_LIB_SRCS)
aux_source_directory(console/implement CONSOLE2_LIB_SRCS)
aux_source_directory(console/portable CONSOLE3_LIB_SRCS)

set(LIBRARY_OUTPUT_PATH ../../bin)

# Generate link library
add_library (cutlass SHARED
				${STRING_LIB_SRCS} 
				${DATAST_LIB_SRCS} 
				${CONSOLE1_LIB_SRCS} 
				${CONSOLE2_LIB_SRCS} 
				${CONSOLE3_LIB_SRCS}
			)
			
add_library (cutlass_static STATIC
				${STRING_LIB_SRCS} 
				${DATAST_LIB_SRCS} 
				${CONSOLE1_LIB_SRCS} 
				${CONSOLE2_LIB_SRCS} 
				${CONSOLE3_LIB_SRCS}
			)

set_target_properties(cutlass PROPERTIES VERSION 1.0 )
set_target_properties(cutlass_static PROPERTIES OUTPUT_NAME "cutlass")