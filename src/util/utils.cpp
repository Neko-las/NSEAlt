//
// Created by nicolas on 9/1/24.
//

#include "util/utils.h"

int create_flood_delay(const std::vector<std::string> &msg_history, int cur_prox, int freq) {
    int prev_prox = msg_history.empty() ? 0 : std::stoi(msg_history.back().substr(10,3));
    double delay = (freq / 2.0) - ((freq / M_PI) * std::atan(cur_prox -prev_prox));
    return static_cast<int>(delay);
}

int create_processing_delay(const std::vector<std::string>& msg_history, int proximity, int freq, int max_hop_count) {
    int network_diameter = 15;
    for(const auto& dict :msg_history) {
        int hop_count = std::stoi(dict.substr(0,2));
        if (network_diameter > hop_count) network_diameter = hop_count;
    }
    network_diameter = max_hop_count + 1 - network_diameter;
    int cur_prox = proximity;

    int delay1 = create_flood_delay(msg_history, cur_prox -1, freq);
    int delay2 = create_flood_delay(msg_history, cur_prox,freq);

    int delay_range_upper_bound = (delay1 - delay2) / network_diameter;
    std::srand(std::time(nullptr));
    int delay = std::rand() % delay_range_upper_bound;
    return delay;
}

