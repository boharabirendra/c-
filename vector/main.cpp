#include <iostream>
#include "Vector.h"

int main()
{

    Vector<int> vec(4, 10);

    std::cout << vec[2] << std::endl;
    std::cout << vec.capacity() << std::endl;

    vec.push_back(1230);

    std::cout << vec[4] << std::endl;

    std::cout << vec.size() << std::endl;

    return 0;
}