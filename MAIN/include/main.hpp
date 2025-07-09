#pragma once

//////////////// C++标准库 //////////////////////////////
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

//////////////// C标准库 ////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>    // 共享内存
#include <sys/sem.h>    // 信号量集
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>




//////////////// OpenCV头文件 ///////////////////////////
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/features2d.hpp>

 

#include "ADC.hpp"
#include "HW_GPIO.hpp"
#include "SHT30.hpp"
#include "Cam.hpp"
#include "Uart.hpp"


using namespace cv;
using namespace cv::dnn;
using namespace std;
