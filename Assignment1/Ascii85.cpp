/* Sergey Cherepanov st129987@student.spbu.ru
   Assignment1
*/

#include "Ascii85.h"
#include <stdexcept>
#include <array>

void Ascii85::encodeStream(std::istream& in, std::ostream& out)
{
    std::array<uint8_t, 4> buffer;
    size_t count = 0;

    while (in.read(reinterpret_cast<char*>(buffer.data() + count), 1))
    {
        if (++count == 4)
        {
            uint32_t num = (buffer[0] << 24) | (buffer[1] << 16) |
                           (buffer[2] << 8) | buffer[3];
            processEncodeBuffer(num, 4, out);
            count = 0;
        }
    }

    if (count > 0)
    {
        uint32_t num = 0;
        for (size_t i = 0; i < count; ++i)
        {
            num |= buffer[i] << (8 * (3 - i));
        }
        processEncodeBuffer(num, count, out);
    }
}

void Ascii85::processEncodeBuffer(uint32_t num, size_t count, std::ostream& out)
{
    if (num == 0 && count == 4)
    {
        out << 'z';
        return;
    }

    std::array<char, 5> chars;
    for (int i = 4; i >= 0; --i)
    {
        chars[i] = static_cast<char>(num % 85 + 33);
        num /= 85;
    }

    out.write(chars.data(), count + 1);
}

void Ascii85::decodeStream(std::istream& in, std::ostream& out)
{
    std::vector<uint32_t> group;
    char c;

    while (in.get(c))
    {
        if (isspace(c)) continue;

        if (c == 'z')
        {
            if (!group.empty())
            {
                throw std::runtime_error("'z' in middle of group");
            }
            out.write("\0\0\0\0", 4);
            continue;
        }

        if (!isValidChar(c))
        {
            throw std::runtime_error("Invalid ASCII85 character");
        }

        group.push_back(c - 33);

        if (group.size() == 5)
        {
            processDecodeBuffer(group, out);
            group.clear();
        }
    }

    if (!group.empty())
    {
        if (group.size() == 1)
        {
            throw std::runtime_error("Incomplete final group");
        }
        processDecodeBuffer(group, out);
    }
}

void Ascii85::processDecodeBuffer(std::vector<uint32_t>& group, std::ostream& out)
{
    uint32_t num = 0;
    for (auto val : group)
    {
        num = num * 85 + val;
    }

    size_t padding = 5 - group.size();
    for (size_t i = 0; i < padding; ++i)
    {
        num = num * 85 + 84;
    }

    std::array<uint8_t, 4> bytes;
    for (int i = 3; i >= 0; --i)
    {
        bytes[i] = static_cast<uint8_t>(num & 0xFF);
        num >>= 8;
    }

    out.write(reinterpret_cast<char*>(bytes.data()), group.size() - 1);
}

bool Ascii85::isValidChar(char c)
{
    return c >= 33 && c <= 117;
}

std::string Ascii85::encode(std::vector<uint8_t>& data)
{
    std::stringstream ss;
    std::vector<uint8_t> copy(data);
    std::stringstream in(std::string(copy.begin(), copy.end()));
    encodeStream(in, ss);
    return ss.str();
}

std::vector<uint8_t> Ascii85::decode(std::string& data)
{
    std::stringstream ss(data);
    std::stringstream out;
    decodeStream(ss, out);
    std::string result = out.str();
    return std::vector<uint8_t>(result.begin(), result.end());
}
