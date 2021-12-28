#pragma once

#include <map>
#include<vector>
#include<string>
using namespace std;

enum types
{
    type_int,
    type_double,
    type_string
};

class Types
{
private:
    map<string, types> typesMap;

public:
    void mapStringToType()
    {
        typesMap["int"] = type_int;
        typesMap["double"] = type_double,
        typesMap["string"] = type_string;
    }

    vector<types> mapAllStringToType(vector<string> &type) const
    {

        vector<types> result;
        for (const auto &t : type)
        {
            result.push_back(typesMap.find(t)->second);
        }
        return result;
    }
};
