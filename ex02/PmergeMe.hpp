#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <ctime>
#include <climits>
#include <algorithm> // std::swap
#include <utility> // std::pair, std::make_pair
#include <list>
#include <deque>
#include <vector>


class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;
   
        void loadVector(int argc, char **argv);
        void loadDeque(int argc, char **argv);
    
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void run(int argc, char **argv);


};


#endif