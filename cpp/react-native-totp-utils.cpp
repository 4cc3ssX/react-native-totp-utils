#include "react-native-totp-utils.h"

#include <chrono>
#include <random>
#include "base32.cpp"
#include "hotp.h"

namespace totputils
{
	void install(Runtime &jsiRuntime)
	{
		// TotpUtils.generateSecretKey(...)
		auto totpUtilsGenerateSecretKey = Function::createFromHostFunction(
			jsiRuntime, PropNameID::forAscii(jsiRuntime, "generateSecretKey"), 0,
			[](Runtime &runtime, const Value &thisValue, const Value *arguments,
			   size_t count) -> Value
			{
				std::string secret = generateSecretKey();
				return Value(String::createFromUtf8(runtime, secret));
			});

		jsiRuntime.global().setProperty(jsiRuntime, "totpUtilsGenerateSecretKey", std::move(totpUtilsGenerateSecretKey));

		// TotpUtils.generateOTP(...)
		auto totpUtilsGenerateTOTP = Function::createFromHostFunction(
			jsiRuntime, PropNameID::forAscii(jsiRuntime, "generateTOTP"), 3,
			[](Runtime &runtime, const Value &thisValue, const Value *arguments,
			   size_t count) -> Value
			{
				std::string secret = arguments[0].toString(runtime).utf8(runtime);
				int digits = arguments[1].getNumber();
				int timeStep = arguments[2].getNumber();
				std::string otp = generateTOTP(secret, digits, timeStep);
				return Value(String::createFromUtf8(runtime, otp));
			});

		jsiRuntime.global().setProperty(jsiRuntime, "totpUtilsGenerateTOTP", std::move(totpUtilsGenerateTOTP));

		// TotpUtils.validateOTP(...)
		auto totpUtilsValidateTOTP = Function::createFromHostFunction(
			jsiRuntime, PropNameID::forAscii(jsiRuntime, "validateTOTP"), 5,
			[](Runtime &runtime, const Value &thisValue, const Value *arguments,
			   size_t count) -> Value
			{
				std::string secret = arguments[0].toString(runtime).utf8(runtime);
				std::string otp = arguments[1].toString(runtime).utf8(runtime);
				int digits = arguments[2].getNumber();
				int timeStep = arguments[3].getNumber();
				int window = arguments[4].getNumber();
				bool isValid = validateTOTP(secret, otp, digits, timeStep, window);
				return Value(isValid);
			});

		jsiRuntime.global().setProperty(jsiRuntime, "totpUtilsValidateTOTP", std::move(totpUtilsValidateTOTP));
	}

	std::string generateSecretKey()
	{
		const int keyLength = 20; // RFC 6238 recommends a key length of 160 bits (20 bytes)

		// Cryptographically secure random number generator
		std::random_device rd;
		std::uniform_int_distribution<uint8_t> distribution(0, 255);

		// Generate binary data and encode it to Base32 directly
		std::string secretKey;
		secretKey.reserve((keyLength * 8 + 4) / 5); // Reserve space for Base32 encoding
		for (int i = 0; i < keyLength; ++i)
		{
			uint8_t randomByte = distribution(rd);
			secretKey.push_back(base32_chars[randomByte & 0x1F]);
			if (i % 5 == 4)
				randomByte >>= 3;
		}

		return secretKey;
	}

	std::string generateTOTP(const std::string &secretKey, int digits, int timeStep)
	{
		// Decode the secret key from Base32 to bytes
		std::vector<uint8_t> decodedSecretKey;
		for (char c : secretKey)
		{
			auto it = std::find(base32_chars.begin(), base32_chars.end(), c);
			if (it == base32_chars.end())
			{
				throw std::invalid_argument("Invalid Base32 character in secret key.");
			}
			decodedSecretKey.push_back(std::distance(base32_chars.begin(), it));
		}

		// Get the current timestamp in seconds
		auto now = std::chrono::system_clock::now();
		auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

		// Calculate the counter value based on the timestamp and time step
		uint64_t counter = timestamp / timeStep;

		// Generate the TOTP using HOTP with the binary secret key
		std::string totp = HOTP(decodedSecretKey, counter, digits);

		return totp;
	}

	bool validateTOTP(const std::string &secretKey, const std::string &otp, int digits, int timeStep, int window)
	{
		for (int i = -window; i <= window; ++i)
		{
			std::string generatedTOTP = generateTOTP(secretKey, digits, timeStep + (i * timeStep));

			if (generatedTOTP == otp)
			{
				return true; // OTP is valid
			}
		}

		return false; // OTP is not valid
	}

}
