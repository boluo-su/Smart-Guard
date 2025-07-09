#include "NetworkManager.hpp"
#include <iostream>
#include <cstring>

NetworkManager::NetworkManager() : sockfd(-1) {}

NetworkManager::~NetworkManager() {
    disconnectDevice();
}

bool NetworkManager::connectDevice(const std::string& deviceIP, int port) {
    if (sockfd != -1) disconnectDevice();

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket creation failed\n";
        return false;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, deviceIP.c_str(), &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address\n";
        return false;
    }

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed\n";
        close(sockfd);
        sockfd = -1;
        return false;
    }
    std::cout << "Connected to " << deviceIP << ":" << port << std::endl;
    return true;
}

void NetworkManager::disconnectDevice() {
    if (sockfd != -1) {
        close(sockfd);
        sockfd = -1;
        std::cout << "Disconnected\n";
    }
}

bool NetworkManager::sendData(const std::string& data) {
    if (sockfd == -1) return false;
    ssize_t sent = send(sockfd, data.c_str(), data.size(), 0);
    return sent == (ssize_t)data.size();
}

std::string NetworkManager::receiveData() {
    if (sockfd == -1) return "";
    char buffer[1024] = {0};
    ssize_t len = recv(sockfd, buffer, sizeof(buffer)-1, 0);
    if (len > 0) return std::string(buffer, len);
    return "";
}