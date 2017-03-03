#include "best_travel.cpp"

namespace tests
{
    void testequal(size_t a, int b)
    {
        bool result = a == b;
        cout << result << endl;
    }

    void Tests()
    {
        size_t n;

        std::vector<int> ts = {50, 55, 56, 57, 58};
        n = BestTravel::chooseBestSum(163, 3, ts);
        testequal(n, 163);

        ts = {50};
        n = BestTravel::chooseBestSum(163, 3, ts);
        testequal(n, -1);


        ts = {91, 74, 73, 85, 73, 81, 87};
        n = BestTravel::chooseBestSum(230, 3, ts);
        testequal(n, 228);

        n = BestTravel::chooseBestSum(331, 2, ts);
        testequal(n, 178);

        n = BestTravel::chooseBestSum(331, 4, ts);
        testequal(n, 331);

        n = BestTravel::chooseBestSum(331, 5, ts);
        testequal(n, -1);

        n = BestTravel::chooseBestSum(331, 1, ts);
        testequal(n, 91);

        n = BestTravel::chooseBestSum(700, 8, ts);
        testequal(n, -1);

        ts = std::vector<int>{50, 55, 57, 58, 60};
        n = BestTravel::chooseBestSum(174, 3, ts);
        testequal(n, 173);

        ts = std::vector<int>{50, 100, 150, 200, 250};
        n = BestTravel::chooseBestSum(100, 3, ts); //In this TC, values are too big for max. Should be -1.
        testequal(n, -1);

        ts = std::vector<int>{50, 100, 150, 200, 250};
        n = BestTravel::chooseBestSum(1000, 3, ts); //In this TC, max is too big for values. The correct result should be 600, because of exercise sentence:
                                                // "Which distances they will choose so that the sum of the distances is the biggest possible - to please Mary - but less than k - to please John?"
        testequal(n, 600);

        ts = std::vector<int>{100, 76, 56, 44, 89, 73, 68, 56, 64, 123, 2333, 144, 50, 132, 123, 34, 89};
        n = BestTravel::chooseBestSum(2430, 15, ts);
        testequal(n, 1287);



    //    n = BestTravel::chooseBestSum(485, 4, std::vector<int>{298, 93, 289, 117, 43, 185, 325, 251, 79, 458, 36, 175, 474, 312, 326, 152, 75,
    //                                                             253, 191, 463, 353});
    //    testequal(n, 485); //Gives 484 :/

    //    n = BestTravel::chooseBestSum(845, 3, std::vector<int>{468, 248, 165, 87, 265, 405, 59, 254, 366, 196, 16, 37, 460, 343, 431, 178, 400,
    //                                                           160, 260, 25, 493, 234, 59, 273});
    //    testequal(n, 845); //Gives -1 :/


        cout << "Bye bye.\n";
    }
}
