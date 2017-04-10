/* https://www.codewars.com/kata/strings-mix */

#include <string>
#include <cctype>
#include <iostream>
#include <map>
#include <algorithm>

class Mix
{
public:

    static char used_mark;

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

    static void Sort_Counters(std::multimap<int, char> &first_string_counter_sorted, std::map<char, int> &first_string_counter,
                              std::multimap<int, char> &second_string_counter_sorted, std::map<char, int> &second_string_counter)
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

    static bool Is_One_String_Completed(std::string &result, std::multimap<int, char> &first_string_counter_sorted,
                                        std::multimap<int, char> &second_string_counter_sorted,
                                        const int max_occurences_one, const int max_occurences_two)
    {
        auto first_char_iter = first_string_counter_sorted.find(max_occurences_one);
        char first_character = first_char_iter->second;
        auto second_char_iter = second_string_counter_sorted.find(max_occurences_two);
        char second_character = second_char_iter->second;

        if(max_occurences_one == -1) //Means second string is not empty yet.
        {
            result.append("2:");
            Add_Letter_N_times(result, second_character, max_occurences_two);
            second_char_iter->second = used_mark;

            result.push_back('/');
            return true;
        }
        else if(max_occurences_two == -1) //Means first string is not empty yet.
        {
            result.append("1:");
            Add_Letter_N_times(result, first_character, max_occurences_one);
            first_char_iter->second = used_mark;

            result.push_back('/');
            return true;
        }

        return false;
    }

    static decltype(auto) Get_Maximum_Element(std::multimap<int, char> &string_counter_sorted)
    {
        while(1)
        {
            if(string_counter_sorted.empty())
                return string_counter_sorted.end();

            auto max_occurence_iterator = std::max_element(string_counter_sorted.begin(), string_counter_sorted.end());

            std::cout << "Secon = " << max_occurence_iterator->second << "\n";

            /* If longest letters are marked as already used, delete them. */
            if(max_occurence_iterator->second == used_mark)
                string_counter_sorted.erase(max_occurence_iterator);
            else
                return max_occurence_iterator;
        }
    }

    static void Put_by_Lexical_Order(int max_occurences_one, int max_occurences_two, char first_character,
                                     char second_character, std::string &result)
    {
        if(first_character > second_character)
        {
            result.append("1:");
            Add_Letter_N_times(result, first_character, max_occurences_one);
        }
        else if(second_character > first_character)
        {
            result.append("2:");
            Add_Letter_N_times(result, second_character, max_occurences_two);
        }
    }

    static void Put_Elements(std::string &result, std::multimap<int, char> &first_string_counter_sorted,
                             std::multimap<int, char> &second_string_counter_sorted)
    {

        while(1) //Loop will end when max_occurences_one == -1 && max_occurences_two == -1
        {
            /* Create function: Delete_Zeros, and let it be at the top of the loop, to garbage collect used items. */

            auto max_occurences_one = Get_Maximum_Element(first_string_counter_sorted);
            auto max_occurences_two  = Get_Maximum_Element(second_string_counter_sorted);

            if(max_occurences_one->first == -1 && max_occurences_two->first == -1)
                break;

            if(Is_One_String_Completed(result, first_string_counter_sorted, second_string_counter_sorted,
                                       max_occurences_one->first, max_occurences_two->first))
                continue;

            char first_character = max_occurences_one->second;
            char second_character = max_occurences_two->second;

            if(max_occurences_one->first > max_occurences_two->first)
            {
                result.append("1:");
                Add_Letter_N_times(result, first_character, max_occurences_one->first);
                max_occurences_one->second = used_mark;
            }
            else if(max_occurences_two->first > max_occurences_one->first)
            {
                result.append("2:");
                Add_Letter_N_times(result, second_character, max_occurences_two->first);
                max_occurences_two->second = used_mark;
            }
            else if(max_occurences_one->first == max_occurences_two->first)
            {
                /* If letters are the same */
                if(first_character == second_character)
                {
                    result.append("=:");
                    Add_Letter_N_times(result, first_character, max_occurences_one->first);
                }
                /* If letters are not the same */
                else
                {
                    Put_by_Lexical_Order(max_occurences_one->first, max_occurences_two->first, first_character,
                                         second_character, result);
                }

                max_occurences_one->second = used_mark;
                max_occurences_two->second = used_mark;
            }

            result.push_back('/');
        }
    }

    static void Remove_Empty_Counters(std::map<char, int> &first_string_counter,
                                      std::map<char, int> &second_string_counter)
    {
        for(auto iter = first_string_counter.begin(); iter != first_string_counter.end(); ++iter)
        {
            if(iter->second == 0) //Means a string doesn't have this letter.
            {
                first_string_counter.erase(iter);
                iter = first_string_counter.begin();
            }
        }

        for(auto iter = second_string_counter.begin(); iter != second_string_counter.end(); ++iter)
        {
            if(iter->second == 0) //Means a string doesn't have this letter.
            {
                iter = second_string_counter.erase(iter);
                iter = second_string_counter.begin();
            }
        }
    }

    static std::string mix(const std::string &s1, const std::string &s2)
    {
        std::map<char, int> first_string_counter;
        std::map<char, int> second_string_counter;

        Fill_Counters(first_string_counter, s1, second_string_counter, s2);
        Remove_Empty_Counters(first_string_counter, second_string_counter);

        std::multimap<int, char> first_string_counter_sorted;
        std::multimap<int, char> second_string_counter_sorted;

        Sort_Counters(first_string_counter_sorted, first_string_counter, second_string_counter_sorted, second_string_counter);

        std::string result = "";

        Put_Elements(result, first_string_counter_sorted, second_string_counter_sorted);

        //I could compare two max elements from both maps. The bigger one is saved, and then I compare again.
        //If two elements are the same, I check if they have same letters or not.
        //If yes, then I put them as '=:'. If not, then I put them sorted lexically.

        return result;
    }
};


char Mix::used_mark = '0';




















