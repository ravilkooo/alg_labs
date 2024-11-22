#include <iostream>
#include "dynamic_array.h"
#include "person.h"

int main() {
    Array<int> arr;
    for (int i = 0; i < 10; ++i) {
        arr.insert(i + 1);
    }

    for (int i = 0; i < arr.size(); ++i) {
        arr[i] *= 2;
    }

    for (auto it = arr.iterator(); it.hasNext(); it.next()) {
        std::cout << it.get() << std::endl;
    }

    Array<Person> arr_2;

    arr_2.insert(Person("Yana", 25));
    arr_2.insert(Person("Ilsur", 30));
    arr_2.insert(Person("Igor", 35));

    auto it = arr_2.iterator();

    std::cout << it.get().getName() << std::endl;
    ++it;
    std::cout << it.get().getName() << std::endl;
    it++;
    std::cout << it.get().getName() << std::endl;

    return 0;
}
