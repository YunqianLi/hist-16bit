# cmake needs this line
cmake_minimum_required(VERSION 3.12)

# Define project name
project(voc_detect LANGUAGES CXX)

# default is release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()


# Find Python
find_package(Python REQUIRED COMPONENTS Development)

# Include Python headers
include_directories(${Python_INCLUDE_DIRS})

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
# set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/opencv3.4.0/")
if (WIN32)
	message(STATUS "Now is windows")
	set(OpenCV_DIR "D:/sdk/opencv-4.6.0/build/")
else()
	message(STATUS "Now is linux")
	#set(OpenCV_DIR "/media/hdd1/lyq/opencv-3.3.1/build/")
	#set(OpenCV_DIR "/data/opencv/INSTALL/")
	set(OpenCV_DIR "/usr/lib/aarch64-linux-gnu/")
endif()
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(/usr/include/opencv4)
#set(OpenCV_LIB ${OpenCV_DIR}/lib/x86_64-linux-gnu/libopencv_world.so)
list(APPEND OpenCV_LIB 
	${OpenCV_DIR}/libopencv_photo.so
	${OpenCV_DIR}/libopencv_ml.so
	${OpenCV_DIR}/libopencv_flann.so
	${OpenCV_DIR}/libopencv_gapi.so
	${OpenCV_DIR}/libopencv_stitching.so
	${OpenCV_DIR}/libopencv_features2d.so
	${OpenCV_DIR}/libopencv_core.so
	${OpenCV_DIR}/libopencv_video.so
	${OpenCV_DIR}/libopencv_imgproc.so
	${OpenCV_DIR}/libopencv_imgcodecs.so
	${OpenCV_DIR}/libopencv_highgui.so
	${OpenCV_DIR}/libopencv_calib3d.so
	${OpenCV_DIR}/libopencv_objdetect.so
	${OpenCV_DIR}/libopencv_videoio.so
	${OpenCV_DIR}/libopencv_dnn.so)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
# message(STATUS "OpenCV library status:")
# message(STATUS "    config: ${OpenCV_DIR}")
# message(STATUS "    version: ${OpenCV_VERSION}")
# message(STATUS "    libraries: ${OpenCV_LIBS}")
# message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# find thread lib
find_package(Threads)

# include directories for search headers
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/alg
)

# Get all sources in the alg
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/alg SRC_LIST)


########################################################
# Create a library
########################################################

# Generate the shared library from the library sources
if (WIN32)
	set(PROJECT_LIBRARY_NAME "libalg")
else()
	set(PROJECT_LIBRARY_NAME "alg")
endif()
add_library(${PROJECT_LIBRARY_NAME} SHARED ${SRC_LIST})
# see https://zhuanlan.zhihu.com/p/212594841
target_compile_definitions(${PROJECT_LIBRARY_NAME} PRIVATE ALG_EXPORTS)
target_compile_definitions(${PROJECT_LIBRARY_NAME} PRIVATE COMMON_EXPORTS)

# Link your application with OpenCV libraries
# target_link_libraries(${PROJECT_LIBRARY_NAME} PRIVATE ${OpenCV_LIBS} )
target_link_libraries(${PROJECT_LIBRARY_NAME} PRIVATE ${OpenCV_LIB} )
target_link_libraries(${PROJECT_LIBRARY_NAME} PRIVATE ${Python_LIBRARIES})



########################################################
# Create an executable
########################################################
# Declare the executable target built from given sources
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

# Link your application with OpenCV libraries
# target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS} )
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIB} )

# Link your application with Thread libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_THREAD_LIBS_INIT} ) 

# Link your application with the library generated above
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBRARY_NAME} ) 
target_link_libraries(${PROJECT_NAME} PRIVATE ${Python_LIBRARIES})
