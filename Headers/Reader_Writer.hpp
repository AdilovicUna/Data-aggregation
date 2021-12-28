#pragma once

#include <iostream>
#include "Column.hpp"
#include "Types.hpp"
#include "Helper.hpp"

class Reader_Writer
{
private:
    Types t;
    Helper h;
    using Name = string;

public:
    string query;
    map<Name, Column> allData;

    void readAndParseInput();
    void printOutput(vector<pair<string,Name>> &select, vector<pair<string, vector<string>>> &selections) const;

};