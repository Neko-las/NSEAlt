//
// Created by nicolas on 8/25/24.
//

#ifndef NSEALGORITHM_H
#define NSEALGORITHM_H

#include <string>
#include <vector>

class NSEHandler {
public:
    bool validate_query(const std::vector<char>& query_data);
    std::string nse_estimate();
    void append_msg_to_history();
    void create_round_msg();

private:
    int m_est_peer_count;
    double m_est_std_deviation;
};

#endif //NSEALGORITHM_H
