#include <iostream>
#include "Hash.h"

int main() {
    Hash hash;

    std::cout << hash.setString("sw").make() << std::endl;
    std::cout << hash.setString("dw").make() << std::endl;

    return 0;
}
