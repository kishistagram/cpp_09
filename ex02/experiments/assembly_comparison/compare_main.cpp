/*
compile:

g++ -std=c++98 -O2 -g \
    -fno-inline \
    -masm=intel \
    compare.cpp compare_main.cpp \
    -o compare
*/

#include <iostream>
#include <vector>
#include <deque>
#include <cstddef>

int getVector(const std::vector<int> &v, std::size_t i);
int getDeque(const std::deque<int> &d, std::size_t i);

int main()
{
    std::vector<int> v;
    std::deque<int> d;

    for (int i = 0; i < 300; ++i)
    {
        v.push_back(i);
        d.push_back(i);
    }

    std::cout << "vector[3]: " << getVector(v, 3) << std::endl;
    std::cout << "deque[3]: " << getDeque(d, 3) << std::endl;
    std::cout << "deque[200]: " << getDeque(d, 200) << std::endl;

    return 0;
}
