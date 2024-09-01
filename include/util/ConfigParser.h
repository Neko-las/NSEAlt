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


struct ConfigData {
    //Gossip Data
    int gossip_cache_size;
    int gossip_max_connections;
    std::string gossip_bootstrapper_adress;
    std::string gossip_listen_address;

    //NSE Data
    std::string nse_listen_adress;
    std::string nse_api_adress;
    int mockup_est_max;
    int mockup_dev_max;
    int pow_num_bits;
};

class ConfigParser {
public:
    bool parse(const std::string& filePath);

    std::string get(const std::string& section, const std::string& key) const;
    int getInt(const std::string& section, const std::string& key) const;

    ConfigData get()const;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_configData;
};

#endif //CONFIGPARSER_H
