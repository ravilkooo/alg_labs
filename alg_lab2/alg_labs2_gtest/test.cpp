#include "pch.h"
#include "../alg_lab2/dynamic_array.h" 

TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, InsertElement) {
    Array<int> arr;
    arr.insert(42);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);
}

TEST(ArrayTest, InsertAtSpecificIndex) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    arr.insert(1, 15);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 15);
    EXPECT_EQ(arr[2], 20);
}

TEST(ArrayTest, RemoveElement) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    arr.remove(0);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 20);
}

TEST(ArrayTest, IndexOperator) {
    Array<int> arr;
    arr.insert(10);
    arr[0] = 15;
    EXPECT_EQ(arr[0], 15);
}

TEST(ArrayTest, IteratorTraversal) {
    Array<int> arr;
    for (int i = 1; i <= 5; ++i) {
        arr.insert(i);
    }

    auto it = arr.iterator();
    int sum = 0;
    while (it.hasNext()) {
        sum += it.get();
        it.next();
    }
    EXPECT_EQ(sum, 15);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);

    Array<int> copy = arr;

    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy[0], 10);
    EXPECT_EQ(copy[1], 20);
}

TEST(ArrayTest, MoveConstructor) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);

    Array<int> moved = std::move(arr);

    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved[0], 10);
    EXPECT_EQ(moved[1], 20);
    EXPECT_EQ(arr.size(), 0);
}

TEST(ArrayTest, ResizeFunctionality) {
    Array<int> arr;
    for (int i = 0; i < 100; ++i) {
        arr.insert(i);
    }
    EXPECT_EQ(arr.size(), 100);
    EXPECT_EQ(arr[99], 99);
}
