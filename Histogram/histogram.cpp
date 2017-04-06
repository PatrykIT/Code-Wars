//https://www.codewars.com/kata/histogram-v1/train/cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

std::vector<int>::iterator Find_Repeating_Not_Used_Element_Index(int number, std::vector<int> &results_numbers,
                                                                 std::vector<size_t> &indexes_that_need_hash);


void Fill_Empty_Lines(std::vector<size_t> &indexes_that_need_hash, int biggest_number, int last_biggest_number,
                      std::string &result)
{
    size_t difference_between_numbers = last_biggest_number - biggest_number;

    /* Between example 10 and 7 there are 2 empty lines, and third has a nr. 7, not hash.
     * This loop fills empty lines. */

    if(difference_between_numbers > 1)
    {
        /* -1 because the last one will be a number */
        for(size_t iteration = 0; iteration < difference_between_numbers -1; ++iteration)
        {
            size_t iterate_up_to_index = *std::max_element(indexes_that_need_hash.begin(),
                                                           indexes_that_need_hash.end());

            /* This loop iterates one single line, and marks each place on this line as # or space. */
            for(size_t index = 0; index <= iterate_up_to_index; ++index)
            {
                /* Check if given index in string should be marked as '#' or ' '. */
                auto found = std::find(indexes_that_need_hash.begin(), indexes_that_need_hash.end(), index);

                if(found != indexes_that_need_hash.end())
                    result.append("# ");
                else
                    result.append("  ");
            }

            if(biggest_number != last_biggest_number)
                result.back() = '\n';
        }
    }
}

/* This function finds all repeating numbers of "current_biggest_number", adds them to indexes_that_needed_hash and
 * set maps occurences to 0. */
void Find_All_Max_Repeating_Elements(std::vector<size_t> &indexes_that_need_hash, int current_biggest_number,
                                     std::vector<int> &results_numbers, std::string &result,
                                     std::map<int, int> &repeating_numbers, size_t &numbers_analyzed_counter)
{
    int index_of_biggest_number;

    std::vector<int>::iterator element = Find_Repeating_Not_Used_Element_Index(current_biggest_number,
                                                                               results_numbers, indexes_that_need_hash);

    while(element != results_numbers.end())
    {
        index_of_biggest_number = std::distance(results_numbers.begin(), element);
        /* Add indexes. */
        indexes_that_need_hash.push_back(index_of_biggest_number);
        /* Remove from map. */
        repeating_numbers.at(current_biggest_number) -= 1;
        ++numbers_analyzed_counter;

        element = Find_Repeating_Not_Used_Element_Index(current_biggest_number,
                                                        results_numbers, indexes_that_need_hash);
    }
}

bool Is_a_Single_Digit(int number)
{
    return(number < 10);
}

void Add_Line_with_Numbers(std::vector<size_t> &indexes_that_need_hash, int current_biggest_number,
                          std::vector<int> &results_numbers, std::string &result,
                          std::map<int, int> &repeating_numbers, size_t &numbers_analyzed_counter)
{
    /* Thanks to this function, we will be able to add all repeating numbers in one line. */
    Find_All_Max_Repeating_Elements(indexes_that_need_hash, current_biggest_number,
                                    results_numbers, result, repeating_numbers, numbers_analyzed_counter);

    size_t iterate_up_to_index = *std::max_element(indexes_that_need_hash.begin(),
                                                   indexes_that_need_hash.end());

    bool biggest_number_saved = false;

    /* This loop iterates one single line, and marks each place on this line as # or space. */
    for(size_t index = 0; index <= iterate_up_to_index; ++index)
    {
        /* Check if given index in string should be marked as '#' or ' '. */
        /* HERE I need to find index that was not used previously. */
        auto found = std::find(indexes_that_need_hash.begin(), indexes_that_need_hash.end(), index);

        if(found != indexes_that_need_hash.end())
        {
            /* If we currently are on index with current biggest number, and it was not saved yet. */
            if(results_numbers.at(*found) == current_biggest_number /*&& biggest_number_saved == false*/)
            {
                if(current_biggest_number != 0)
                {
                    if(Is_a_Single_Digit(current_biggest_number))
                    {
                        result.append(std::to_string(current_biggest_number) +' ');
                    }
                    else
                    {
                        result.append(std::to_string(current_biggest_number));
                    }
                }
                else
                {
                    result.append("  ");
                }

                biggest_number_saved = true;
            }
            else
            {
                result.append("# ");
            }
        }
        else
            result.append("  ");
    }

    /* Take care not to overwrite a number (might happen if number is multi-digit). */
    if(std::isdigit(result.back()))
        result.push_back('\n');
    else
        result.back() = '\n';
}

std::vector<int>::iterator Find_Repeating_Not_Used_Element_Index(int number, std::vector<int> &results_numbers,
                                                                 std::vector<size_t> &indexes_that_need_hash)
{
    for(auto iter = results_numbers.begin(); iter != results_numbers.end(); ++iter)
    {
        if(*iter == number)
        {
            size_t index_of_iterator = std::distance(results_numbers.begin(), iter);
            /* If the index was not yet used. */
            if(std::find(indexes_that_need_hash.begin(), indexes_that_need_hash.end(), index_of_iterator)
                    == indexes_that_need_hash.end())
            {
                return iter;
            }
        }
    }

    return results_numbers.end();
}


