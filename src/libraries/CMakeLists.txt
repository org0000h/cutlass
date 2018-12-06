#CMakeLists.txt
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_C_FLAGS "-Wall -std=c99")

#header locations
set(LIB_INC
	dataStructure/api/
	console/api/
	console/implement/
	console/portable/
	log/api/
	)
include_directories( ${LIB_INC} )

#all source to be compiled	
aux_source_directory(./ LOG_LIB_SRCS)
aux_source_directory(classString/ STRING_LIB_SRCS)
aux_source_directory(dataStructure/implement DATAST_LIB_SRCS)
aux_source_directory(console CONSOLE1_LIB_SRCS)
aux_source_directory(console/implement CONSOLE2_LIB_SRCS)
aux_source_directory(console/portable CONSOLE3_LIB_SRCS)	
aux_source_directory(log/implement LOG_LIB_SRCS)	
aux_source_directory(log/portable LOG_PORTABLE_LIB_SRCS)	
set(LIB_SRCS 
    ${LOG_LIB_SRCS} 
	${STRING_LIB_SRCS} 
	${DATAST_LIB_SRCS} 
	${CONSOLE1_LIB_SRCS} 
	${CONSOLE2_LIB_SRCS} 
	${CONSOLE3_LIB_SRCS}
	${LOG_LIB_SRCS}
	${LOG_PORTABLE_LIB_SRCS}
	)

# Generate link library
set(LIBRARY_OUTPUT_PATH ../../bin)
add_library (cutlass SHARED ${LIB_SRCS})
add_library (cutlass_static STATIC ${LIB_SRCS})
set_target_properties(cutlass PROPERTIES VERSION 1.0 )
set_target_properties(cutlass_static PROPERTIES OUTPUT_NAME "cutlass")