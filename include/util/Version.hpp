#pragma once

#include <util/Util.hpp>

#include <string>

namespace JEM
{
    struct Version
    {
        int major;
        int minor;
        int patch;

        operator const std::string() const { return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch); }

        Version() = default;

        Version(int maj, int min, int pat)
        {
            major = maj;
            minor = min;
            patch = pat;
        }

        consteval Version(const char *str)
        {
            major = 0;
            minor = 0;
            patch = 0;

            const char *token = str;
            if (*token == '\0')
                return;

            major = atoi(token);

            do
            {
                token++;
                if (*token == '\0')
                    return;
            } while (*(token - 1) != '.');

            minor = atoi(token);

            do
            {
                token++;
                if (*token == '\0')
                    return;
            } while (*(token - 1) != '.');

            patch = atoi(token);
        }
    };
}