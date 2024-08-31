//
// Created by nicolas on 8/25/24.
//

#include "util/ConfigParser.h"

bool ConfigParser::parse(const std::string &filePath) {
    std::ifstream file(filePath);
    if(!file.is_open()) {
        std::cerr << "Unable to open config file: " << filePath << std::endl;
        return false;
    }

    std::string line, currentSection;

    while (std::getline(file, line)) {

        line.erase(0,line.find_first_not_of("\t"));
        line.erase(line.find_first_not_of("\t") + 1);

        if (line.empty() || line[0] == ';' || line[0] == '#') {
            continue;
        }

        if (line[0] == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() -2);
        }

        else if (!currentSection.empty()) {
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) {
                std::string key = line.substr(0,delimiterPos);
                std::string value = line.substr(delimiterPos +1);

                key.erase(0,key.find_first_not_of(" \t"));
                key.erase(key.find_first_not_of(" \t") +1);
                value.erase(0,value.find_first_not_of(" \t"));
                value.erase(value.find_first_not_of(" \t") +1);

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



