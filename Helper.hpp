#pragma once

#include <string>
#include <vector>


class Helper
{
public:
    inline std::vector<std::string> splitString(std::string &str, char delim)
    {
        size_t pos = 0;
        std::string token;
        std::vector<std::string> result;
        while ((pos = str.find(delim)) != std::string::npos)
        {
            token = str.substr(0, pos);
            result.push_back(trim(token));
            str.erase(0, pos + 1);
        }
        token = str.substr(0, std::string::npos);
        result.push_back(trim(token));
        return result;
    }

    inline std::string trim(std::string &str)
    {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }
};