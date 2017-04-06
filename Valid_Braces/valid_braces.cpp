#include <string>
#include <stack>

bool valid_braces(std::string braces)
{
    bool is_perfect = false;
    std::stack<char> braces;

    for(char brace : braces)
    {
        braces.push(brace);
    }

    while(!braces.empty())
    {
        char last_brace = braces.top();

        braces.pop();

        if(!braces.empty())
        {
            char current_brace = braces.top();
            /* CHANGE THIS TO GOOD COMPARATOR. I have to compare counterparts, i.e. '{' vs. '}' */
            if(current_brace != last_brace)
            {
                return false;
            }
        }
                //Compare 2 character next to each other. Like top and then pop with compare.
    }


    return true;
}
