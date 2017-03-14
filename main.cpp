#include <iostream>
//#define BestTravel_usage
//#define Weight_for_Weight
//#define INTEGERS_RECREATION_ONE
#define BUNDESLIGA


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

using std::cout;
using std::endl;

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

    Bundesliga table;
    std::vector<std::string> results = {            "6:0 FC Bayern Muenchen - Werder Bremen",
                                                    "1:0 Eintracht Frankfurt - Schalke 04",
                                                    "0:2 FC Augsburg - VfL Wolfsburg",
                                                    "1:1 Hamburger SV - FC Ingolstadt",
                                                    "2:0 1. FC Koeln - SV Darmstadt",
                                                    "2:1 Borussia Dortmund - FSV Mainz 05",
                                                    "2:1 Borussia Moenchengladbach - Bayer Leverkusen",
                                                    "2:0 AAertha BSC Berlin - SC Freiburg",
                                                    "-:- TSG 1899 Hoffenheim - RasenBall Leipzig"
                                       };
    table.table(results);

    return 0;
}
