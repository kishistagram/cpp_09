#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <stack>

class RPN
{
	private:
		std::stack<long> _stack;

		void applyOperator(char op);

	public:
		RPN();
		RPN(const RPN &other);
		~RPN();
		RPN &operator=(const RPN &other);

		void executeRPN(const std::string &input);


};


#endif