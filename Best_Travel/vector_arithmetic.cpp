
namespace Vector_Multiplication
{

    std::vector<std::vector<int>> Multiply_Vectors(std::vector<int> &multiplayer, std::vector<int> &numbers)
    {
        std::vector<std::vector<int>> holding_numbers; //Use std::deque in future (faster front insertions)
        int current_depth = 0, carry = 0;
        bool is_carry_available = false;

        /* Start with 5, then 1. Multiply 5 by 3, then 2, then 1. */
        for(auto multiplayer_it = multiplayer.rbegin(); multiplayer_it != multiplayer.rend(); ++multiplayer_it)
        {
            for(auto numbers_it = numbers.rbegin(); numbers_it != numbers.rend(); ++numbers_it)
            {
                /* Multiply individual integers */
                int result = (*multiplayer_it) * (*numbers_it);

                /* If there is a "rest" from previous multiplication, add it here. I.e: 5 * 3 = 15. 5 is written, and 1 is saved as a carry, which would be added here. */
                if(is_carry_available == true)
                {
                    result += carry;
                    is_carry_available = false;
                }

                /* If sum is bigger then one integer */
                if(result > 9)
                {
                    carry = result / 10; //Value to be moved to the next integer
                    result = result % 10;
                    is_carry_available = true;

                    /* If we reached the end of numbers to multiply */
                    if(numbers_it == numbers.rend() -1)
                    {
                        /* Push front: carry, rest. So it would be: [carry, rest, x, y, z] */
                        holding_numbers.at(current_depth).insert(holding_numbers[current_depth].begin(), result); //TO DO: There should be an if checking if vector to insert is empty. Same check as below.
                        holding_numbers.at(current_depth).insert(holding_numbers[current_depth].begin(), carry);
                        is_carry_available = false;
                        continue;
                    }
                }
                if(holding_numbers.begin() + current_depth == holding_numbers.end())
                {
                    holding_numbers.emplace_back(std::vector<int> {result}); //Will put a std::vector with first value.
                }
                else
                {
                    holding_numbers.at(current_depth).insert(holding_numbers[current_depth].begin(), result);
                }

            }
            ++current_depth;
        }

        return holding_numbers;
    }

    void Vectors()
    {
        std::vector<int> multiplayer {1, 5}; //TODO: This have to be automated, to transform int to std::vector<int>
        std::vector<int> numbers {1, 2, 3};
        int number_2 = 15;

        int number_of_digits = 0;
        auto count_digits = [number_2, &number_of_digits]() mutable -> int { while(number_2) { ++number_of_digits; number_2 /= 10; } return number_of_digits; };
        int numbers_of_holding_vectors = count_digits();

        std::vector<std::vector<int>> holding_numbers = Multiply_Vectors(multiplayer, numbers);

        /* Before addition, we need to fill vector with 0's in the empty places. */

    }

    #include <cassert>
    void Test_Vector_Multiplication()
    {
        std::vector<std::vector<int>> result;

        std::vector<int> first {1, 5};;
        std::vector<int> second {1, 2, 3};
        result = Multiply_Vectors(first, second);
        std::cout << (result[0])[0] << "\n";
        assert(result[0][2] == 5 && result[0][1] == 1 && result[0][0] == 6);
        assert(result[1][2] == 3 && result[1][1] == 2 && result[1][0] == 1);

    }
}
