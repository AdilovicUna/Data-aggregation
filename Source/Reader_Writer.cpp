#include "Reader_Writer.hpp"
void Reader_Writer::readAndParseInput()
{
    /*
        Reads the input from stdin converts and stores it to appropriate data structure
    */

    // get first 3 rows and split the information from there
    string row1;
    string row2;
    size_t N;

    cin >> row1;
    cin >> row2;
    cin >> N;

    // split name and types
    vector<Name> v_names = h.splitString(row1, ';');
    vector<string> temp = h.splitString(row2, ';');

    // map types to enum types
    t.mapStringToType();
    vector<types> v_types = t.mapAllStringToType(temp);

    // create our allData dictionary
    for (size_t i = 0; i < v_names.size(); i++)
    {
        allData.insert(make_pair(v_names[i], Column()));
    }

    // process data line by line and store the values into allData
    string line;
    vector<string> data;
    while (N-- > 0)
    {
        cin >> line;
        data = h.splitString(line, ';');

        for (size_t i = 0; i < v_names.size(); i++)
        {
            switch (v_types[i])
            {
            case type_int:
                allData[v_names[i]].push_back(stoi(data[i]));
                break;
            case type_double:
                allData[v_names[i]].push_back(stod(data[i]));
                break;
            case type_string:
                allData[v_names[i]].push_back(data[i]);
                break;
            default:
                break;
            }
        }
    }

    cin.ignore(256, '\n'); // ignore the remaining input characters up to the next newline character
    getline(cin, query);   // read the query
}

void Reader_Writer::printOutput(vector<pair<string, Name>> &select, vector<pair<string, vector<string>>> &selections) const
{
    /*
        Prints the results in appropriate format to stdin
    */

    bool first = true;
    for (const auto &s : select)
    {
        if (!first) // we want to prepend ; to every operation, except first
        {
            cout << ";";
        }
        if (s.first != "print") // eg. s.first = SUM ; s.second = jmeno
        {
            cout << s.first << "(" << s.second << ")";
        }
        else // in case we don't have an operation (eg. prijemni)
        {
            cout << s.second;
        }
        first = false;
    }
    cout << endl;
    for (const auto &group : selections)
    {
        first = true;
        for (const auto &selection : group.second)
        {
            if (!first) // similarly as above
            {
                cout << ";";
            }
            cout << selection;
            first = false;
        }
        cout << endl;
    }
}
