//
// Created by nicolas on 8/25/24.
//

#include "security/ProofofWork.h"

#include "security/PoW.h"
#include <sstream>
#include <iomanip>
#include <random>
#include <openssl/sha.h>
#include <iostream>

PoW createPoW(int num_matches) {
    while (true) {
        // Create a random 64-bit integer
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dis;
        uint64_t random_number = dis(gen);

        // Get the current time
        std::time_t t = std::time(nullptr);
        std::tm* now = std::gmtime(&t);
        char time_buffer[20];
        strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", now);

        // Concatenate the random number and time
        std::string attempt = std::to_string(random_number) + time_buffer;

        // Hash the attempt
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, attempt.c_str(), attempt.size());
        SHA256_Final(hash, &sha256);

        // Convert the hash to a string
        std::stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            ss << std::setw(2) << std::setfill('0') << std::hex << (int)hash[i];
        }
        std::string hash_str = ss.str();

        // Validate the hash
        if (validateHash(hash_str, num_matches)) {
            PoW pow;
            pow.Time = std::string(time_buffer);
            pow.RandomNumber = std::to_string(random_number);
            pow.Hash = hash_str;
            return pow;
        }
    }
}

bool validateHash(const std::string& hash, int num_matches) {
    return hash.compare(0, num_matches, std::string(num_matches, '0')) == 0;
}

bool validatePoW(const std::string& cur_round, const std::string& msg_round, const PoW& pow, int num_matches) {
    std::tm tm_msg_round = {};
    std::tm tm_pow_time = {};
    strptime(msg_round.c_str(), "%Y-%m-%d %H:%M:%S", &tm_msg_round);
    strptime(pow.Time.c_str(), "%Y-%m-%d %H:%M:%S", &tm_pow_time);

    // Truncate to hour precision
    tm_msg_round.tm_sec = tm_pow_time.tm_sec = 0;
    tm_msg_round.tm_min = tm_pow_time.tm_min = 0;

    if (std::mktime(&tm_msg_round) != std::mktime(&tm_pow_time) && cur_round != pow.Time) {
        return false;
    }

    std::string attempt = pow.RandomNumber + pow.Time;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, attempt.c_str(), attempt.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::setw(2) << std::setfill('0') << std::hex << (int)hash[i];
    }

    return ss.str() == pow.Hash && validateHash(ss.str(), num_matches);
}

