#include <string>
#include <vector>
#include <map>


bool Is_Closing_Bracket(char brace)
{
    return brace == ']' || brace == '}' || brace == ')';
}

bool Check_If_All_Elements_Closed(std::map<char, int> &braces_counter)
{
    for(std::pair<char, int> counter : braces_counter)
    {
        if(counter.second != 0)
            return false;
    }

    return true;
}

bool Find_Closing_Element(std::vector<char> &all_braces, std::vector<char>::iterator searched_element)
{
    if(*searched_element == ']' || *searched_element == '}' || *searched_element == ')')
        throw std::invalid_argument ("Function takes only opening brackets! Error argument: " + *searched_element);

    std::map<char, char> opposite_braces = {
                                             {']', '['},
                                             {'}', '{'},
                                             {')', '('}
                                           };

    std::map<char, int> braces_counter = {
                                            {'[', 0},
                                            {']', 0},
                                            {'{', 0},
                                            {'}', 0},
                                            {'(', 0},
                                            {')', 0}
                                         };

    /* Mark looked for element as first occurence */
    braces_counter.at(*searched_element) += 1;

    char original_element = *searched_element;
    ++searched_element;

    while(braces_counter.at(original_element) != 0)
    {
        if(searched_element != all_braces.end())
        {
            if(Is_Closing_Bracket(*searched_element))
            {
                /* Decrement opening bracket */
                braces_counter.at(opposite_braces.at(*searched_element)) -= 1;
            }
            else
            {
                /* Increment opening bracket */
                braces_counter.at(*searched_element) += 1;
            }

            ++searched_element;
        }
        else
            break;

    }

    return Check_If_All_Elements_Closed(braces_counter);
}


bool valid_braces(std::string braces)
{
    std::vector<char> all_braces;

    int opening_braces = 0;
    int closing_braces = 0;

    for(char brace : braces)
    {
        all_braces.emplace_back(brace);
        if(Is_Closing_Bracket(brace))
            ++closing_braces;
        else
            ++opening_braces;
    }

    if(opening_braces != closing_braces)
        return false;

    /* Check for invalid input, like: )[]{} */
    if(Is_Closing_Bracket(all_braces.at(0)))
        return false;

    for(auto braces_iterator = all_braces.begin(); braces_iterator != all_braces.end(); ++braces_iterator)
    {
        /* Do search only by opening brackets */
        if(Is_Closing_Bracket(*braces_iterator) == false)
        {
            if(Find_Closing_Element(all_braces, braces_iterator) == false)
                return false;
        }
    }


    return true;
}
