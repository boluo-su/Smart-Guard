#include "DeviceManager.hpp"
#include <vector>
#include <string>

class Device {
public:
    std::string id;
    std::string name;
    bool isBound;

    Device(const std::string& id, const std::string& name) : id(id), name(name), isBound(false) {}
};

class DeviceManager {
private:
    std::vector<Device> devices;
    Device* currentDevice;

public:
    DeviceManager() : currentDevice(nullptr) {}

    void addDevice(const std::string& id, const std::string& name) {
        devices.emplace_back(id, name);
    }

    bool bindDevice(const std::string& id) {
        for (auto& device : devices) {
            if (device.id == id) {
                device.isBound = true;
                currentDevice = &device;
                return true;
            }
        }
        return false;
    }

    bool switchDevice(const std::string& id) {
        for (auto& device : devices) {
            if (device.id == id && device.isBound) {
                currentDevice = &device;
                return true;
            }
        }
        return false;
    }

    Device* getCurrentDevice() const {
        return currentDevice;
    }

    const std::vector<Device>& getDevices() const {
        return devices;
    }
};