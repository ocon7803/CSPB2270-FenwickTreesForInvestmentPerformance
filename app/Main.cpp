#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "../code/FenwickTree.h"

using namespace std;

//Read daily returns from a CSV file with "day,return" headers.
//Returns a 0-indexed vector where result[0] = day 1 return.
vector<double> loadCSV(const string& filename) {
    vector<double> returns;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open file \"" << filename << "\"." << endl;
        return returns;
    }

    string line;
    getline(file, line); //skip header row

    while (getline(file, line)) {
        stringstream ss(line);
        string dayStr, returnStr;
        getline(ss, dayStr, ','); //parse
        getline(ss, returnStr, ',');
        returns.push_back(stod(returnStr));
    }

    //Output ingested returns
    return returns;
}

int main() {
    // Load returns from CSV and build the Fenwick Tree
    vector<double> dailyReturns = loadCSV("../daily_returns.csv");
    if (dailyReturns.empty()) {
        cout << "Error: No data found" << endl;
        return 1;
    }

    FenwickTree tree(dailyReturns);
    cout << "Loaded " << dailyReturns.size() << " days of returns.\n";

    //Functionality 1: Range query: cumulative return from day 10 to day 50
    int startDay = 10;
    int endDay   = 50;
    cout << "Cumulative return from day " << startDay << " to day " << endDay << ": $"
         << tree.rangeSum(startDay, endDay) << "\n";

    //Functionality 2: Update: correct day 15's return from +$1450 to -$2500
    int correctedDay = 15;
    double originalReturn = dailyReturns[correctedDay - 1];
    double correctedReturn = -2500;
    double delta = correctedReturn - originalReturn;

    tree.update(correctedDay, delta);
    cout << "Updated day " << correctedDay << " from $" << originalReturn
         << " to $" << correctedReturn << "\n";

    //Run again to show the update was reflected
    cout << "Cumulative return from day 10 to day 50 after update: $"
         << tree.rangeSum(startDay, endDay) << "\n";

    return 0;
}