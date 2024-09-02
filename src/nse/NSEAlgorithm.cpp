//
// Created by nicolas on 8/25/24.
//

#include "nse/NSEAlgorithm.h"
bool NSEHandler::validate_query(const std::vector<char> &query_data) {
    return true;
}

std::string NSEHandler::nse_estimate() {
    return "NSE Estimate: " + std::to_string(m_est_peer_count) + " peers, std Deviation: " + std::to_string(m_est_std_deviation);
}

std::string NSEHandler::getMsg() {
    return m_msg;
}



