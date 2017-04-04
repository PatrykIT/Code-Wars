#include <iostream>
#include <vector>
std::string histogram(std::vector<int> results)
{
    std::string result = "";

    int index = 1;

    for(int number : results)
    {
        int how_many_hashes = number;
        result.append(std::to_string(number) + "\n");

        for(int i = 0; i < how_many_hashes; ++i)
            result.append("#\n");

        result.append("-\n");
        result.append(std::to_string(index) + "\n");
         ++index;
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
