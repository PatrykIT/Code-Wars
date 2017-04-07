/* https://www.codewars.com/kata/strings-mix */

#include <string>
#include <cctype>
#include <iostream>
#include <map>

class Mix
{
public:

    static bool Is_a_z(const char letter)
    {
        return std::isalpha(letter) && std::islower(letter);
    }

    static void Fill_Counters(std::map<char, int> &first_string_counter, const std::string &s1,
                       std::map<char, int> &second_string_counter, const std::string &s2)
    {
        /* Fill maps as [a - z] and occurences. */
        for(char c = 'a'; c != 'z' +1; ++c)
        {
            first_string_counter.emplace(c, 0);
            second_string_counter.emplace(c, 0);
        }

        for(char letter : s1)
        {
            if(Is_a_z(letter))
            {
                first_string_counter.at(letter) += 1;
            }
        }

        for(char letter : s2)
        {
            if(Is_a_z(letter))
            {
                second_string_counter.at(letter) += 1;
            }
        }
    }

    static std::string mix(const std::string &s1, const std::string &s2)
    {
        std::map<char, int> first_string_counter;
        std::map<char, int> second_string_counter;

        Fill_Counters(first_string_counter, s1, second_string_counter, s2);

        return "";
    }
};
