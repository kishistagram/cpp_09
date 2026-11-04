#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <climits>

/* constructor, destructor*/

RPN::RPN() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN::~RPN() {}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stack = other._stack;
	return (*this);
}

static bool isAdditionOverflow(long left, long right)
{
	if (right > 0 && left > LONG_MAX - right)
		return true;
	if (right < 0 && left < LONG_MIN - right)
		return true;
	return false;
}

static bool isSubtractionOverflow(long left, long right)
{
	if (right < 0 && left > LONG_MAX + right)
		return true;
	if (right > 0 && left < LONG_MIN + right)
		return true;
	return false;
}

static bool isMultiplicationOverflow(long left, long right)
{
	if (left == 0 || right == 0)
		return false;
	
	if (left > 0 && right > 0)
		return left > LONG_MAX / right;
	
	if (left > 0 && right < 0)
		return right < LONG_MIN / left;
	
	if (left < 0 && right > 0)
		return left < LONG_MIN / right;

	// left < 0 && right < 0
	if (left == LONG_MIN || right == LONG_MIN)
		return true;
	
	return left < LONG_MAX / right;
}

static bool isDivisionInvalid(long left, long right)
{
	if (right == 0)
		return true;
	if (left == LONG_MIN && right == -1)
		return true;
	return false;
}



void RPN::applyOperator(char op)
{
	if (_stack.size() < 2)
		throw std::runtime_error("Error");
	
	long right = _stack.top();
	_stack.pop();

	long left = _stack.top();
	_stack.pop();

	long result = 0;

	if (op == '+')
	{
		if (isAdditionOverflow(left, right))
			throw std::runtime_error("Error");
		result = left + right;
	}
	else if (op == '-')
	{
		if (isSubtractionOverflow(left, right))
			throw std::runtime_error("Error");
		result = left - right;
	}
	else if (op == '*')
	{
		if (isMultiplicationOverflow(left, right))
			throw std::runtime_error("Error"); 
		result = left * right;
	}
	else if (op == '/')
	{
		if (isDivisionInvalid(left, right))
			throw std::runtime_error("Error");
		result = left / right;
	}
	else
		throw std::runtime_error("Error");

	_stack.push(result);
}

void RPN::executeRPN(const std::string &input)
{
	while (!_stack.empty())
		_stack.pop();
	
	std::istringstream iss(input);
	std::string token;

	while (iss >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("Error");
		char c = token[0];

		if (c >= '0' && c <= '9')
		{
			_stack.push(c - '0');
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			applyOperator(c);
		}
		else
		{
			throw std::runtime_error("Error");
		}

	}
	if (_stack.size() != 1)
		throw std::runtime_error("Error");
	
	std::cout << _stack.top() << std::endl;
}


