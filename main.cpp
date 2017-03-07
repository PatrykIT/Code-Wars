#include <iostream>
//#define BestTravel_usage
//#define Weight_for_Weight
#define Integers_Recreation_One


#ifdef BestTravel_usage
#include "Best_Travel\test_cases.cpp"
#include "Best_Travel\vector_arithmetic.cpp"
#endif

#ifdef Weight_for_Weight
#include "Weight_for_Weight\Weight.cpp"
#endif

#ifdef Integers_Recreation_One
#include "Integers_Recreation_One\integers.cpp"
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

#ifdef Integers_Recreation_One
    SumSquaredDivisors object;
    std::cout << object.listSquared(1, 250) << std::endl;
#endif


    return 0;
}
