//
// Created by nicolas on 9/2/24.
//

#ifndef POW_H
#define POW_H

struct PoW {
    std::string Time;
    std::string RandomNumber;
    std::string Hash;
};

PoW createPoW(int num_matches);
bool validateHash(const std::string& hash, int num_matches);
bool validatePoW(const std::string& cur_round, const std::string& msg_round, const PoW& pow, int num_matches);
Json::Value powToJson(const PoW& pow);
PoW jsonToPoW(const Json::Value& json);

#endif //POW_H
