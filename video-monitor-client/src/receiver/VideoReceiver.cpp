#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "../receiver/VideoReceiver.hpp"

VideoReceiver::VideoReceiver(const std::string& ip, int port, QObject *parent)
    : QThread(parent), ip_(ip), port_(port), running_(true) {}

void VideoReceiver::stop() {
    running_ = false;
}

void VideoReceiver::run() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_);
    inet_pton(AF_INET, ip_.c_str(), &serv_addr.sin_addr);

    if (::connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        return;
    }

    while (running_) {
        int len = 0;
        int received = recv(sockfd, &len, sizeof(len), MSG_WAITALL);
        if (received != sizeof(len) || len <= 0) break;

        std::vector<uchar> buf(len);
        int total = 0;
        while (total < len) {
            int n = recv(sockfd, buf.data() + total, len - total, 0);
            if (n <= 0) break;
            total += n;
        }
        if (total != len) break;

        cv::Mat img = cv::imdecode(buf, cv::IMREAD_COLOR);
        if (!img.empty()) {
            cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
            QImage qimg(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
            emit frameReceived(qimg.copy());
        }
    }
    close(sockfd);
}