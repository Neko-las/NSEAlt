//
// Created by nicolas on 8/25/24.
//

#ifndef NSEALGORITHM_H
#define NSEALGORITHM_H

#include <string>
#include <vector>
#include <sstream>

struct Message {
    int32_t hop_count;
    uint64_t magic_code;
    int64_t round_time;
    int32_t proximity;
    unsigned char pub_key[260];
    PoW pow;
    std::string sign;

    //Function to serialize the Message into a string for signing or transmission
    std::string serialize() const {
        std::stringstream ss;

        ss.write(reinterpret_cast<const char*>(&hop_count), sizeof(hop_count));
        ss.write(reinterpret_cast<const char*>(&magic_code), sizeof(magic_code));
        ss.write(reinterpret_cast<const char*>(&round_time), sizeof(round_time));
        ss.write(reinterpret_cast<const char*>(&proximity), sizeof(proximity));
        ss.write(reinterpret_cast<const char*>(pub_key), sizeof(pub_key));
        ss.write(reinterpret_cast<const char*>(&pow), sizeof(pow));

        return ss.str();
    }

    //Function to serialize for network transmission
    std::string serialize_for_network() const {
        std::string serialized_msg = serialize();
        serialized_msg += sign;
        return serialized_msg;
    }
};

class NSEHandler {
public:
    bool validate_query(const std::vector<char>& query_data);
    std::string nse_estimate();
    void append_msg_to_history();
    void create_round_msg();

    std::string getMsg();

private:
    int m_est_peer_count;
    double m_est_std_deviation;
    Message m_msg;

};

#endif //NSEALGORITHM_H
