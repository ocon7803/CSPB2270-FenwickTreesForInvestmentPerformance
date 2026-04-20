# CSPB2270-FenwickTreesForInvestmentPerformance

I've implemented a Fenwick Tree in C++ that logs simulated daily returns for a portfolio. Each index represents a trading day, and each value represents that day's return. The program will support two operations: inserting a daily return, and querying cumulative return between any two days. I've ran it against a hardcoded sequence of simulated daily returns and printed the results demonstrating that the range queries produce correct results.

## Overview:

A Fenwick Tree, also called a Binary Indexed Tree, is a data structure built on top of a plain array that supports two operations in O(log n) time: recording or updating a value at a position, and querying the cumulative sum up to any given position. A cumulative sum, referred to as a prefix sum in much of the documentation surrounding Fenwick trees, is simply just a running total computed along the tree’s nodes. Range queries between two nodes, like the total % return from day 10 to day 50, are just calculated as the difference between the cumulative sums at day 9 and day 50. This cumulative sum functionality is the core operation I'll be implementing, and is the main benefit of the Fenwick tree structure. However, I’ll also support inserting a daily return to update a value at a position. 

## More about Fenwick Trees:

Fenwick trees provide a method to query the running total at any index, or prefix sum, while allowing changes to the underlying value array and having all further queries reflect those changes. The benefit of the Fenwick tree vs the naive approach of looping through and summing every element in an input array is that you can retrieve cumulative changes over time in O(log n) time, versus O(n) time. The Fenwick Tree's efficiency comes from a single bit operation: 'i & (-i)'. This expression isolates the lowest set bit of any integer i, meaning it finds the rightmost 1 in the binary representation of i and returns its value. This works because of how negative numbers are stored in binary. To negate a number, the computer flips all its bits and adds 1. When you 'AND' the original number with its negation, every bit cancels out except the lowest set bit, which survives in both versions.

The Fenwick Tree uses this in two ways: During a query, each node at index i is responsible for storing the sum of exactly i & (-i) elements ending at position i. To get a cumulative sum up to position i, you add up the current node and then strip the lowest set bit (i -= i & (-i)) to jump to the next node below, repeating until you reach zero. During an update, you do the opposite: after updating the current node, you add the lowest set bit (i += i & (-i)) to jump to the next node whose range covers position i, propagating the change upward.

## My Implementation:

This implementation uses vectors rather than arrays, primarily out of laziness, but also for it's dynamic sizing, memory management, use of .size(), and convenience of initializing. It is also different from the geeksforgeeks implementation, which required some brainpower. 

As mentioned above, the program takes in 250 simulated daily portfolio returns from 'daily_returns.csv' and uses that data to demonstrate its functionality.

I've set this project up just like the homeworks, where you can use 'make && ./run_app' to execute the whole program, and you can also use 'make && ./run_tests' to execute tests, which were written by Claude per the instructor's recommendation. 

The main outputs of the program are a summed cumulative return from day 10 to 50, an update to day 15's return, and then another summed cumulative return showcasing the effect of the update.

In lieu of a recorded video, I included a pdf walkthrough of the project in the pdf titled 'Walkthrough_Fenwick_Tree_Final_Project' in this repository.
