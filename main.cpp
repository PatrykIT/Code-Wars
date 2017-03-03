#define BestTravel_usage

#ifdef BestTravel_usage
#include "Best_Travel\test_cases.cpp"
#include "Best_Travel\vector_arithmetic.cpp"
#else

#include <iostream>

#endif

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
#ifdef BestTravel_usage
    tests::Tests();
    Vector_Multiplication::Test_Vector_Multiplication();
#endif

    return 0;
}
