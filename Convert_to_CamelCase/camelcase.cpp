#include <string>
#include <cctype>

std::string to_camel_case(std::string text)
{
    // TODO: Your code goes here!
    char dash = '-';
    char underscore = '_';
    for(std::string::iterator iter = text.begin(); iter != text.end(); ++iter)
    {
        if(*iter == dash || *iter == underscore)
        {
            iter = text.erase(iter);
            *iter = std::toupper(*iter);
        }
    }
    return text;
}

