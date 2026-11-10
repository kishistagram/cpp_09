#include "PmergeMe.hpp"



int main(int argc, char **argv)
{
    try
    {
        PmergeMe sorter;
        sorter.run(argc, argv);
    
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error: "
                  << e.what() 
                  << std::endl;
        return 1;
    }
    return 0;
    
}

// static void printNumbers(const std::vector<int> &numbers)
// {
//     for (std::vector<int>::const_iterator it = numbers.begin(); it!= numbers.end(); ++it)
//     {
//         if (it != numbers.begin())
//             std::cout << " ";
//         std::cout << *it;
//     }
//     std::cout << std::endl;
// }


// int main(int argc, char **argv)
// {
//     if (argc < 2)
//     {
//         std::cerr << "Error: provide positive integers" << std::endl;
//         return 1;

//     }
//     try
//     {
//         std::vector<int> numbers;

//         for (int i = 1; i < argc; ++i)
//             numbers.push_back(parsePositiveInt(argv[i]));

//         std::cout << "Before: ";
//         printNumbers(numbers);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << "Error: " << e.what() << std::endl;
//         return 1;
//     }

//     return 0;
// }
