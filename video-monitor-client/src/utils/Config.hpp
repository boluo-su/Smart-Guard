#ifndef _CONFIG_HPP_
#define CONFIG_HPP

#include <string>
#include <map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Config {
public:
    Config(const std::string& configFilePath);
    bool loadConfig();
    bool saveConfig();
    std::string getValue(const std::string& key);
    void setValue(const std::string& key, const std::string& value);
    json getConfigData() const;
    void setConfigData(const json& newConfigData);


private:
    std::string configFilePath;
    json configData;

    void parseConfigFile();
    void writeConfigFile();
};

#endif // CONFIG_HPP