#pragma once

#include "PolyColumn.hpp"

class Column
{
public:
    vector<unique_ptr<PolyColumn>> columnData;

    inline void push_back(int value)
    {
        columnData.push_back(make_unique<IntColumn>(value));
    }

    inline void push_back(double value)
    {
        columnData.push_back(make_unique<DoubleColumn>(value));
    }

    inline void push_back(const string &value)
    {
        columnData.push_back(make_unique<StringColumn>(value));
    }

    void print(size_t i) const;

    void print_all() const;
};