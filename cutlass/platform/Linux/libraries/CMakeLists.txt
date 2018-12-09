#CMakeLists.txt
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_C_FLAGS "-Wall -std=c99")
    
ADD_DEFINITIONS(-DON_UNIX=1)

#header locations
set(LIB_INC
	../../../src/libraries/data_structure/api/
	../../../src/libraries/console/api/
	../../../src/libraries/console/implement/
	../../../src/libraries/console/portable/
	../../../src/libraries/log/api/
	../../../src/libraries/mbedTLS/include/
	)
include_directories( ${LIB_INC} )

#all source to be compiled	
aux_source_directory(../../../src/libraries/ LOG_LIB_SRCS)
aux_source_directory(../../../src/libraries/classString/ STRING_LIB_SRCS)
aux_source_directory(../../../src/libraries/data_structure/implement DATAST_LIB_SRCS)
aux_source_directory(../../../src/libraries/console CONSOLE1_LIB_SRCS)
aux_source_directory(../../../src/libraries/console/implement CONSOLE2_LIB_SRCS)
aux_source_directory(../../../src/libraries/console/portable CONSOLE3_LIB_SRCS)	
aux_source_directory(../../../src/libraries/log/implement LOG_LIB_SRCS)	
aux_source_directory(../../../src/libraries/log/portable LOG_PORTABLE_LIB_SRCS)	
aux_source_directory(../../../src/libraries/mbedTLS/library MBEDTLS_LIB_SRCS)	
set(LIB_SRCS 
    ${LOG_LIB_SRCS} 
	${STRING_LIB_SRCS} 
	${DATAST_LIB_SRCS} 
	${CONSOLE1_LIB_SRCS} 
	${CONSOLE2_LIB_SRCS} 
	${CONSOLE3_LIB_SRCS}
	${LOG_LIB_SRCS}
	${LOG_PORTABLE_LIB_SRCS}
	${MBEDTLS_LIB_SRCS}
	)

# Generate link library
set(LIBRARY_OUTPUT_PATH ../bin)
add_library (cutlass SHARED ${LIB_SRCS})
add_library (cutlass_static STATIC ${LIB_SRCS})
set_target_properties(cutlass PROPERTIES VERSION 1.0 )
set_target_properties(cutlass_static PROPERTIES OUTPUT_NAME "cutlass")