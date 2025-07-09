#include "MainWindow.hpp"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <QDebug>
#include "../receiver/VideoReceiver.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    initializeUI();
}

MainWindow::~MainWindow() {
    if (receiver) {
        receiver->stop();
        receiver->wait();
        delete receiver;
    }
}

void MainWindow::initializeUI()
{
    setWindowTitle("Video Monitor Client");
    resize(800, 600);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    statusLabel = new QLabel("Status: Disconnected", this);
    layout->addWidget(statusLabel);

    deviceComboBox = new QComboBox(this);
    // 假设有两个设备IP
    deviceComboBox->addItem("192.168.137.20");
    deviceComboBox->addItem("192.168.1.102");
    layout->addWidget(deviceComboBox);

    QPushButton *connectButton = new QPushButton("Connect Device", this);
    layout->addWidget(connectButton);
    connect(connectButton, &QPushButton::clicked, this, &MainWindow::connectDevice);

    QPushButton *viewHistoryButton = new QPushButton("View History", this);
    layout->addWidget(viewHistoryButton);
    connect(viewHistoryButton, &QPushButton::clicked, this, &MainWindow::viewHistory);

    videoStreamLabel = new QLabel(this);
    layout->addWidget(videoStreamLabel);
}

void MainWindow::updateStatus(const QString &status)
{
    statusLabel->setText("Status: " + status);
}

void MainWindow::showVideoStream(const QImage &frame)
{
    videoStreamLabel->setPixmap(QPixmap::fromImage(frame));
}

void MainWindow::onStartButtonClicked() {
    QString deviceIP = deviceComboBox->currentText(); // 获取当前选中的IP
    if (deviceIP.isEmpty()) {
        QMessageBox::warning(this, "提示", "请选择设备IP");
        return;
    }
    // 连接服务端
    if (networkManager.connectDevice(deviceIP.toStdString())) {
        QMessageBox::information(this, "连接成功", "已连接到设备: " + deviceIP);
    } else {
        QMessageBox::warning(this, "连接失败", "无法连接到设备: " + deviceIP);
    }
}

void MainWindow::connectDevice()
{
    if (receiver) {
        receiver->stop();
        receiver->wait();
        delete receiver;
        receiver = nullptr;
    }
    QString ip = deviceComboBox->currentText();
    receiver = new VideoReceiver(ip.toStdString(), 12345, this);
    connect(receiver, &VideoReceiver::frameReceived, this, &MainWindow::showVideoStream);
    receiver->start();
    updateStatus("Connected to " + ip);
}

void MainWindow::viewHistory()
{
    // Logic to view history data
    QMessageBox::information(this, "View History", "Displaying history data...");
}


void MainWindow::onStopButtonClicked() {
    // 停止视频流的逻辑
    qDebug() << "Stop button clicked";
}

void MainWindow::onDeviceChanged(int index) {
    // 设备切换逻辑
    qDebug() << "Device changed to index:" << index;
}

