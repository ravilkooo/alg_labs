#include <iostream>
#include "dynamic_array.h"

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

    return 0;
}
