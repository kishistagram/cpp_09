#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	RPN rpn;

	if (argc != 2)
	{
		std::cerr << "incorrect input" << std::endl;
		return 1;
	}
	try
	{
		rpn.executeRPN(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

/*
$ ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42

$ ./RPN "7 7 * 7 -"
42

$ ./RPN "1 2 * 2 / 2 * 2 4 - +"
0

$ ./RPN "(1 + 1)"
Error
$ ./RPN "5 2 - 1 2 - -"
4
$ ./RPN "5 2 -"
3
$ ./RPN "5 2 - 3 *"
9
$ ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$ ./RPN "1 2 * 2 / 2 * 2 4 - +"
0
$ ./RPN "7 7 * 7 -"
42
$ ./RPN "1 0 /"
Error
$ ./RPN "1 +"
Error
$ ./RPN "1 2 3 +"
Error
$ ./RPN "12 3 +"
Error
$ ./RPN ""
Error
$ ./RPN "3 4 &"
Error



*/