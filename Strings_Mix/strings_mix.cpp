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
        result.push_back('/');
    }

    static bool Is_One_String_Completed(std::string &result, std::multimap<int, char> &first_string_counter_sorted,
                                        std::multimap<int, char> &second_string_counter_sorted,
                                        std::multimap<int, char>::iterator max_occurences_one,
                                        std::multimap<int, char>::iterator max_occurences_two)
    {

        if(max_occurences_one != first_string_counter_sorted.end() &&
                max_occurences_two != second_string_counter_sorted.end())
            return false;

        char first_character = 'Z';
        char second_character = 'Z';

        if(max_occurences_one != first_string_counter_sorted.end())
            first_character = max_occurences_one->second;

        if(max_occurences_two != second_string_counter_sorted.end())
            second_character = max_occurences_two->second;

        if(max_occurences_one == first_string_counter_sorted.end()) //Means second string is not empty yet.
        {
            result.append("2:");
            Add_Letter_N_times(result, second_character, max_occurences_two->first);
            max_occurences_two->second = used_mark;
            return true;
        }
        else if(max_occurences_two == second_string_counter_sorted.end()) //Means first string is not empty yet.
        {
            result.append("1:");
            Add_Letter_N_times(result, first_character, max_occurences_one->first);
            max_occurences_one->second = used_mark;
            return true;
        }

        return false;
    }

    static std::multimap<int, char>::iterator Get_Maximum_Element(std::multimap<int, char> &string_counter_sorted)
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


    static void Put_by_Lexical_Order(std::multimap<int, char>::iterator max_occurences_one,
                                     std::multimap<int, char>::iterator max_occurences_two, char first_character,
                                     char second_character, std::string &result, std::multimap<int, char> &first_str,
                                     std::multimap<int, char> &second_str)
    {
        if(first_character < second_character)
        {
            result.append("1:");
            Add_Letter_N_times(result, first_character, max_occurences_one->first);
            Remove_Letter_from_other_Map(second_str, first_character);
            max_occurences_one->second = used_mark;
        }
        else if(second_character < first_character)
        {
            result.append("2:");
            Add_Letter_N_times(result, second_character, max_occurences_two->first);
            Remove_Letter_from_other_Map(first_str, second_character);
            max_occurences_two->second = used_mark;
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

    /** Removes letter from the opposite multimap.
     * If first string had more occurences of the letter, then we need to remove this letter from the other multimap. */
    static void Remove_Letter_from_other_Map(std::multimap<int, char> &delete_from, char letter_to_delete)
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

    static void Append_Buffer(int current_number, int &last_number, std::string &to_append, std::string &result)
    {
        /* Means we can append := to the end of string, becuase it is the end of previous number. */
        if(current_number < last_number)
        {
            /* If there is something to append */
            if(to_append.empty() == false)
            {
                result.append(to_append);
                to_append.clear();
                last_number = current_number;
            }
        }
    }

    static void Put_Elements(std::string &result, std::multimap<int, char> &first_string_counter_sorted,
                             std::multimap<int, char> &second_string_counter_sorted)
    {
        int last_number = -1; // Change to max int
        int current_number = -1; // Change to max int
        std::string to_append = "";

        while(1) //Loop will end when max_occurences_one == .end() && max_occurences_two == -1
        {
            Delete_Zeros(first_string_counter_sorted);
            Delete_Zeros(second_string_counter_sorted);

            auto max_occurences_one = Get_Maximum_Element(first_string_counter_sorted);
            auto max_occurences_two  = Get_Maximum_Element(second_string_counter_sorted);

            if(max_occurences_one == first_string_counter_sorted.end() &&
                    max_occurences_two == second_string_counter_sorted.end())
                break;

            if(Is_One_String_Completed(result, first_string_counter_sorted, second_string_counter_sorted,
                                       max_occurences_one, max_occurences_two))
                continue;

            char first_character = max_occurences_one->second;
            char second_character = max_occurences_two->second;
            int number_of_occurences_one = max_occurences_one->first;
            int number_of_occurences_two = max_occurences_two->first;

            if(number_of_occurences_one > number_of_occurences_two)
            {
                current_number = number_of_occurences_one;
                Append_Buffer(current_number, last_number, to_append, result);

                result.append("1:");
                Add_Letter_N_times(result, first_character, number_of_occurences_one);
                /* Delete from the second string the same letter, because this string won. */
                Remove_Letter_from_other_Map(second_string_counter_sorted, first_character);
                max_occurences_one->second = used_mark;
            }
            else if(number_of_occurences_two > number_of_occurences_one)
            {
                current_number = number_of_occurences_two;
                Append_Buffer(current_number, last_number, to_append, result);

                result.append("2:");
                Add_Letter_N_times(result, second_character, number_of_occurences_two);
                /* Delete from the first string the same letter, because this string won. */
                Remove_Letter_from_other_Map(first_string_counter_sorted, second_character);
                max_occurences_two->second = used_mark;
            }
            else if(number_of_occurences_one == number_of_occurences_two)
            {
                current_number = number_of_occurences_one;

                /* If letters are the same */
                if(first_character == second_character)
                {   
                    /* Here I should change so that letters are only pushed back at the end of same number (int). */
                    last_number = number_of_occurences_one;
                    to_append.append("=:");
                    Add_Letter_N_times(to_append, first_character, number_of_occurences_one);
                    max_occurences_one->second = used_mark;
                    max_occurences_two->second = used_mark;
                }
                /* If letters are not the same */
                else
                {
                    Append_Buffer(current_number, last_number, to_append, result);
                    Put_by_Lexical_Order(max_occurences_one, max_occurences_two,
                                         first_character, second_character, result,
                                         first_string_counter_sorted, second_string_counter_sorted);
                }
            }
        }

        if(!to_append.empty())
        {
            result.append(to_append);
            to_append.clear();
        }

        result.pop_back(); //Delete last, unnecesary '/'
    }

    /** Removes letters that have count 0 or 1. */
    static void Remove_Empty_Counters(std::map<char, int> &first_string_counter,
                                      std::map<char, int> &second_string_counter)
    {
        auto iter = first_string_counter.begin();
        while ( (iter = std::find_if(iter, first_string_counter.end(), [&](std::pair<char, int> element)
                                        { return element.second < 2; } ) )
              != first_string_counter.end())
        {
            first_string_counter.erase(iter++);
        }

        iter = second_string_counter.begin();
        while ( (iter = std::find_if(iter, second_string_counter.end(), [&](std::pair<char, int> element)
                                        { return element.second < 2; } ))
              != second_string_counter.end() )
        {
            second_string_counter.erase(iter++);
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

        Sort_Counters(first_string_counter_sorted, first_string_counter,
                      second_string_counter_sorted, second_string_counter);

        std::string result = "";

        Put_Elements(result, first_string_counter_sorted, second_string_counter_sorted);

        //I could compare two max elements from both maps. The bigger one is saved, and then I compare again.
        //If two elements are the same, I check if they have same letters or not.
        //If yes, then I put them as '=:'. If not, then I put them sorted lexically.

        return result;
    }
};


char Mix::used_mark = '0';

/* When you have := they need to be at the end of the same count. Alphabet doesn't matter.
 * For example:
 *
 * 2:dd/2:ff/2:ii/2:rr/=:ee/=:ss
 *
 * */


















