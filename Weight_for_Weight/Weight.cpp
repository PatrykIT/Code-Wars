#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

class WeightSort
{
public:

    static unsigned long long Convert_Vector_to_Number(std::vector<unsigned long long> &numbers)
    {
        unsigned long long result = numbers.back(); //Save first digit.
        int counter = numbers.size() -2; //We will be saving digits from the back.
        int multiply_level = numbers.size() -1; //How many times should multiplyer be multiplied by 10
        unsigned long long start_multiply = 10; //We will be multiplying numbers * 10, then * 100, then * 1000 and so on..

        for(int i = 0; i < multiply_level; ++i)
        {
            result += start_multiply * numbers.at(counter);
            start_multiply *= 10;
            --counter;
        }

        return result;
    }

    static std::vector<unsigned long long> Convert_String_to_Vector(const std::string &strng)
    {
        std::vector<unsigned long long> weights;
        std::vector<unsigned long long> current_number;

        //Get number until space.
        for(auto &number : strng)
        {
            if(number != ' ')
            {
                current_number.emplace_back(number - '0'); //Convert from char to int.
            }
            else
            {
                auto whole_number = Convert_Vector_to_Number(current_number); //Convert number from vector to one int.
                weights.emplace_back(whole_number);
                current_number.clear();
            }
        }

        auto whole_number = Convert_Vector_to_Number(current_number); //Get last thing from buffer
        weights.emplace_back(whole_number);

        return weights;
    }

    static unsigned long long Sum_Digits(int number)
    {
        int a, sum = 0;
        while(number > 0)
        {
            a = number % 10;
            number = number / 10;
            sum = sum + a;
        }

        return sum;
    }

    static std::vector<unsigned long long> Sort_Weights(std::vector<unsigned long long> &weights)
    {
        /* Key: original weight. Value: Weight after addition of all digits. */
        std::multimap<unsigned long long, unsigned long long> weights_dictionary;

        for(auto &nr : weights)
        {
            weights_dictionary.insert({nr, Sum_Digits(nr)});
        }

        //Now we have i.e. [100 - 1], [99 - 18]
        //Now we need to sort keys by their values :D So the smallest value goes first, and we save its key.

        std::vector<unsigned long long> result;
        while(weights_dictionary.size() > 0)
        {
            auto minimum_value = std::min_element(weights_dictionary.begin(), weights_dictionary.end(),
                                                  [] (const std::pair<int, int> &numbers, const std::pair<int, int> &numbers_2) {return numbers.second < numbers_2.second;} ); //Lookup by values, not keys!

            result.emplace_back(minimum_value->first); //Add by keys, not values!
            weights_dictionary.erase(minimum_value);
        }

        return result;
    }

    static void Reorder_Repeating_Weights(std::vector<unsigned long long> &numbers)
    {
        //We know repeating numbers will be next to each other.

        for(auto it = numbers.begin(); it != numbers.end() -1; ++it)
        {
            unsigned long long first_number = Sum_Digits(*it);
            unsigned long long second_number = Sum_Digits(*(it +1));

            if(first_number == second_number)
            {
                std::string first_number_string {std::to_string(*it)};
                std::string second_number_string {std::to_string(*(it +1))};

                if(first_number_string > second_number_string) //If first is bigger, then he needs to be swapped.
                {
                    std::swap(*it, *(it +1));
                }
            }
        }
    }

    static std::string orderWeight(const std::string &strng)
    {
        if(strng.empty())
            return {};

        std::cout << strng << std::endl;

        std::vector<unsigned long long> weights = Convert_String_to_Vector(strng);
        weights = Sort_Weights(weights);
        Reorder_Repeating_Weights(weights);


        std::string string_result;

        for(auto &nr : weights)
        {
            string_result.append(std::to_string(nr));
            string_result.push_back(' ');
        }

        string_result.pop_back(); //Delete last whitespace
        return string_result;
    }
};
