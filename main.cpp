#define In_Main

#ifdef In_Main

#include "Best_Travel\best_travel.cpp"

#else

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <array>
#include <algorithm>

using std::cout;
using std::endl;

class BestTravel
{
public:

    template <typename T>
    static T GetFactorial(T number)
    {
        T result = 1;
        for (; number > 0; --number)
            result *= number;
        return result;
    }

    /**
     * @brief Number_of_Unique_Combinations
     * @param n - count of all elements
     * @param k - subset of elements for combination
     * @return - number of possible unique combinations
     */
    static unsigned int Number_of_Unique_Combinations(const size_t n, const unsigned int k)
    {
        const size_t n_factorial = GetFactorial(n);
        const unsigned int k_factorial = GetFactorial(k);

        const unsigned int result = n_factorial / (k_factorial * (GetFactorial(n-k)));
        return result;
    }

    static void Save_Combination(const std::vector<int>& combination, std::vector<int> &all_combinations)
    {
      for (int i = 0; i < combination.size(); ++i)
      {
          //cout << combination[i] << " ";
          all_combinations.push_back(combination[i]);
      }
    }

    static void Create_All_Unique_Combinations(int offset, int k, std::vector<int> &all_combinations, std::vector<int> &list_of_distances)
    {
      static std::vector<int> combinations;
      if (k == 0)
      {
        Save_Combination(combinations, all_combinations);
        return;
      }

      for (int i = offset; i <= list_of_distances.size() - k; ++i)
      {
        combinations.push_back(list_of_distances[i]);
        Create_All_Unique_Combinations(i+1, k-1, all_combinations, list_of_distances);
        combinations.pop_back();
      }
    }

    static int chooseBestSum(int max_distance, int towns_to_visit, std::vector<int>& list_of_distances_arg)
    {
      static std::vector<int> all_combinations;
      static std::vector<int> list_of_distances;
      list_of_distances = list_of_distances_arg;

      if(towns_to_visit > list_of_distances.size())
          return -1;

      Create_All_Unique_Combinations(0, towns_to_visit, all_combinations, list_of_distances);

      /* Sum each subarrays from 'all_combinations' vector. */
      const int subarrays_count = Number_of_Unique_Combinations(list_of_distances.size(), towns_to_visit);
      std::vector<int> unique_sums_of_paths;

      for(int current_array = 0; current_array < subarrays_count; ++current_array)
      {
          int sum = 0;
          int offset = current_array * towns_to_visit; //We have to multiply by 'towns_to_visit' so we can sum all elements of given array.
          for(int a = offset; a < offset + towns_to_visit; ++a)
          {
              sum += all_combinations[a];
          }
          unique_sums_of_paths.push_back(sum);
      }

      int not_good_paths = 0;

      /* Count the difference between maximum distance and path distances */
      for(auto &&path : unique_sums_of_paths)
      {
          path = max_distance - path; //Result  must be > 0. Otherwise it means that path was initially too big, and can't be counted.
          if(path < 0) //If path is greater then the maximum distance, set it to very big value, so the function std::min_element would ignore it.
          {
              path = std::numeric_limits<int>::max();
              ++not_good_paths;
          }
      }

      if(not_good_paths == unique_sums_of_paths.size()) //Means that all roads were too big for given max distance.
      {
          all_combinations.clear();
          list_of_distances.clear();
          return -1;
      }

      /* Take the iterator from the best sum of paths, and find its corresponding subarray. */
      auto &&best_path = std::min_element(unique_sums_of_paths.begin(), unique_sums_of_paths.end());

      int best_subarray_number = std::distance(unique_sums_of_paths.begin(), best_path);
      int starting_index_of_best_subarray = best_subarray_number * towns_to_visit;
      int sum_of_best_path = 0;

      for(int i = starting_index_of_best_subarray ; i < starting_index_of_best_subarray + towns_to_visit; ++i)
      {
          sum_of_best_path += all_combinations[i];
      }

      all_combinations.clear();
      list_of_distances.clear();

      return sum_of_best_path;
    }
};
#endif

#include "Best_Travel\vector_arithmetic.cpp"

using std::cout;
using std::endl;

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



int main(int argc, char *argv[])
{
    //Tests();

    //BigNumber::factorial_3(24);
    //factorial_3(24);


    //Vectors();

    Vector_Multiplication::Test_Vector_Multiplication();

    return 0;
}
