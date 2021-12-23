#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include "Types.hpp"
using namespace std;

class PolyColumn
{
public:
    virtual string getStringValue() { return ""; };
    virtual types getType() { return type_string; };
};

class IntColumn : public PolyColumn
{
public:
    int value;
    IntColumn(int v) : value(v)
    {
    }
    inline string getStringValue() override
    {
        return to_string(value);
    }
    inline types getType() override
    {
        return type_int;
    }
};

class DoubleColumn : public PolyColumn
{
public:
    double value;
    DoubleColumn(double v) : value(v)
    {
    }
    inline string getStringValue() override
    {
        stringstream s;
        s << fixed << setprecision(6) << value;
        return s.str();
    }
    inline types getType() override
    {
        return type_double;
    }
};

class StringColumn : public PolyColumn
{
public:
    string value;
    StringColumn(const string &v) : value(v)
    {
    }
    inline string getStringValue() override
    {
        return value;
    }
    inline types getType() override
    {
        return type_string;
    }
};