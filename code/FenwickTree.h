#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

#include <vector>

using namespace std;

class FenwickTree {
public:
    //Construct and initialize from an existing array of values (1-indexed values
    //are passed in a 0-indexed vector, where v[0] = value at position 1).
    FenwickTree(const vector<double>& values);

    //Add `change` to the value at position `day` (1-indexed).
    //All subsequent prefix-sum queries will reflect this change.
    //Prints error message if 'day' is outside [1, numDays].
    void update(int day, double change);

    //Return the cumulative (prefix) sum from position 1 to 'day' (1-indexed).
    //Prints error message if i is outside [0, numDays].
    double prefixSum(int day) const;

    //Return the sum of values in the closed range [left, right] (1-indexed).
    //This is just prefixSum(right) - prefixSum(left - 1).
    //Prints error message if indices are invalid or left > right.
    double rangeSum(int left, int right) const;

    //Return the number of positions this tree was built for.
    int size() const;

private:
    int numDays; //number of positions (1-indexed, so tree has n+1 slots)
    vector<double> tree;// internal storage; tree[0] is unused
};

#endif // FENWICK_TREE_H