std::vector<int>::iterator Find_Max(std::vector<int> &results_numbers, std::vector<int> &numbers_analyzed,
                                    std::map<int, int> &repeating_numbers, std::vector<size_t> &indexes_that_need_hash)
{
    int max;
    bool found_first = false;
    std::vector<int>::iterator biggest;

    for(int number : results_numbers)
    {
        if(std::find(numbers_analyzed.begin(), numbers_analyzed.end(), number) == numbers_analyzed.end()
                || repeating_numbers.at(number) > 0)
        {
            if(found_first == false)
            {
                /* Save first number that has not been analysed. */
                max = number;
                biggest = Find_Repeating_Not_Used_Element_Index(number, results_numbers, indexes_that_need_hash);
                found_first = true;
            }
            else
            {
                if(number > max)
                {
                    max = number;
                    biggest = Find_Repeating_Not_Used_Element_Index(number, results_numbers, indexes_that_need_hash);
                }
            }
        }
    }

    /* If there was a max value that wasn't analysed yet, return iterator to this value. */
    if(found_first)
    {
        repeating_numbers.at(*biggest) -= 1;
        return biggest;
    }
    else
        return results_numbers.end();
}

std::string histogram(std::vector<int> results_numbers)
{
    std::string result = "";

    int biggest_number;
    int last_biggest_number;
    size_t index_of_biggest_number;

    std::vector<int>::iterator biggest_number_iterator;
    std::vector<size_t> indexes_that_need_hash;
    std::vector<int> numbers_analyzed;

    /* Key is a number, value is how many times it occures. */
    std::map<int, int> repeating_numbers;
    /* Count how many times numbers repeat. */
    for(int number : results_numbers)
        repeating_numbers[number]++;


    size_t numbers_analyzed_counter = 0;

    /* Put biggest number */
    biggest_number_iterator = Find_Max(results_numbers, numbers_analyzed,
                                       repeating_numbers, indexes_that_need_hash);
    biggest_number = *biggest_number_iterator;
    index_of_biggest_number = std::distance(results_numbers.begin(), biggest_number_iterator);
    indexes_that_need_hash.push_back(index_of_biggest_number);
    Add_Line_with_Numbers(indexes_that_need_hash, biggest_number, results_numbers, result,
                         repeating_numbers, numbers_analyzed_counter);
    numbers_analyzed.push_back(biggest_number);


    /* Put rest of numbers */
    while(numbers_analyzed_counter != results_numbers.size())
    {
        last_biggest_number = biggest_number;

        biggest_number_iterator = Find_Max(results_numbers, numbers_analyzed,
                                           repeating_numbers, indexes_that_need_hash);

        if(biggest_number_iterator != results_numbers.end())
        {
            biggest_number = *biggest_number_iterator;
            Fill_Empty_Lines(indexes_that_need_hash, biggest_number, last_biggest_number, result);

            index_of_biggest_number = std::distance(results_numbers.begin(), biggest_number_iterator);
            numbers_analyzed.push_back(biggest_number);

            /* Mark which index should have #. It will be marked in a loop. Indexes not in vector will have a space. */
            indexes_that_need_hash.push_back(index_of_biggest_number);

            /* Here I repeat this 3 times for 7, thats why it grows. I should call it once, and it would save all 7's.
             * That would be correct, because repeating numbers need to be on the same line. */
            Add_Line_with_Numbers(indexes_that_need_hash, biggest_number, results_numbers, result,
                                 repeating_numbers, numbers_analyzed_counter);
        }

        ++numbers_analyzed_counter;
    }

    /* If there was no 0 number, we have to call function again so that it would fill # up until 0. */
    if(std::find(results_numbers.begin(), results_numbers.end(), 0) == results_numbers.end())
    {
        Fill_Empty_Lines(indexes_that_need_hash, -1, last_biggest_number, result);
    }

    //If all numbers are 0, erase whole line.
    if(std::all_of(results_numbers.begin(), results_numbers.end(), [](const int number) { return number == 0; }))
    {
        result.clear();
    }

    result.append("-----------\n");
    result.append("1 2 3 4 5 6\n");

    return result;
}

        //      12
        //    11#
        //    # #
        //    # #
        //    # #
        //  7 # # 7 7
        //  # # # # # 6
        //  # # # # # #
        //  # # # # # #
        //  # # # # # #
        //  # # # # # #
        //  # # # # # #
        //  # # # # # #
        //  -----------
        //  1 2 3 4 5 6





/*          expected = "    10\n"
                       "    #\n"
                       "    #\n"
                       "7   #\n"
                       "#   #\n"
                       "#   #     5\n"
                       "#   #     #\n"
                       "# 3 #     #\n"
                       "# # #     #\n"
                       "# # # 1   #\n"
                       "# # # #   #\n"
                       "-----------\n"
                       "1 2 3 4 5 6\n";

*/
