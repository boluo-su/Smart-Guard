#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <string>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

class NetworkManager {
public:
    NetworkManager();
    ~NetworkManager();

    bool connectDevice(const std::string& deviceIP, int port = 12345);
    void disconnectDevice();
    bool sendData(const std::string& data);
    std::string receiveData();

private:
    int sockfd;
};

#endif // NETWORKMANAGER_HPP