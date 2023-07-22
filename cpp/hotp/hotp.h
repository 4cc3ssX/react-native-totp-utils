#ifndef HOTP_H
#define HOTP_H

#include <string>
#include <iomanip>
#include <sstream>
#include <openssl/hmac.h>

std::string HOTP(const std::vector<uint8_t> &secretKey, uint64_t counter, int digits);

#endif /* HOTP_H */
