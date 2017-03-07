#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>

class SumSquaredDivisors
{
public:
    /* 1. Save all divisors of a number.
       2. Square all the numbers.
       3. Sum all the numbers.
       4. Check if this sum is a square.
       5. If yes, then save it as {original_number, sum_of_squared_numbers_for_this_number}.
    */
    using big = unsigned long long;

    static std::vector<big> Get_Divisors_of_a_Number(big number)
    {
        std::vector<big> divisors;
        for(big i = 1; i <= number ; ++i)
        {
            if(number % i == 0)
                divisors.push_back(i);
        }

        return divisors;
    }

    static void Square_Numbers(std::vector<big> &divisors)
    {
        for(auto &nr : divisors)
            nr *= nr;
    }

    static big Sum_Squares(std::vector<big> &squares)
    {
        big sum = 0;
        for(auto &nr : squares)
            sum += nr;
        return sum;
    }

    static bool Is_Square(big number)
    {
        auto root = std::round(std::sqrt(number)); //Without std::round, it worked on my PC, but on the website, it gave wrong results ;) Lookout for those mines in code.
        return number == (root * root);
    }

    static std::string listSquared(long long m, long long n)
    {
        std::vector<big> all_numbers_to_check ( (n - m) +1);
        std::iota(all_numbers_to_check.begin(), all_numbers_to_check.end(), m);

        std::string result;

        for(auto &nr : all_numbers_to_check)
        {
            std::vector<big> divisors = Get_Divisors_of_a_Number(nr);

            Square_Numbers(divisors);
            big sum_of_squares = Sum_Squares(divisors);

            if(Is_Square(sum_of_squares))
            {
                result.append("{" + std::to_string(nr) + ", " + std::to_string(sum_of_squares) + "}"
                              +
                              ", ");
            }
        }

        result = "{" + result.substr(0, result.size() -2) + "}";
        return result;
    }
};
