/* https://www.codewars.com/kata/strings-mix */

#include <string>
#include <cctype>
#include <iostream>
#include <map>
#include <algorithm>

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
                first_string_counter.at(letter) += 1;
        }

        for(char letter : s2)
        {
            if(Is_a_z(letter))
                second_string_counter.at(letter) += 1;
        }
    }

    static void Sort_Counters(std::map<int, char> &first_string_counter_sorted, std::map<char, int> &first_string_counter,
                              std::map<int, char> &second_string_counter_sorted, std::map<char, int> &second_string_counter)
    {
        for(auto element : first_string_counter)
            first_string_counter_sorted.emplace(element.second, element.first);
        for(auto element : second_string_counter)
            second_string_counter_sorted.emplace(element.second, element.first);
    }

    static void Add_Letter_N_times(std::string &result, char letter, int how_many)
    {
        for(int i = 0; i < how_many; ++i)
            result.push_back(letter);
    }

    static bool Is_Empty(std::string &result, std::map<int, char> &first_string_counter_sorted,
                          std::map<int, char> &second_string_counter_sorted, const int max_occurences_one, const int max_occurences_two)
    {
        if(max_occurences_one == -1 && max_occurences_two == -1)
            return true;
        else if(max_occurences_one == -1) //Means second string is not empty yet.
        {
            result.append("2:");
            Add_Letter_N_times(result, second_string_counter_sorted.at(max_occurences_two), max_occurences_two);
            second_string_counter_sorted.at(max_occurences_two) = -1;

            result.push_back('/');
            return true;
        }
        else if(max_occurences_two == -1) //Means first string is not empty yet.
        {
            result.append("1:");
            Add_Letter_N_times(result, first_string_counter_sorted.at(max_occurences_one), max_occurences_one);
            first_string_counter_sorted.at(max_occurences_one) = -1;

            result.push_back('/');
            return true;
        }

        return false;
    }

    static void Put_Elements(std::string &result, std::map<int, char> &first_string_counter_sorted,
                             std::map<int, char> &second_string_counter_sorted)
    {
        auto max_occurence = std::max_element(first_string_counter_sorted.begin(), first_string_counter_sorted.end());
        int max_occurences_one = max_occurence->first;

        max_occurence = std::max_element(second_string_counter_sorted.begin(), second_string_counter_sorted.end());
        int max_occurences_two  = max_occurence->first;

        if(Is_Empty(result, first_string_counter_sorted, second_string_counter_sorted, max_occurences_one, max_occurences_two))
            return;

        if(max_occurences_one > max_occurences_two)
        {
            result.append("1:");
            Add_Letter_N_times(result, first_string_counter_sorted.at(max_occurences_one), max_occurences_one);
            first_string_counter_sorted.at(max_occurences_one) = -1;
        }
        else if(max_occurences_two > max_occurences_one)
        {
            result.append("2:");
            Add_Letter_N_times(result, second_string_counter_sorted.at(max_occurences_two), max_occurences_two);
            second_string_counter_sorted.at(max_occurences_two) = -1;
        }
        else if(max_occurences_one == max_occurences_two)
        {
            /* If letters are the same */
            if(first_string_counter_sorted.at((max_occurences_one)) == second_string_counter_sorted.at(max_occurences_two))
            {

            }
            else
            {
                //Do lexical sorting
            }
        }

        result.push_back('/');
    }

    static std::string mix(const std::string &s1, const std::string &s2)
    {
        std::map<char, int> first_string_counter;
        std::map<char, int> second_string_counter;

        Fill_Counters(first_string_counter, s1, second_string_counter, s2);

        std::map<int, char> first_string_counter_sorted;
        std::map<int, char> second_string_counter_sorted;

        Sort_Counters(first_string_counter_sorted, first_string_counter, second_string_counter_sorted, second_string_counter);


        std::string result = "";

        Put_Elements(result, first_string_counter_sorted, second_string_counter_sorted);

        //I could compare two max elements from both maps. The bigger one is saved, and then I compare again.
        //If two elements are the same, I check if they have same letters or not.
        //If yes, then I put them as '=:'. If not, then I put them sorted lexically.

        return "";
    }
};






















