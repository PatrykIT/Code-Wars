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
      Debug_Info(__func__, __LINE__, max_distance, towns_to_visit, list_of_distances_arg);
      static std::vector<int> all_combinations;
      static std::vector<int> list_of_distances;
      list_of_distances = list_of_distances_arg;


      if(towns_to_visit > list_of_distances.size())
      {
          all_combinations.clear();
          list_of_distances.clear();
          return -1;
      }

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

    static void Debug_Info(std::string function_name, int line_of_code, int max_distance, int towns_to_visit, std::vector<int> numbers = {})
    {
        cout << "Function: " << function_name << " | Line: " << line_of_code << " ";

        if(!numbers.empty())
        {
            cout << "Numbers: ";
            for(auto x : numbers)
                cout << x << " ";
            cout << endl;
        }
        cout << "Max distance: " << max_distance << ". Towns to visit: " << towns_to_visit;
        cout << endl;
    }
};
