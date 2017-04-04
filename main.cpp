#include <iostream>

//#define BestTravel_usage
//#define Weight_for_Weight
//#define INTEGERS_RECREATION_ONE
//#define BUNDESLIGA
//#define CAR
//#define PERFECT_TREE
#define HISTOGRAM










#ifdef BestTravel_usage
#include "Best_Travel\test_cases.cpp"
#include "Best_Travel\vector_arithmetic.cpp"
#endif

#ifdef Weight_for_Weight
#include "Weight_for_Weight\Weight.cpp"
#endif

#ifdef INTEGERS_RECREATION_ONE
#include "Integers_Recreation_One\integers.cpp"
#endif

#ifdef BUNDESLIGA
#include "Bundesliga\bundesliga.h"
#endif

#ifdef IsMyFriendCheating
#include "IsMyFriendCheating\ismyfriendcheating.cpp"
#endif

#ifdef CAR
#include "Constructing_a_Car\Car.cpp"
#endif

#ifdef PERFECT_TREE
#include "Perfect_Tree/is_perfect.cpp"
#endif

#ifdef HISTOGRAM
#include "Histogram/histogram.cpp"
#endif

int main(int argc, char *argv[])
{
#ifdef BestTravel_usage
    tests::Tests();
    Vector_Multiplication::Test_Vector_Multiplication();
#endif
#ifdef Weight_for_Weight
    WeightSort xx;
    //xx.orderWeight(std::string ("100 99 90"));
    std::cout << xx.orderWeight(std::string("56 65 74 100 99 68 86 180 90")) << std::endl;
    std::cout << xx.orderWeight(std::string("3 16 9 38 95 1131268 49455 347464 59544965313 496636983114762 85246814996697")) << std::endl; //Here is wrong apparently.

    //std::vector<int> comparator {180, 90};
    //xx.Reorder_Repeating_Weights(comparator);
#endif

    bool bigger = std::string {"90"} < std::string {"180"}; //Check narrowing!

#ifdef INTEGERS_RECREATION_ONE
    SumSquaredDivisors object;
    std::cout << object.listSquared(1, 250) << std::endl;
#endif

#ifdef BUNDESLIGA
    Bundesliga table;
    std::vector<std::string> results = {    "6:0 FC Bayern Muenchen - Werder Bremen",
                                            "1:0 Eintracht Frankfurt - Schalke 04",
                                            "0:2 FC Augsburg - VfL Wolfsburg",
                                            "1:1 Hamburger SV - FC Ingolstadt",
                                            "2:0 1. FC Koeln - SV Darmstadt",
                                            "2:1 Borussia Dortmund - FSV Mainz 05",
                                            "2:1 Borussia Moenchengladbach - Bayer Leverkusen",
                                            "-:- Hertha BSC Berlin - SC Freiburg",
                                            "-:- TSG 1899 Hoffenheim - RasenBall Leipzig"
                                       };

//    std::vector<std::string> results = {            "2:0 AReal Madrit - Sevilla",
//                                                    "2:0 Zeicester - Atletico Madrid",
//                                                    "5:1 Tottenham - PSG",
//                                                    "2:0 Barcelona - Chelsea"
//                                       };
//    std::vector<std::string> results = {    "3:2 Barcelona - Chelsea",
//                                            "1:0 FC Bayern Muenchen - Werder Bremen",
//                                            "2:1 Tottenham - PSG",
//                                       };

    table.table(results);
#endif

#ifdef CAR
    Car car;
#endif

#ifdef PERFECT_TREE
    TreeNode node;
#endif

#ifdef HISTOGRAM
    std::cout << histogram({7, 3, 10, 1, 0, 5}) << std::endl << "\n";

    std::string expected = "    10\n"
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

    std::cout << expected << std::endl;
#endif

    return 0;
}
