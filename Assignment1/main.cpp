/* Sergey Cherepanov st129987@student.spbu.ru
   Assignment1
*/

#include "Ascii85.h"
#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char* argv[])
{
    Ascii85 ascii85;
    bool decode_mode = false;

    if (argc > 1)
    {
        std::string arg = argv[1];
        if (arg == "-d")
        {
            decode_mode = true;
        }
        else if (arg != "-e")
        {
            std::cerr << "Usage: " << argv[0] << " [-d | -e]\n";
            return 1;
        }
    }

    try
    {
        std::string line;
        while (std::getline(std::cin, line))
        {
            if (decode_mode)
            {
                std::istringstream iss(line);
                ascii85.decodeStream(iss, std::cout);
            }
            else
            {
                std::vector<uint8_t> data(line.begin(), line.end());
                std::cout << ascii85.encode(data);
            }
            std::cout << "\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 2;
    }

    return 0;
}
