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
#include <cstddef>


class PmergeMe
{
    private:
        std::vector<int> _vector;
        std::deque<int> _deque;
   
        void loadVector(int argc, char **argv);
        void loadDeque(int argc, char **argv);

		// vector
        void makeVectorPairs(
            std::vector<std::pair<int, int> > &pairs,
            bool &hasStraggler,
            int &straggler) const;
    	static void fordJohnsonVector(
        	std::vector<int> &data,
        	std::size_t groupSize);
		//　共通関数でOK
		static std::vector<std::size_t>PmergeMe::generateJacobsthalOrder(
			std::size_t count);
    
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void run(int argc, char **argv);


};


#endif