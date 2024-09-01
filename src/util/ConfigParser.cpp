//
// Created by nicolas on 8/25/24.
//

#include "util/ConfigParser.h"

bool ConfigParser::parse(const std::string &filePath) {
    std::ifstream file(filePath);

    std::string line;
    std::string currentSection;

    while (std::getline(file, line)) {
        // Remove whitespace from start and end of line
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

        // Skip empty lines and comments
        if (line.empty() || line[0] == ';' || line[0] == '#') {
            continue;
        }

        // If the line is a section header
        if (line[0] == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        // If the line is a key-value pair
        else {
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);

                // Remove whitespace from key and value
                key.erase(0, key.find_first_not_of(" \t\n\r\f\v"));
                key.erase(key.find_last_not_of(" \t\n\r\f\v") + 1);

                value.erase(0, value.find_first_not_of(" \t\n\r\f\v"));
                value.erase(value.find_last_not_of(" \t\n\r\f\v") + 1);

                m_configData[currentSection][key] = value;
            }
        }
    }

    file.close();
    return true;
}

std::string ConfigParser::get(const std::string &section, const std::string &key) const {
    auto secIt = m_configData.find(section);
    if(secIt != m_configData.end()) {
        auto keyIt = secIt->second.find(key);
        if(keyIt != secIt-> second.end()) {
            return keyIt->second;
        }
    }
    return "";
}

int ConfigParser::getInt(const std::string &section, const std::string &key) const {
    std::string value = get(section,key);
    return value.empty() ? 0: std::stoi(value);
}

ConfigData ConfigParser::get() const {
    ConfigData data {};
    data.gossip_cache_size = getInt("gossip","cache_size");
    data.gossip_bootstrapper_adress = get("gossip","bootstrapper");
    data.gossip_listen_address = get("gossip","listen_address");
    data.gossip_max_connections = getInt("gossip","max_connections");

    data.nse_listen_adress = get("nse","listen_address");
    data.nse_api_adress = get("nse","api_adress");
    data.mockup_est_max = getInt("nse","mockup_estimate_max");
    data.mockup_dev_max = getInt("nse","mockup_deviation_max");
    data.pow_num_bits = getInt("nse","pow_num_bits");
    return data;
}



