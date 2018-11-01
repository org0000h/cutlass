
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_C_FLAGS "-Wall -std=c99")
# headers
include_directories(
					DataStructure/interface
					console/interface
					console/implement
					console/adaptation
					string
					)

aux_source_directory(string/ STRING_LIB_SRCS)
aux_source_directory(DataStructure/implement DATAST_LIB_SRCS)
aux_source_directory(console CONSOLE1_LIB_SRCS)
aux_source_directory(console/implement CONSOLE2_LIB_SRCS)
aux_source_directory(console/adaptation CONSOLE3_LIB_SRCS)

set(LIBRARY_OUTPUT_PATH .)

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

#set_target_properties(Wsc PROPERTIES VERSION 1.0 SOVERSION 1)
set_target_properties(cutlass_static PROPERTIES OUTPUT_NAME "cutlass")