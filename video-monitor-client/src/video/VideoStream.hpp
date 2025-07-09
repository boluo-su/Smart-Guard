#ifndef VIDEO_STREAM_HPP
#define VIDEO_STREAM_HPP

#include <string>
#include <opencv2/opencv.hpp>

class VideoStream {
public:
    VideoStream();
    VideoStream(const std::string& deviceUrl);
    ~VideoStream();

    void startStream();
    void stopStream();
    cv::Mat getVideoFrame();

private:
    std::string deviceUrl;
    bool isStreaming;
};

#endif // VIDEO_STREAM_HPP