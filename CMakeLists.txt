# created by bacox 2010
cmake_minimum_required(VERSION 2.8.7)
# ---[ Multiface project
project(multi-face-detector)

find_package (Eigen3 3.3 REQUIRED)
find_package(OpenCV REQUIRED )
# Including caffe by cmake will break my search paths
#find_package(Caffe REQUIRED)
include(FindProtobuf)
find_package(Protobuf REQUIRED)
message(STATUS "${OpenCV_FOUND}")
message(STATUS "${Eigen3_FOUND}")
message(STATUS "${Caffe_LIBRARY}")
message(STATUS "proto ${Protobuf_FOUND}")
message(STATUS "proto_loc ${PROTOBUF_LIBRARY}")
include_directories(${Caffe_INCLUDE_DIRS})
# Including glog by cmake will break my search paths
#find_package(Glog REQUIRED)
add_definitions( -DBOOST_ALL_DYN_LINK )
find_package( Boost COMPONENTS system filesystem REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
set(CURRENT_SRC_BOOST_LIBS ${Boost_LIBRARIES} )

SET(LINK_FLAGS "-L/usr/local/lib/ -lprotobuf -pthread -lpthread -lboost_system")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")

add_executable(${PROJECT_NAME} integrated_caffe/main.cpp integrated_caffe/face_detection.cpp)

target_link_libraries (${PROJECT_NAME}
        # Use pixed paths for now
        /usr/lib/x86_64-linux-gnu/libcaffe.so
        ${PROTOBUF_LIBRARY}
        # Use pixed paths for now
        /usr/local/lib/libprotobuf.so
        ${OpenCV_LIBRARIES}
        ${Boost_LIBRARIES}
        # Use pixed paths for now
        /usr/lib/x86_64-linux-gnu/libglog.so
        )

function(COPY_RESOURCE FILE_NAME)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}")
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME} ${CMAKE_BINARY_DIR}/${FILE_NAME} COPYONLY)
    else()
        MESSAGE(SEND_ERROR "Unable to copy ${FILE_NAME} from ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME}. Missing file?")
    endif()
endfunction()

# Copy the needed resources to run
copy_resource(face_full_conv.prototxt)
copy_resource(face_full_conv2.prototxt)
copy_resource(face_full_conv.caffemodel)
copy_resource(naassom-azevedo-cropped.jpg)


