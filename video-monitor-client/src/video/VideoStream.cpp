#include "VideoStream.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>

VideoStream::VideoStream() : isStreaming(false) {}

void VideoStream::startStream() {
    if (!isStreaming) {
        // Initialize video capture and start streaming
        std::cout << "Starting video stream..." << std::endl;
        isStreaming = true;
        // Additional code to start video capture
    }
}

void VideoStream::stopStream() {
    if (isStreaming) {
        // Stop video capture
        std::cout << "Stopping video stream..." << std::endl;
        isStreaming = false;
        // Additional code to stop video capture
    }
}

cv::Mat VideoStream::getVideoFrame() {
    cv::Mat frame;
    if (isStreaming) {
        // Capture a frame from the video stream
        // Additional code to retrieve the frame
    }
    return frame;
}