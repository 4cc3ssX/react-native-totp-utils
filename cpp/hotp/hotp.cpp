#include "hotp.h"

std::string HOTP(const std::vector<uint8_t> &secretKey, uint64_t counter, int digits)
{
    // Convert the counter to a byte array in big-endian format
    std::vector<uint8_t> counterData;
    for (int i = 7; i >= 0; --i)
    {
        counterData.push_back(static_cast<uint8_t>((counter >> (i * 8)) & 0xFF));
    }

    // Calculate the HMAC-SHA1 value using OpenSSL
    unsigned int hmacLength;
    unsigned char hmacResult[EVP_MAX_MD_SIZE];
    HMAC(EVP_sha1(), secretKey.data(), static_cast<int>(secretKey.size()), counterData.data(), static_cast<int>(counterData.size()), hmacResult, &hmacLength);

    // Get the offset value from the last 4 bits of the HMAC-SHA1 result
    int offset = hmacResult[hmacLength - 1] & 0x0F;

    // Get the 4 bytes from the HMAC-SHA1 result, starting from the calculated offset
    int bin_code = (hmacResult[offset] & 0x7F) << 24 | (hmacResult[offset + 1] & 0xFF) << 16 | (hmacResult[offset + 2] & 0xFF) << 8 | (hmacResult[offset + 3] & 0xFF);

    // Generate the TOTP code by getting the last 6 digits
    int otp = bin_code % static_cast<int>(std::pow(10, digits));

    // Convert the TOTP code to a string and pad with leading zeros if necessary
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(digits) << otp;

    return oss.str();
}
