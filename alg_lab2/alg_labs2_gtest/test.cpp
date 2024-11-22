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

    EXPECT_EQ(arr[8], 8);
    EXPECT_EQ(arr[45], 45);
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


TEST(ArrayTest, Increments) {
    Array<int> arr;
    for (int i = 1; i <= 5; ++i) {
        arr.insert(i);
    }

    auto it = arr.iterator();
    EXPECT_EQ(*it, 1);

    
    EXPECT_EQ(*(++it), 2);

    EXPECT_EQ(*(it++), 2);

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

TEST(ArrayTest, ConstIteratorTraversal) {
    const Array<int> arr = []() {
        Array<int> temp;
        temp.insert(10);
        temp.insert(20);
        temp.insert(30);
        return temp;
        }();

    auto it = arr.iterator();

    std::string result;
    while (it.hasNext()) {
        result += std::to_string(it.get()) + " ";
        it.next();
    }

    EXPECT_EQ(result, "10 20 30 ");
}

TEST(ArrayTest, ConstIteratorRangeFor) {
    const Array<int> arr = []() {
        Array<int> temp;
        temp.insert(10);
        temp.insert(20);
        temp.insert(30);
        return temp;
        }();

    std::string result;
    for (const auto& value : arr) {
        result += std::to_string(value) + " ";
    }

    EXPECT_EQ(result, "10 20 30 ");
}

TEST(ArrayTest, ConstReverseIterator) {
    const Array<int> arr = []() {
        Array<int> temp;
        temp.insert(10);
        temp.insert(20);
        temp.insert(30);
        return temp;
        }();

    auto it = arr.reverseIterator();

    std::string result;
    while (it.hasNext()) {
        result += std::to_string(it.get()) + " ";
        it.next();
    }

    EXPECT_EQ(result, "30 20 10 ");
}

TEST(ArrayTest, ReverseIteratorTraversal) {
    Array<int> arr;
    arr.insert(10);
    arr.insert(20);
    arr.insert(30);

    auto it = arr.reverseIterator();

    std::string result;
    while (it.hasNext()) {
        result += std::to_string(it.get()) + " ";
        it.next();
    }

    EXPECT_EQ(result, "30 20 10 ");
}

TEST(PersonArrayTest, DefaultConstructor) {
    Array<Person> arr;
    EXPECT_EQ(arr.size(), 0);
}

TEST(PersonArrayTest, InsertElement) {
    Array<Person> arr;
    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0].getName(), "Yana");
    EXPECT_EQ(arr[0].getAge(), 25);
    EXPECT_EQ(arr[1].getName(), "Ilsur");
    EXPECT_EQ(arr[1].getAge(), 30);
}

TEST(PersonArrayTest, InsertAtSpecificIndex) {
    Array<Person> arr;
    arr.insert(Person("Yana", 25));
    arr.insert(Person("Igor", 35));
    arr.insert(1, Person("Ilsur", 30));

    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0].getName(), "Yana");
    EXPECT_EQ(arr[1].getName(), "Ilsur");
    EXPECT_EQ(arr[2].getName(), "Igor");
}

TEST(PersonArrayTest, RemoveElement) {
    Array<Person> arr;
    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));
    arr.insert(Person("Igor", 35));

    arr.remove(1);

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0].getName(), "Yana");
    EXPECT_EQ(arr[1].getName(), "Igor");
}

TEST(PersonArrayTest, IndexOperator) {
    Array<Person> arr;
    arr.insert(Person("Yana", 25));

    EXPECT_EQ(arr[0].getName(), "Yana");
    EXPECT_EQ(arr[0].getAge(), 25);

    arr[0] = Person("Ilsur", 30);
    EXPECT_EQ(arr[0].getName(), "Ilsur");
    EXPECT_EQ(arr[0].getAge(), 30);
}

TEST(PersonArrayTest, IteratorDereferenceAndIncrement) {
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

TEST(PersonArrayTest, Increments) {
    Array<Person> arr;
    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));
    arr.insert(Person("Igor", 35));

    auto it = arr.iterator();
    EXPECT_EQ(it.get().getName(), "Yana");
    EXPECT_EQ((++it).get().getName(), "Ilsur");
    EXPECT_EQ((it++).get().getName(), "Ilsur");
}

