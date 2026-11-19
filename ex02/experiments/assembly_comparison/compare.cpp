/*
これでコンパイル: 
g++ -Wall -Wextra -Werror -std=c++98 -O2 -S -masm=intel compare.cpp -
o compare.s
*/



#include <vector>
#include <deque>

int getVector(const std::vector<int> &v, std::size_t i)
{
	return v[i];
}

int getDeque(const std::deque<int> &d, std::size_t i)
{
	return d[i];
}

