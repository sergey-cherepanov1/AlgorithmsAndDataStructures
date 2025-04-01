/* Sergey Cherepanov st129987@student.spbu.ru
   Assignment1
*/

#ifndef ASCII85_H
#define ASCII85_H

#include <iostream>
#include <vector>
#include <cstdint>
#include <sstream>
#include <string>

class Ascii85
{
public:
    void encodeStream(std::istream& in, std::ostream& out);
    void decodeStream(std::istream& in, std::ostream& out);
    std::string encode(std::vector<uint8_t>& data);
    std::vector<uint8_t> decode(std::string& data);

private:
    bool isValidChar(char c);
    void processEncodeBuffer(uint32_t num, size_t count, std::ostream& out);
    void processDecodeBuffer(std::vector<uint32_t>& group, std::ostream& out);
};

#endif
