cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER /opt/loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.3-1/bin/loongarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /opt/loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.3-1/bin/loongarch64-linux-gnu-g++)

project(main)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/opt/loongson-gnu-toolchain-8.3-x86_64-loongarch64-linux-gnu-rc1.3-1/loongarch64-linux-gnu/sysroot/usr/include/)


include_directories(/home/su/work/opencv-4.5.5/install/include/opencv4)

find_library(OPENCV_CORE        opencv_core         /home/su/work/opencv-4.5.5/install/lib)
find_library(OPENCV_IMGPROC     opencv_imgproc      /home/su/work/opencv-4.5.5/install/lib) 
find_library(OPENCV_HIGHGUI     opencv_highgui      /home/su/work/opencv-4.5.5/install/lib) 
find_library(OPENCV_VIDEOIO     opencv_videoio      /home/su/work/opencv-4.5.5/install/lib)
find_library(OPENCV_IMGCODECS   opencv_imgcodecs    /home/su/work/opencv-4.5.5/install/lib)
find_library(OPENCV_OBJDETECT   opencv_objdetect    /home/su/work/opencv-4.5.5/install/lib)
find_library(OPENCV_DNN         opencv_dnn          /home/su/work/opencv-4.5.5/install/lib)
find_library(OPENCV_CALIB3D     opencv_calib3d      /home/su/work/opencv-4.5.5/install/lib)
find_library(OPENCV_FEATURES2D  opencv_features2d   /home/su/work/opencv-4.5.5/install/lib)
find_library(OPENCV_FLANN       opencv_flann        /home/su/work/opencv-4.5.5/install/lib)





add_executable(main ${SRC})

target_link_libraries(main PUBLIC ${OPENCV_CORE} ${OPENCV_IMGPROC} ${OPENCV_HIGHGUI} ${OPENCV_VIDEOIO} ${OPENCV_IMGCODECS} ${OPENCV_OBJDETECT} ${OPENCV_DNN} ${OPENCV_FEATURES2D} ${OPENCV_CALIB3D}  ${OPENCV_FLANN}) 
target_link_libraries(main PUBLIC pthread)
