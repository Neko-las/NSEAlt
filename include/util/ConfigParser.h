//
// Created by nicolas on 8/25/24.
//

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H
#include<string>
#include<fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class ConfigParser {
public:
    bool parse(const std::string& filePath);

    std::string get(const std::string& section, const std::string& key) const;
    int getInt(const std::string& section, const std::string& key) const;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_configData;
};

#endif //CONFIGPARSER_H
