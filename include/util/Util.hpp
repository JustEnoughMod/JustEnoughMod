#pragma once

#include <vector>
#include <sstream>

namespace JEM
{
    std::vector<std::string> split(const std::string &s, char delim)
    {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (getline(ss, item, delim))
        {
            result.push_back(item);
        }

        return result;
    }

    constexpr int atoi(const char *ch)
    {
        int i = 0;

        while (*ch != '\0')
        {
            if (*ch < 48 || *ch > 57)
                break;

            i *= 10;
            i += *ch - 48;

            ch++;
        }

        return i;
    }
}