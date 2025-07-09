#pragma once
#include <QThread>
#include <QImage>
#include <atomic>
#include <string>

class VideoReceiver : public QThread {
    Q_OBJECT
public:
    VideoReceiver(const std::string& ip, int port, QObject *parent = nullptr);
    void stop();

signals:
    void frameReceived(const QImage &img);

protected:
    void run() override;

private:
    std::string ip_;
    int port_;
    std::atomic<bool> running_;
};