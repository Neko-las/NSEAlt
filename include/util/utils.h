//
// Created by nicolas on 9/1/24.
//

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <boost/asio.hpp>
#include <openssl/sha.h>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>
#include <ctime>

std::chrono::system_clock::time_point get_next_hour();

int create_flood_delay(const std::vector<std::string>& msg_history, int cur_prox, int freq);

int create_processing_delay(const std::vector<std::string>& msg_history, int proximity, int freq, int max_hop_count);

#endif //UTILS_H
