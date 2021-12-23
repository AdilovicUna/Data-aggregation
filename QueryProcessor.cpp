#include "QueryProcessor.hpp"
QueryProcessor::QueryProcessor(string &query)
{
    /*
        Splits the query into appropriate parts
    */

    size_t pos = query.find("GROUP_BY");
    // 6 is the length of string "SELECT"
    string str = string(&query[6], &query[pos]);
    vector<string> select_h = h.splitString(str, ',');
    vector<string> temp;
    for (auto &s : select_h)
    {
        // eg1. s = SUM(jmeno)
        // temp[0] = "SUM", temp[1] = "jmeno)"
        // we need to take the substring of temp[1] so that we get "jmeno"
        // eg2. s = prijemni
        // temp[0] = "prijemni"

        temp = h.splitString(s, '(');
        if (temp.size() == 1)
        {
            select.push_back(make_pair("print", temp[0]));
        }
        else
        {
            select.push_back(make_pair(temp[0], temp[1].substr(0, temp[1].size() - 1)));
        }
    }
    // 8 is the length of string "GROUP_BY"
    groupBy = string(&query[pos + 8], &query[query.length()]);
    groupBy = h.trim(groupBy);
}

void QueryProcessor::GroupBy(map<Name, Column> const &data)
{
    /*
        For every group stores which rows of the data belong to it
    */

    int index = 0;
    string key;
    // loop over column with the name == groupBy
    for (auto &&elem : data.find(groupBy)->second.columnData)
    {
        key = elem->getStringValue();
        // if the group doesn't exist, create it
        bool found = false;
        for (const auto &g : groups)
        {
            if (g.first == key)
            {
                found = true;
            }
        }
        if (!found)
        {
            groups.push_back(make_pair(key, vector<int>()));
        }

        // store the element into the group
        for (auto &g : groups)
        {
            if (g.first == key)
            {
                (g.second).push_back(index++);
            }
        }
    }
}

string QueryProcessor::Sum(types &t, vector<string> &vals)
{
    /*
        Calculate sum of vals
    */
    string result;
    stringstream s;
    int sumi = 0;
    double sumd = 0;
    switch (t)
    {
    case type_int:
        for (const auto &val : vals)
        {
            sumi += stoi(val);
        }
        result = to_string(sumi);
        break;
    case type_double:
        for (const auto &val : vals)
        {
            sumd += stod(val);
        }
        s << fixed << setprecision(6) << sumd;
        result = s.str();
        break;
    case type_string:
        for (const auto &val : vals)
        {
            result += val;
        }
        break;
    default:
        break;
    }
    return result;
}

string QueryProcessor::Min(types &t, vector<string> &vals)
{
    /*
        Find min value from the vals
    */
    string result;
    stringstream s;
    int mini;
    double mind;
    switch (t)
    {
    case type_int:
        mini = stoi(vals[0]);
        for (const auto &val : vals)
        {
            if (stoi(val) < mini)
            {
                mini = stoi(val);
            }
        }
        result = to_string(mini);
        break;
    case type_double:
        mind = stod(vals[0]);
        for (const auto &val : vals)
        {
            if (stod(val) < mind)
            {
                mind = stod(val);
            }
        }
        s << fixed << setprecision(6) << mind;
        result = s.str();
        break;
    case type_string:
        result = *min_element(vals.begin(), vals.end());
        break;
    default:
        break;
    }
    return result;
}

string QueryProcessor::Max(types &t, vector<string> &vals)
{
    /*
        Find max value from the vals
    */
    string result;
    stringstream s;
    int maxi;
    double maxd;
    switch (t)
    {
    case type_int:
        maxi = stoi(vals[0]);
        for (const auto &val : vals)
        {
            if (stoi(val) > maxi)
            {
                maxi = stoi(val);
            }
        }
        result = to_string(maxi);
        break;
    case type_double:
        maxd = stod(vals[0]);
        for (const auto &val : vals)
        {
            if (stod(val) > maxd)
            {
                maxd = stod(val);
            }
        }
        s << fixed << setprecision(6) << maxd;
        result = s.str();
        break;
    case type_string:
        result = *max_element(vals.begin(), vals.end());
        break;
    default:
        break;
    }
    return result;
}

void QueryProcessor::PerformSelect(const string &group, types &t, vector<string> &vals, Combiner op)
{
    /*
        Appends result of sum/min/max to the appropriate group in selections
    */
    for (auto &ss : selections)
    {
        if (ss.first == group)
        {
            ss.second.push_back((this->*op)(t, vals));
        }
    }
}

void QueryProcessor::Select(map<Name, Column> const &data)
{
    types t;
    vector<string> vals;
    for (const auto &group : groups)
    {
        selections.push_back(make_pair(group.first, vector<string>()));
        for (const auto &s : select)
        {
            // get type of the value we will be working with
            // all types are the same so we only need to check for one
            t = data.find(s.second)->second.columnData[group.second[0]]->getType();
            vals.clear();
            for (auto i : group.second)
            {
                // we get all the values we will be working with
                vals.push_back(data.find(s.second)->second.columnData[i]->getStringValue());
            }
            if (s.first == "SUM")
            {
                PerformSelect(group.first, t, vals, &QueryProcessor::Sum);
            }
            else if (s.first == "MIN")
            {
                PerformSelect(group.first, t, vals, &QueryProcessor::Min);
            }
            else if (s.first == "MAX")
            {
                PerformSelect(group.first, t, vals, &QueryProcessor::Max);
            }
            else if (groupBy == s.second)
            {
                // if none of the above is valid
                // append group names to selections
                for (auto &ss : selections)
                {
                    if (ss.first == group.first)
                    {
                        ss.second.push_back(group.first);
                        break;
                    }
                }
            }
        }
    }
}