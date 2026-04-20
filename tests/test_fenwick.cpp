#include <gtest/gtest.h>
#include <vector>
#include "../code/FenwickTree.h"

using namespace std;

// Helper: brute force sum of a vector from index left to right (1-indexed)
double bruteForceSum(const vector<double>& vals, int left, int right) {
    double sum = 0.0;
    for (int i = left; i <= right; ++i) {
        sum += vals[i - 1];
    }
    return sum;
}

// -----------------------------------------------------------------------
// FenwickTree tests
// -----------------------------------------------------------------------

TEST(FenwickTree, StartsAtZero) {
    vector<double> empty(8, 0.0);
    FenwickTree t(empty);
    EXPECT_DOUBLE_EQ(t.prefixSum(0), 0.0);
    EXPECT_DOUBLE_EQ(t.prefixSum(8), 0.0);
}

TEST(FenwickTree, SingleUpdate) {
    vector<double> empty(8, 0.0);
    FenwickTree t(empty);
    t.update(3, 5.0);
    EXPECT_DOUBLE_EQ(t.prefixSum(2), 0.0);
    EXPECT_DOUBLE_EQ(t.prefixSum(3), 5.0);
    EXPECT_DOUBLE_EQ(t.prefixSum(8), 5.0);
}

TEST(FenwickTree, MultipleUpdates) {
    vector<double> empty(8, 0.0);
    FenwickTree t(empty);
    t.update(1, 2.0);
    t.update(3, 5.0);
    t.update(5, 3.0);
    EXPECT_DOUBLE_EQ(t.prefixSum(1),  2.0);
    EXPECT_DOUBLE_EQ(t.prefixSum(4),  7.0);
    EXPECT_DOUBLE_EQ(t.prefixSum(5), 10.0);
    EXPECT_DOUBLE_EQ(t.prefixSum(8), 10.0);
}

TEST(FenwickTree, RangeSum) {
    vector<double> vals = {1.0, 2.0, 3.0, 4.0, 5.0};
    FenwickTree t(vals);
    EXPECT_DOUBLE_EQ(t.rangeSum(1, 5), 15.0);
    EXPECT_DOUBLE_EQ(t.rangeSum(1, 1),  1.0);
    EXPECT_DOUBLE_EQ(t.rangeSum(2, 4),  9.0);
    EXPECT_DOUBLE_EQ(t.rangeSum(3, 5), 12.0);
    EXPECT_DOUBLE_EQ(t.rangeSum(4, 4),  4.0);
}

TEST(FenwickTree, BuildFromVector) {
    vector<double> vals = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    FenwickTree t(vals);
    EXPECT_DOUBLE_EQ(t.prefixSum(1),  1.0);
    EXPECT_DOUBLE_EQ(t.prefixSum(4), 10.0);
    EXPECT_DOUBLE_EQ(t.prefixSum(8), 36.0);
    EXPECT_DOUBLE_EQ(t.rangeSum(3, 6), 18.0);
}

TEST(FenwickTree, UpdateModifiesQueries) {
    vector<double> vals = {10.0, 20.0, 30.0, 40.0, 50.0};
    FenwickTree t(vals);
    EXPECT_DOUBLE_EQ(t.prefixSum(3), 60.0);
    t.update(2, -5.0); // 20 -> 15
    EXPECT_DOUBLE_EQ(t.prefixSum(3),  55.0);
    EXPECT_DOUBLE_EQ(t.prefixSum(5), 145.0);
    EXPECT_DOUBLE_EQ(t.rangeSum(2, 4), 85.0);
}

TEST(FenwickTree, NegativeValues) {
    vector<double> vals = {1.0, -2.0, 3.0, -4.0, 5.0};
    FenwickTree t(vals);
    EXPECT_DOUBLE_EQ(t.prefixSum(5),    3.0);
    EXPECT_DOUBLE_EQ(t.rangeSum(1, 4), -2.0);
    EXPECT_DOUBLE_EQ(t.rangeSum(2, 3),  1.0);
}

TEST(FenwickTree, MatchesBruteForce) {
    vector<double> vals = {0.42, -0.31, 1.12, 0.67, -0.55, 1.38, 0.91, 0.14, -1.02, 0.72};
    FenwickTree t(vals);

    // Test several ranges — Fenwick result must match brute force exactly
    EXPECT_NEAR(t.rangeSum(1, 10), bruteForceSum(vals, 1, 10), 1e-9);
    EXPECT_NEAR(t.rangeSum(1,  5), bruteForceSum(vals, 1,  5), 1e-9);
    EXPECT_NEAR(t.rangeSum(3,  7), bruteForceSum(vals, 3,  7), 1e-9);
    EXPECT_NEAR(t.rangeSum(5,  5), bruteForceSum(vals, 5,  5), 1e-9);

    // Apply an update and verify both approaches still agree
    t.update(3, 2.0);
    vals[2] += 2.0; // keep brute force in sync
    EXPECT_NEAR(t.rangeSum(1, 10), bruteForceSum(vals, 1, 10), 1e-9);
    EXPECT_NEAR(t.rangeSum(3,  7), bruteForceSum(vals, 3,  7), 1e-9);
}

TEST(FenwickTree, OutOfRangeReturnsSafely) {
    vector<double> vals = {1.0, 2.0, 3.0, 4.0, 5.0};
    FenwickTree t(vals);
    // These should print an error message and return 0.0 without crashing
    EXPECT_DOUBLE_EQ(t.prefixSum(6),   0.0);
    EXPECT_DOUBLE_EQ(t.rangeSum(3, 1), 0.0);
}