TEST(PersonArrayTest, IteratorTraversal) {
    Array<Person> arr;
    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));
    arr.insert(Person("Igor", 35));

    auto it = arr.iterator();
    std::string result;
    while (it != arr.end()) {
        result += it.get().getName() + " ";
        ++it;
    }
    EXPECT_EQ(result, "Yana Ilsur Igor ");
}

TEST(PersonArrayTest, BeginEndRangeFor) {
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

TEST(PersonArrayTest, CBeginCEnd) {
    Array<Person> arr;
    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));
    arr.insert(Person("Igor", 35));

    std::string result;
    for (auto it = arr.cbegin(); it != arr.cend(); ++it) {
        result += it.get().getName() + " ";
    }

    EXPECT_EQ(result, "Yana Ilsur Igor ");
}

TEST(PersonArrayTest, CopyConstructor) {
    Array<Person> arr;
    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));

    Array<Person> copy = arr;

    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy[0].getName(), "Yana");
    EXPECT_EQ(copy[1].getName(), "Ilsur");
}

TEST(PersonArrayTest, MoveConstructor) {
    Array<Person> arr;
    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));

    Array<Person> moved = std::move(arr);

    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved[0].getName(), "Yana");
    EXPECT_EQ(moved[1].getName(), "Ilsur");
    EXPECT_EQ(arr.size(), 0);
}

TEST(PersonArrayTest, ResizeFunctionality) {
    Array<Person> arr;

    for (int i = 0; i < 100; ++i) {
        arr.insert(Person("Person" + std::to_string(i), i));
    }

    EXPECT_EQ(arr.size(), 100);
    EXPECT_EQ(arr[8].getName(), "Person8");
    EXPECT_EQ(arr[8].getAge(), 8);
    EXPECT_EQ(arr[45].getName(), "Person45");
    EXPECT_EQ(arr[45].getAge(), 45);
    EXPECT_EQ(arr[99].getName(), "Person99");
    EXPECT_EQ(arr[99].getAge(), 99);
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

TEST(PersonArrayTest, ConstIteratorTraversal) {
    const Array<Person> arr = []() {
        Array<Person> temp;
        temp.insert(Person("Yana", 25));
        temp.insert(Person("Ilsur", 30));
        temp.insert(Person("Igor", 35));
        return temp;
        }();

    auto it = arr.iterator();

    std::string result;
    while (it.hasNext()) {
        result += it.get().getName() + " ";
        it.next();
    }

    EXPECT_EQ(result, "Yana Ilsur Igor ");
}

//TEST(PersonArrayTest, ConstIteratorRangeFor) {
//    const Array<Person> arr = []() {
//        Array<Person> temp;
//        temp.insert(Person("Yana", 25));
//        temp.insert(Person("Ilsur", 30));
//        temp.insert(Person("Igor", 35));
//        return temp;
//        }();
//
//    std::string result;
//    for (const auto& person : arr) {
//        result += person.getName() + " ";
//    }
//
//    EXPECT_EQ(result, "Yana Ilsur Igor ");
//}

TEST(PersonArrayTest, ConstReverseIterator) {
    const Array<Person> arr = []() {
        Array<Person> temp;
        temp.insert(Person("Yana", 25));
        temp.insert(Person("Ilsur", 30));
        temp.insert(Person("Igor", 35));
        return temp;
        }();

    auto it = arr.reverseIterator();

    std::string result;
    while (it.hasNext()) {
        result += it.get().getName() + " ";
        it.next();
    }

    EXPECT_EQ(result, "Igor Ilsur Yana ");
}


TEST(PersonArrayTest, ReverseIteratorTraversal) {
    Array<Person> arr;
    arr.insert(Person("Yana", 25));
    arr.insert(Person("Ilsur", 30));
    arr.insert(Person("Igor", 35));

    auto it = arr.reverseIterator();

    std::string result;
    while (it.hasNext()) {
        result += it.get().getName() + " ";
        it.next();
    }

    EXPECT_EQ(result, "Igor Ilsur Yana ");
}
