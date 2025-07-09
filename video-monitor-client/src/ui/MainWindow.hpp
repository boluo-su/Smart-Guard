#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTimer>
#include <QThread>
#include <QImage>
#include <atomic>
#include "network/NetworkManager.hpp"

class VideoReceiver;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    
    void updateStatus(const QString &status);
    void showVideoStream(const QImage &frame);
private slots:
    void connectDevice();
    void viewHistory();

private:
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QLabel *statusLabel;
    QPushButton *startButton;
    QPushButton *stopButton;
    QComboBox *deviceComboBox;
    QTimer *updateTimer;
    QLabel *videoStreamLabel;
    NetworkManager networkManager;
    VideoReceiver *receiver = nullptr;

private slots:
    void onStartButtonClicked();
    void onStopButtonClicked();
    void onDeviceChanged(int index);
    void initializeUI();
};

#endif // MAINWINDOW_HPP