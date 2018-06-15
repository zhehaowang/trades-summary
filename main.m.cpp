#include <tradebook.h>
#include <string>
#include <fstream>

using namespace std;
using namespace tradebook;

const string INPUT_FILE_NAME  = "input.csv";
const string OUTPUT_FILE_NAME = "output.csv";

void generateSummary() {
    Tradebook tradebook;

    fstream ifs;
    ifs.open(INPUT_FILE_NAME, fstream::in);

    string timestamp = "";
    string symbol    = "";
    string quantity  = "";
    string price     = "";

    while (getline(ifs, timestamp, ',')) {
        getline(ifs, symbol, ',');
        getline(ifs, quantity, ',');
        getline(ifs, price);
        tradebook.insertTrade(Trade(stoull(timestamp),
                                    symbol,
                                    stoul(quantity),
                                    stoul(price)));
    }
    ifs.close();

    fstream ofs;
    ofs.open(OUTPUT_FILE_NAME, fstream::out);
    tradebook.printSummary(ofs);
    ofs.close();
}

int main() {
    generateSummary();
    return 0;
}