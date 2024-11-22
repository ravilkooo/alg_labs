#include "pch.h"
#include "../alg_lab2/dynamic_array.h"
#include "../alg_lab2/person.h"

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


TEST(ArrayTest, IteratorDereferenceAndIncrement) {
    Array<int> arr;
    for (int i = 1; i <= 5; ++i) {
        arr.insert(i);
    }

    auto it = arr.iterator();

    EXPECT_EQ(*it, 1);

    ++it;
    EXPECT_EQ(*it, 2);

    it++;
    EXPECT_EQ(*it, 3);

    ++it;
    ++it;
    EXPECT_EQ(*it, 5);

    ++it;
    EXPECT_FALSE(it != arr.end());
}

TEST(ArrayTest, BeginEndRangeFor) {
    Array<int> arr;
    for (int i = 1; i <= 5; ++i) {
        arr.insert(i);
    }

    int sum = 0;
    for (const auto& value : arr) {
        sum += value;
    }

    EXPECT_EQ(sum, 15);
}

TEST(ArrayTest, CBeginCEnd) {
    Array<int> arr;
    for (int i = 1; i <= 5; ++i) {
        arr.insert(i);
    }

    int sum = 0;
    for (auto it = arr.cbegin(); it != arr.cend(); ++it) {
        sum += *it;
    }

    EXPECT_EQ(sum, 15);
}


TEST(PersonArrayTest, InsertAndAccess) {
    Array<Person> arr;

    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0].getName(), "Yana");
    EXPECT_EQ(arr[0].getAge(), 25);
    EXPECT_EQ(arr[1].getName(), "Ilsur");
    EXPECT_EQ(arr[1].getAge(), 30);
}

TEST(PersonArrayTest, RemovePerson) {
    Array<Person> arr;

    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));
    arr.insert(Person("Igor", 35));

    arr.remove(1);

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0].getName(), "Yana");
    EXPECT_EQ(arr[1].getName(), "Igor");
}

TEST(PersonArrayTest, IteratorPerson) {
    Array<Person> arr;

    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));
    arr.insert(Person("Igor", 35));

    auto it = arr.iterator();

    EXPECT_EQ(it.get().getName(), "Yana");
    ++it;
    EXPECT_EQ(it.get().getName(), "Ilsur");
    it++;
    EXPECT_EQ(it.get().getName(), "Igor");
}

TEST(PersonArrayTest, RangeForPerson) {
    Array<Person> arr;

    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));
    arr.insert(Person("Igor", 35));

    std::string result;
    for (const auto& person : arr) {
        result += person.getName() + " ";
    }

    EXPECT_EQ(result, "Yana Ilsur Igor ");
}
