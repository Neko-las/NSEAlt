//
// Created by nicolas on 9/1/24.
//

#ifndef CRYPTOUTILS_H
#define CRYPTOUTILS_H

#include <sstream>
#include <openssl/sha.h>

std::string sha256(const std::string &str);
std::string sha256_hex_digest(const std::string& input);

#endif //CRYPTOUTILS_H
