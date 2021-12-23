#include "Reader_Writer.hpp"
#include "QueryProcessor.hpp"

int main()
{
    // read
    Reader_Writer io;
    io.readAndParseInput();

    // process
    QueryProcessor qp(io.query);
    qp.GroupBy(io.allData);
    qp.Select(io.allData);

    // write
    io.printOutput(qp.select, qp.selections);
}