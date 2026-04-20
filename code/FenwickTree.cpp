#include "FenwickTree.h"
#include <iostream>

using namespace std;

//Fenwick Tree Implementation

FenwickTree::FenwickTree(const vector<double>& values) {
    numDays = (static_cast<int>(values.size()));//static cast to convert to int
    tree = vector<double>(numDays + 1, 0.0);

    //copy values into tree at 1-based positions, then propagate
    //each node's value to its parent
    for (int i = 1; i <= numDays; ++i) {
        //copy the raw value, ignoring position 0
        tree[i] += values[i - 1];          
        //below is the bit trick that ensures propagation of the sum to parents
        int parent = i + (i & (-i));
        if (parent <= numDays) {
            tree[parent] += tree[i]; //add the sum from the previous node to parent
        }
    }
}

void FenwickTree::update(int day, double change) {
    //make sure that the input is valid
    if (day < 1 || day > numDays) {
        cout << "Error: day " << day << " is out of range [1, " << numDays << "]." << endl;
        return;
    }

    //walk upward through all nodes whose coverage range includes position i.
    //adding the lowest set bit moves us to the next covering ancestor.
    while (day <= numDays) {
        tree[day] += change;
        day += (day & (-day));   // i += lowest set bit of i
    }
}

double FenwickTree::prefixSum(int day) const {
    //make sure that the input is valid
    if (day < 0 || day > numDays) {
        cout << "Error: day " << day << " is out of range [1, " << numDays << "]." << endl;
        return 0.0;
    }

    //walk downward, accumulating partial sums stored at each node.
    //stripping the lowest set bit moves us to the next node below us.
    double sum = 0.0;
    while (day > 0) {
        sum += tree[day];
        day -= (day & (-day));   // day -= lowest set bit of day
    }
    return sum;
}

double FenwickTree::rangeSum(int left, int right) const {
    //make sure that the input is valid
    if (left < 1 || right > numDays || left > right) {
        cout << "rangeSum(): invalid range [" << left << ", " 
            << right << "] for tree of size " << numDays << endl;
        return 0.0;
    }
    //prefixSum(right) includes positions 1 to 'right'
    //prefixSum(left-1) includes positions 1 to 'left-1').
    //their difference is exactly the sum of positions left to right.
    return prefixSum(right) - prefixSum(left - 1);
}

int FenwickTree::size() const {
    return numDays;
}