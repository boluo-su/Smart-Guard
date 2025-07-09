#include "main.hpp"

int Temp1 = 0;
int Humi1 = 0;
double adc = 0 ;

int CameraDemo()
{
    // 1. 打开 FrameBuffer 设备
    int fb_fd = open("/dev/fb0", O_RDWR);
    if (fb_fd < 0) {
        perror("Error: Cannot open /dev/fb0");
        return -1;
    }

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(12345);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);
    std::cout << "Server listening on 12345\n";

    int client_fd = accept(server_fd, nullptr, nullptr);
    std::cout << "Client connected\n";

    // 2. 获取屏幕信息
    struct fb_var_screeninfo vinfo;
    ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);
    int width = vinfo.xres;
    int height = vinfo.yres;
    int bpp = vinfo.bits_per_pixel / 8;  // Bytes per pixel (通常 4 for RGB32)

    // 3. 映射 FrameBuffer 到内存
    char *fb_data = (char *)mmap(0, width * height * bpp, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);

    // 4. 加载 OpenCV 图像并调整大小
    cv::CascadeClassifier faceDetector;
    std::string modelPath = "/home/loongson/install/share/opencv4/haarcascades/haarcascade_frontalface_default.xml";  // 模型路径

    if (!faceDetector.load(modelPath)) {
        std::cerr << "错误：无法加载人脸检测模型！" << std::endl;
        return -1;
    }
    // 2. 打开视频源（0表示摄像头，或替换为视频文件路径）
    cv::VideoCapture cap(0);  // 若使用视频文件：cv::VideoCapture cap("video.mp4");

    cv::Mat frame, grayFrame,smallFrame;
    while(1)
    {
    cap.read(frame);  // 循环读取每一帧
    float scaleFactor = 0.1; // 缩小至70%
    cv::resize(frame, smallFrame, cv::Size(), scaleFactor, scaleFactor, cv::INTER_AREA);
        // // 3. 图像预处理
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(grayFrame, grayFrame);

        // // 4. 人脸检测
        std::vector<cv::Rect> faces;
        faceDetector.detectMultiScale(
            grayFrame, 
            faces, 
            1.4,     // 缩放因子（不可等于1)
            2,       // 邻域阈值
            0, 
            cv::Size(30, 30)
        );

        // 5. 在原图上绘制人脸框
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
            cv::putText(frame, "Face", cv::Point(face.x, face.y - 10),
                        cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
        }

    cv::resize(frame, frame, cv::Size(width, height));  // 调整到屏幕分辨率
    cv::cvtColor(frame, frame, cv::COLOR_BGR2BGRA);    // 转换格式（FBG 通常用 BGRA）

    // 5. 将图像数据写入 FrameBuffer
    if(frame.isContinuous()){
    memcpy(fb_data, frame.data, width * height * bpp);}
    
    std::vector<uchar> buf;
    cv::imencode(".jpg", frame, buf);

    int len = buf.size();
        // 先发长度
    if (send(client_fd, &len, sizeof(len), 0) != sizeof(len)) 
        continue;
        // 再发数据
    if (send(client_fd, buf.data(), len, 0) != len) 
        continue;

        // 控制帧率
    usleep(33000); // ~30fps

    
    }
    // 6. 清理

    return 0;
}