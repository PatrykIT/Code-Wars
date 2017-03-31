#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

class RemovedNumbers
{
public:

    static unsigned long long Get_Sum_Of_Numbers(long long n)
    {
        unsigned long long sum_of_numbers = 0;
        for(int number = n; number >= 0 ; --number)
        {
            sum_of_numbers += number;
        }
        return sum_of_numbers;
    }

    static std::vector<std::vector<long long>> removNb(long long n)
    {
        std::cout << "N = " << n << "\n";
        std::vector<std::vector<long long>> returner;
        unsigned long long sum_of_numbers = Get_Sum_Of_Numbers(n);

        std::vector<unsigned long long> numbers (n, 0);
        std::iota(numbers.begin(), numbers.end(), 1);

        for(long long number : numbers)
        {
            for(long long number_2 : numbers)
            {
                unsigned long long product_of_a_b = number * number_2;
                unsigned long long sum_without_a_b = sum_of_numbers - number - number_2;

                if(product_of_a_b == sum_without_a_b)
                {
                    /* Add (a, b) and (b, a) */
                    returner.push_back({number, number_2}); //Try with emplace_back next
                }
            }
        }

        if(!returner.empty())
            return returner;
        else
            return {};
    }
};
