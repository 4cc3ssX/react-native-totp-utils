#ifndef TOTPUTILS_H
#define TOTPUTILS_H

#include <jsi/jsi.h>
#include <random>
#include <string>
#include <chrono>
#include "hmac/hmac_sha1.hpp"

using namespace facebook::jsi;

const int DEFAULT_KEY_LENGTH = 16;
const int DEFAULT_DIGITS = 6;
const int DEFAULT_TIMESTEP = 30;
const int DEFAULT_WINDOW = 1;


namespace totputils {
  void install(Runtime& jsiRuntime);

  std::string generateSecretKey(int length = DEFAULT_KEY_LENGTH);

  std::string generateOTP(const std::string &secretKey, int digits = DEFAULT_DIGITS, int timeStep = DEFAULT_TIMESTEP);

  bool validateOTP(const std::string &secretKey, const std::string &otp, int digits = DEFAULT_DIGITS, int timeStep = DEFAULT_TIMESTEP, int window = DEFAULT_WINDOW);
}

#endif /* TOTPUTILS_H */
