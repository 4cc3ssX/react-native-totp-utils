#include "react-native-totp-utils.h"

namespace totputils
{
	std::string generateSecretKey(int keyLength)
	{
		const std::string base32Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
		std::string secretKey;
		secretKey.reserve(keyLength);

		// Initialize random number generator with a seed based on current time
		auto currentTime = std::chrono::system_clock::now();
		auto timeSinceEpoch = currentTime.time_since_epoch();
		auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch).count();
		std::mt19937 gen(static_cast<unsigned int>(seed));

		// Generate key using random base32 characters
		std::uniform_int_distribution<int> distribution(0, base32Chars.size() - 1);
		for (int i = 0; i < keyLength; ++i)
		{
			secretKey.push_back(base32Chars[distribution(gen)]);
		}

		return secretKey;
	}

	std::string generateOTP(const std::string &secretKey, int digits, int timeStep)
	{
		// Get the current timestamp in seconds
		auto now = std::chrono::system_clock::now();
		auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

		// Compute the counter value based on the timestamp and time step
		uint64_t counter = static_cast<uint64_t>(timestamp) / timeStep;

		// Convert the counter value to big-endian bytes
		unsigned char counterBytes[8];
		for (int i = 7; i >= 0; --i)
		{
			counterBytes[i] = counter & 0xFF;
			counter >>= 8;
		}

		// Compute the HMAC-SHA1 hash of the counter value using the secret key
		std::string hmacResult = HMAC(secretKey, std::string(reinterpret_cast<char *>(counterBytes), sizeof(counterBytes)));

		// Extract the offset from the last 4 bits of the hash
		int offset = hmacResult[hmacResult.length() - 1] & 0x0F;

		// Compute the 4-byte binary code starting from the offset
		int binary = ((hmacResult[offset] & 0x7F) << 24) |
					 ((hmacResult[offset + 1] & 0xFF) << 16) |
					 ((hmacResult[offset + 2] & 0xFF) << 8) |
					 (hmacResult[offset + 3] & 0xFF);

		// Compute the final OTP value by taking the modulo of the binary code
		int otp = binary % static_cast<int>(std::pow(10, digits));

		// Convert the OTP value to a string with leading zeros
		std::ostringstream oss;
		oss << std::setw(digits) << std::setfill('0') << otp;

		return oss.str();
	}

	bool validateOTP(const std::string &secretKey, const std::string &otp, int digits, int timeStep, int window)
	{
		// Get the current timestamp in seconds
		auto now = std::chrono::system_clock::now();
		auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

		// Compute the counter value based on the timestamp and time step
		uint64_t counter = static_cast<uint64_t>(timestamp) / timeStep;

		// Iterate over the window of counters and generate OTPs to validate
		for (int i = -window; i <= window; ++i)
		{
			uint64_t currentCounter = counter + i;

			// Convert the counter value to big-endian bytes
			unsigned char counterBytes[8];
			for (int j = 7; j >= 0; --j)
			{
				counterBytes[j] = currentCounter & 0xFF;
				currentCounter >>= 8;
			}

			// Compute the HMAC-SHA1 hash of the counter value using the secret key
			std::string generatedOTP = HMAC(secretKey, std::string(reinterpret_cast<char *>(counterBytes), sizeof(counterBytes)));

			// Extract the offset from the last 4 bits of the hash
			int offset = generatedOTP[generatedOTP.length() - 1] & 0x0F;

			// Compute the 4-byte binary code starting from the offset
			int binary = ((generatedOTP[offset] & 0x7F) << 24) |
						 ((generatedOTP[offset + 1] & 0xFF) << 16) |
						 ((generatedOTP[offset + 2] & 0xFF) << 8) |
						 (generatedOTP[offset + 3] & 0xFF);

			// Compute the final OTP value by taking the modulo of the binary code
			int generatedOTPValue = binary % static_cast<int>(std::pow(10, digits));

			// Convert the OTP value to a string with leading zeros
			std::ostringstream oss;
			oss << std::setw(digits) << std::setfill('0') << generatedOTPValue;
			std::string generatedOTPString = oss.str();

			if (generatedOTPString == otp)
			{
				return true; // OTP is valid
			}
		}

		return false; // OTP is not valid
	}

}
