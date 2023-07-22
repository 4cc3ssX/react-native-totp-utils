#ifndef TOTPUTILS_H
#define TOTPUTILS_H

#include <jsi/jsi.h>
#include <string>

using namespace facebook::jsi;

const int DEFAULT_DIGITS = 6;
const int DEFAULT_TIMESTEP = 30;
const int DEFAULT_WINDOW = 1;

namespace totputils {
  void install(Runtime& jsiRuntime);

  std::string generateSecretKey();

  std::string generateTOTP(const std::string &secretKey, int digits = DEFAULT_DIGITS, int timeStep = DEFAULT_TIMESTEP);

  bool validateTOTP(const std::string &secretKey, const std::string &otp, int digits = DEFAULT_DIGITS, int timeStep = DEFAULT_TIMESTEP, int window = DEFAULT_WINDOW);
}

#endif /* TOTPUTILS_H */
