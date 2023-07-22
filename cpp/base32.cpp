#include <iostream>
#include <string>
#include <vector>
#include <bitset>

static const std::string base32_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"; // Base32 characters
static const char padding_char = '=';                                       // Padding character used in Base32

static std::string base32_encode(const std::vector<uint8_t> &data)
{
    std::string encoded;
    size_t input_size = data.size();

    for (size_t i = 0; i < input_size; i += 5)
    {
        uint32_t chunk = 0;
        size_t chunk_size = std::min(input_size - i, static_cast<size_t>(5));

        for (size_t j = 0; j < chunk_size; j++)
        {
            chunk = (chunk << 8) | data[i + j];
        }

        size_t pad_count = (8 - (chunk_size * 8) % 5) % 8;

        for (size_t j = 0; j < 8; j++)
        {
            if (j < chunk_size + pad_count)
            {
                size_t index = (chunk >> (35 - 5 * j)) & 0x1F;
                encoded.push_back(base32_chars[index]);
            }
            else
            {
                encoded.push_back(padding_char);
            }
        }
    }

    return encoded;
}

static std::vector<uint8_t> base32_decode(const std::string &encoded)
{
    std::vector<uint8_t> data;
    size_t input_size = encoded.size();
    size_t padding_count = 0;

    if (input_size % 8 != 0)
    {
        throw std::invalid_argument("Invalid Base32 string: Length not multiple of 8.");
    }

    for (size_t i = 0; i < input_size; i += 8)
    {
        uint32_t chunk = 0;

        for (size_t j = 0; j < 8; j++)
        {
            char c = encoded[i + j];
            if (c == padding_char)
            {
                padding_count++;
                continue;
            }

            auto it = std::find(base32_chars.begin(), base32_chars.end(), c);
            if (it == base32_chars.end())
            {
                throw std::invalid_argument("Invalid Base32 character.");
            }

            chunk = (chunk << 5) | (std::distance(base32_chars.begin(), it) & 0x1F);
        }

        size_t chunk_size = 5 - padding_count;
        for (size_t j = 0; j < chunk_size; j++)
        {
            data.push_back(static_cast<uint8_t>((chunk >> (32 - 8 * (j + 1))) & 0xFF));
        }
    }

    return data;
}
