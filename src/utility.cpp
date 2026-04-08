#include "utility.h"


void utility::trimString(std::string& string)
{
    uint64_t strStart{string.find_first_not_of(" \t\n\r")};
    uint64_t strEnd{string.find_last_not_of(" \t\n\r")};
    if (strStart == string.npos)
    {
        string.clear();
    }
    else
    {
        string = string.substr(strStart, strEnd - strStart + 1);
    }
}

void utility::toLowerString(std::string& string)
{
    for (char& ch : string)
        ch = std::tolower(static_cast<unsigned char>(ch));
}