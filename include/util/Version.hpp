#pragma once

#include <string>

namespace JEM {
    struct Version
    {
        int major;
        int minor;
        int patch;

        operator const std::string() const { return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(patch); }
    };
}