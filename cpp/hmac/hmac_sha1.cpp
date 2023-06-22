#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

#include "../sha/sha1.cpp"

static std::string Sha1(const std::string &message)
{
    SHA1 sha1;
    sha1.update(message);
    std::string digest = sha1.final();

    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (size_t i = 0; i < digest.length(); ++i)
        ss << std::setw(2) << static_cast<int>(static_cast<unsigned char>(digest[i]));

    return ss.str();
}

static std::string KeyPadding(const std::string &key)
{
    std::string paddedKey = key;
    if (key.length() > 64)
        paddedKey = Sha1(key);
    else if (key.length() < 64)
        paddedKey.append(64 - key.length(), 0x00);

    return paddedKey;
}

static std::string XorString(const std::string &a, const std::string &b)
{
    std::string result;
    for (size_t i = 0; i < a.length(); ++i)
        result.push_back(a[i] ^ b[i]);

    return result;
}

static std::string HMAC(const std::string &key, const std::string &message)
{
    std::string paddedKey = KeyPadding(key);
    std::string innerKey = XorString(paddedKey, std::string(64, 0x36));
    std::string outerKey = XorString(paddedKey, std::string(64, 0x5C));

    std::string innerHash = Sha1(innerKey + message);
    std::string hmac = Sha1(outerKey + innerHash);

    return hmac;
}
