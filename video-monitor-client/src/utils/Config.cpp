#include "Config.hpp"
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

Config::Config(const std::string& configFilePath) : configFilePath(configFilePath) {}

bool Config::loadConfig() {
    std::ifstream configFile(configFilePath);
    if (!configFile.is_open()) {
        std::cerr << "Could not open the config file: " << configFilePath << std::endl;
        return false;
    }

    try {
        configFile >> configData;
    } catch (const json::parse_error& e) {
        std::cerr << "Error parsing config file: " << e.what() << std::endl;
        return false;
    }

    configFile.close();
    return true;
}

bool Config::saveConfig() {
    std::ofstream configFile(configFilePath);
    if (!configFile.is_open()) {
        std::cerr << "Could not open the config file for writing: " << configFilePath << std::endl;
        return false;
    }

    configFile << configData.dump(4); // Pretty print with 4 spaces
    configFile.close();
    return true;
}

json Config::getConfigData() const {
    return configData;
}

void Config::setConfigData(const json& newConfigData) {
    configData = newConfigData;
}