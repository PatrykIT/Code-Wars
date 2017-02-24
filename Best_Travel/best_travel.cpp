#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <array>
#include <algorithm>

using std::cout;
using std::endl;

namespace BigNumber
{
    template<typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
    static std::vector<int> GetFactorial(T number)
    {
        // Apply simple factorial formula n! = 1 * 2 * 3 * 4...*n
        std::vector<int> result = multiply(number);

        std::reverse(result.begin(), result.end());

        cout << "Result: ";
        for (auto &it = result.cbegin(); it != result.cend(); ++it)
            cout << *it;

        return result;
    }

    static std::vector<int> multiply(int number)
    {
        std::vector<int> result {1};

        for(int x = 2; x <= number; x++)
        {
            int carry = 0;

            // One by one multiply n with individual digits of res[]
            for (int i = 0; i < result.size(); i++)
            {
                int prod = result.at(i) * x + carry;
                result.at(i) = prod % 10;  // Store last digit of 'prod' in res[]
                carry  = prod / 10;    // Put rest in carry
            }

            while (carry)
            {
                result.emplace_back(carry % 10);
                carry = carry / 10;
            }
        }
        return result;
    }

    static std::vector<int> Multiply_from_Vector(std::vector<int> &lhs, size_t rhs)
    {
    /* Return lhs * rhs */


        return {};
    }
    static std::vector<int> Multiply_from_Vector(std::vector<size_t> lhs, size_t rhs) //This overload allows us creating vector when calling a function.
    {
    /* Return lhs * rhs */
        return {};
    }

    static size_t Divide_Vector_by_Vector(std::vector<int> &lhs, std::vector<int> &rhs)
    {
        return 0;
    }

    static size_t Divide_Number_by_Vector(size_t lhs, std::vector<int> &rhs)
    {
        return 0;
    }
    static size_t Divide_Vector_by_Number(std::vector<int> &lhs, size_t rhs)
    {
        return 0;
    }
}






class BestTravel
{
public:

    template<typename T, typename = std::enable_if_t<std::is_integral<T>::value, T>>
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
    static size_t Number_of_Unique_Combinations(const size_t n, const size_t k)
    {
        /* 20! is the biggest factorial C++ can handle (long long int) */
        if(k <= 20 && n <= 20)
        {
            const auto n_factorial = GetFactorial<size_t>(n);
            const auto k_factorial = GetFactorial<size_t>(k);
            const auto division = k_factorial * GetFactorial<size_t>(n-k);

            const auto result = n_factorial / division;
            return result;
        }
        /* Handle very big number, larger then maximum numerical type in C++ */
        else
        {
           std::vector<int> n_factorial_big, k_factorial_big, division_big;
           size_t n_factorial, k_factorial;
           size_t n_substract_k_factorial = GetFactorial<size_t>(n-k);

            if(n > 20)
            {
               n_factorial_big = BigNumber::GetFactorial<size_t>(n);
            }
            else
            {
               n_factorial = GetFactorial<size_t>(n);
            }
            if(k > 20)
            {
               k_factorial_big = BigNumber::GetFactorial<size_t>(k);
               division_big = BigNumber::Multiply_from_Vector(k_factorial_big, n_substract_k_factorial);
            }
            else
            {
               k_factorial = GetFactorial<size_t>(k);
               division_big = BigNumber::Multiply_from_Vector({k_factorial}, n_substract_k_factorial);
            }

            size_t result;

            if(n > 20)
                result = BigNumber::Divide_Vector_by_Vector(n_factorial_big, division_big); //result = n_factorial_big / division;
            else if(n < 20)
                result = BigNumber::Divide_Number_by_Vector(n_factorial, division_big); //result = n_factorial / division;


            return result;
        }
    }

    static void Save_Combination(const std::vector<int>& combination, std::vector<int> &all_combinations)
    {
      for (int i = 0; i < combination.size(); ++i)
      {
          all_combinations.push_back(combination[i]);
      }
    }

    /**
     * @brief Create_All_Unique_Combinations - function that transforms a combination like:  [1, 2, 3, 4] with k = 2, to: [ [1, 2][1, 3][1, 4][2, 3][2, 4][3, 4] ]
     * @param offset
     * @param k - amount of distances in single array.
     * @param all_combinations - output. To this list we save all possible combinations.
     * @param list_of_distances - input. From this list we create all possible combinations.
     */
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

    static size_t chooseBestSum(int max_distance, int towns_to_visit, std::vector<int>& list_of_distances_arg)
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

      const size_t subarrays_count = Number_of_Unique_Combinations(list_of_distances.size(), towns_to_visit);
      std::vector<long long> unique_sums_of_paths;

      /* Sum each subarrays from 'all_combinations' vector. */
      for(size_t current_array = 0; current_array < subarrays_count; ++current_array)
      {
          size_t sum = 0;
          size_t offset = current_array * towns_to_visit; //We have to multiply by 'towns_to_visit' so we can sum all elements of given array.
          for(size_t a = offset; a < offset + towns_to_visit; ++a)
          {
              sum += all_combinations[a];
          }
          unique_sums_of_paths.push_back(sum);
      }

      size_t not_good_paths = 0;

      /* Count the difference between maximum distance and path distances */
      for(auto &&path : unique_sums_of_paths)
      {
          /* Result  should be > 0. Otherwise it means that path was initially too big, and can't be counted. */
          bool too_long_path = (max_distance - path) < 0 ? true : false;

          if(too_long_path)
          {
              /* If path is greater then the maximum distance, set it to very big value, so the function std::min_element would ignore it. */
              path = std::numeric_limits<long long>::max();
              ++not_good_paths;
          }
          else
          {
              path = max_distance - path;
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

      auto best_subarray_number = std::distance(unique_sums_of_paths.begin(), best_path);
      auto starting_index_of_best_subarray = best_subarray_number * towns_to_visit;
      size_t sum_of_best_path = 0;

      for(auto i = starting_index_of_best_subarray ; i < starting_index_of_best_subarray + towns_to_visit; ++i)
      {
          sum_of_best_path += all_combinations[i];
      }

      all_combinations.clear();
      list_of_distances.clear();

      cout << "Answer: " << sum_of_best_path << "\n";
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
