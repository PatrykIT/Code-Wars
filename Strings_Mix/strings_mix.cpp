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
        //I need to return 'aa', not 'ee' first. So gotta search all biggest elements, and return by lexical order.
        while(1)
        {
            if(string_counter_sorted.empty())
                return string_counter_sorted.end();

            auto max_occurence_iterator = std::max_element(string_counter_sorted.begin(), string_counter_sorted.end());

            if(max_occurence_iterator->second == used_mark)
            {
                std::cout << "Deletion in Get_Maximum_Element shouldn't happen. Deleted item int: "
                          << max_occurence_iterator->first << "\n";
                string_counter_sorted.erase(max_occurence_iterator);
                continue;
            }


            std::cout << "Second = " << max_occurence_iterator->second << "\n";

            /* For example: 'ee' and 'aa' both are same keys (2). I then need to return 'aa', not 'ee'. */
            bool has_repeating_keys = string_counter_sorted.count(max_occurence_iterator->first) > 1;
            if(has_repeating_keys)
            {
                /* Find biggest letter. */
                auto all_same_keys = string_counter_sorted.equal_range(max_occurence_iterator->first);

                auto begin_iter = all_same_keys.first;
                auto end_iter = all_same_keys.second;

                std::multimap<int, char>::iterator biggest_letter;
                char biggest_number = 'z' + 1;

                for(std::multimap<int, char>::iterator iter = begin_iter; iter != end_iter; ++iter)
                {
                    if(iter->second < biggest_number)
                    {
                        biggest_letter = iter;
                        biggest_number = iter->second;
                    }
                }

                max_occurence_iterator = biggest_letter;
            }

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

    static void Delete_Zeros(std::multimap<int, char> &to_check_and_delete)
    {
        for(auto iter = to_check_and_delete.begin(); iter != to_check_and_delete.end(); ++iter)
        {
            /* Remove character that was used from the map. */
            if(iter->second == used_mark)
            {
                to_check_and_delete.erase(iter);
                if(!to_check_and_delete.empty())
                    iter = to_check_and_delete.begin();
                else
                    return;
            }
        }
    }


    static void Remove_Letter(std::multimap<int, char> &delete_from, char letter_to_delete)
    {
        for(auto iter = delete_from.begin(); iter != delete_from.end(); ++iter)
        {
            if(iter->second == letter_to_delete)
            {
                delete_from.erase(iter);
                return;
            }
        }
    }

    static void Put_Elements(std::string &result, std::multimap<int, char> &first_string_counter_sorted,
                             std::multimap<int, char> &second_string_counter_sorted)
    {

        while(1) //Loop will end when max_occurences_one == -1 && max_occurences_two == -1
        {
            /* Create function: Delete_Zeros, and let it be at the top of the loop, to garbage collect used items. */

            Delete_Zeros(first_string_counter_sorted);
            Delete_Zeros(second_string_counter_sorted);

            auto max_occurences_one = Get_Maximum_Element(first_string_counter_sorted);
            auto max_occurences_two  = Get_Maximum_Element(second_string_counter_sorted);

            if(max_occurences_one == first_string_counter_sorted.end() &&
                    max_occurences_two == second_string_counter_sorted.end())
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
                /* Delete from the second string the same letter, because this string won. */
                Remove_Letter(second_string_counter_sorted, max_occurences_one->second);
                max_occurences_one->second = used_mark;
            }
            else if(max_occurences_two->first > max_occurences_one->first)
            {
                result.append("2:");
                Add_Letter_N_times(result, second_character, max_occurences_two->first);
                Remove_Letter(first_string_counter_sorted, max_occurences_two->second);
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

    /** Removes letters that have count 0 or 1. */
    static void Remove_Empty_Counters(std::map<char, int> &first_string_counter,
                                      std::map<char, int> &second_string_counter)
    {
        for(auto iter = first_string_counter.begin(); iter != first_string_counter.end(); ++iter)
        {
            if(iter->second < 2)
            {
                first_string_counter.erase(iter);
                iter = first_string_counter.begin();
            }
        }

        for(auto iter = second_string_counter.begin(); iter != second_string_counter.end(); ++iter)
        {
            if(iter->second < 2)
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




















