#pragma once

#include <map>
#include <algorithm>
#include "Column.hpp"
#include "Helper.hpp"
#include "Types.hpp"
using namespace std;

class QueryProcessor
{
private:
    using Name = string;

    Helper h;

    string groupBy;
    vector<pair<string, vector<int>>> groups; //value and index of rows

    using Combiner = string (QueryProcessor::*)(types &t, vector<string> &vals);
    void PerformSelect(const string &group, types &t, vector<string> &vals, Combiner op);
    string Sum(types &t, vector<string> &vals);
    string Min(types &t, vector<string> &vals);
    string Max(types &t, vector<string> &vals);

public:
    vector<pair<string, Name>> select; // operation and column name
    vector<pair<string, vector<string>>> selections; // group and results from select on that group

    QueryProcessor(string &query);
    void GroupBy(map<Name, Column> const &data);
    void Select(map<Name, Column> const &data);
};