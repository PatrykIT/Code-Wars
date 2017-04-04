#include <iostream>
#include <vector>
#include <algorithm>


void Fill_Empty_Lines(std::vector<size_t> &indexes_that_need_hash, int biggest_number, int last_biggest_number, std::string &result)
{
    size_t difference_between_numbers = last_biggest_number - biggest_number;

    /* Between example 10 and 7 there are 2 empty lines, and third has a nr. 7, not hash.
     * This loop fills empty lines. */
    for(size_t iteration = 0; iteration < difference_between_numbers -1; ++iteration) //-1 because the last one will be a number
    {
        size_t iterate_up_to_index = *std::max_element(indexes_that_need_hash.begin(),
                                                       indexes_that_need_hash.end());

        /* This loop iterates one single line, and marks each place on this line as # or space. */
        for(size_t index = 0; index <= iterate_up_to_index; ++index)
        {
            /* Check if given index in string should be marked as '#' or ' '. */
            auto found = std::find(indexes_that_need_hash.begin(), indexes_that_need_hash.end(), index);

            if(found != indexes_that_need_hash.end())
                result.push_back('#');
            else
                result.push_back(' ');
        }

        result.append("\n");
    }
}

void Add_Line_with_Number(std::vector<size_t> &indexes_that_need_hash, int current_biggest_number, std::vector<int> &results_numbers, std::string &result)
{
    size_t iterate_up_to_index = *std::max_element(indexes_that_need_hash.begin(),
                                                   indexes_that_need_hash.end());

    std::cout << "I will iterate until: " << iterate_up_to_index << "\n";
    bool biggest_number_saved = false;

    /* This loop iterates one single line, and marks each place on this line as # or space. */
    for(size_t index = 0; index <= iterate_up_to_index; ++index)
    {
        /* Check if given index in string should be marked as '#' or ' '. */
        auto found = std::find(indexes_that_need_hash.begin(), indexes_that_need_hash.end(), index);

        if(found != indexes_that_need_hash.end())
        {
            /* If we currently are on index with current biggest number, and it was not saved yet. */
            if(results_numbers.at(*found) == current_biggest_number && biggest_number_saved == false)
            {
                result.append(std::to_string(current_biggest_number));
                biggest_number_saved = true;
            }
            else
                result.push_back('#');
        }
        else
            result.push_back(' ');
    }

    result.append("\n");
}


std::string histogram(std::vector<int> results_numbers)
{
    std::string result = "";
    std::vector<size_t> indexes_that_need_hash;

    /* Putting biggest number */
    std::vector<int>::iterator biggest_number_iterator = std::max_element(results_numbers.begin(), results_numbers.end());
    int biggest_number = *biggest_number_iterator;
    size_t index_of_biggest_number = std::distance(results_numbers.begin(), biggest_number_iterator);
    indexes_that_need_hash.push_back(index_of_biggest_number);

    for(size_t i = 0; i < index_of_biggest_number; ++i)
    {
        result.push_back(' ');
    }
    result.insert(index_of_biggest_number, std::to_string(biggest_number) + "\n");


    /* Putting rest of numbers */



    /* The problem is that I delete elements, and indexes change places.
     * I could make a copy of vector and take biggest number from the false one and then delete this number,
     * and take indexes from original vector.
     *
     * That is good, but let's think of something that doesn't involve creating a second vector. */
    while(!results_numbers.empty())
    {
        int last_biggest_number = biggest_number;
        results_numbers.erase(biggest_number_iterator);

        biggest_number_iterator = std::max_element(results_numbers.begin(), results_numbers.end());
        biggest_number = *biggest_number_iterator;
        index_of_biggest_number = std::distance(results_numbers.begin(), biggest_number_iterator);

        Fill_Empty_Lines(indexes_that_need_hash, biggest_number, last_biggest_number, result);

        /* Mark which index should have #. It will be marked in a loop. Indexes not in vector will have a space. */
        indexes_that_need_hash.push_back(index_of_biggest_number);

        Add_Line_with_Number(indexes_that_need_hash, biggest_number, results_numbers, result);

//        size_t iterate_up_to_index = *std::max_element(indexes_that_need_hash.begin(), indexes_that_need_hash.end());

//        /* This loop iterates one single line, and marks each place on this line as # or space. */
//        for(size_t index = 0; index < iterate_up_to_index; ++index)
//        {
//            /* Check if given index in string should be marked as # or space. */
//            auto found = std::find(indexes_that_need_hash.begin(), indexes_that_need_hash.end(), index);
//            if(found != indexes_that_need_hash.end())
//                result.push_back('#');
//            else
//                result.push_back(' ');
//        }
//        result.append("\n");
    }









    return result;
}


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
