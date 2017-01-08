#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <array>

using std::cout;
using std::endl;


template <typename T>
T GetFactorial(T number)
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
unsigned int Number_of_Unique_Combinations(const size_t n, const unsigned int k)
{
    const size_t n_factorial = GetFactorial(n);
    const unsigned int k_factorial = GetFactorial(k);

    const unsigned int result = n_factorial / (k_factorial * (GetFactorial(n-k)));
    return result;
}

void Save_Combination(const std::vector<int>& combination, std::vector<int> &all_combinations)
{
  for (int i = 0; i < combination.size(); ++i)
  {
      //cout << combination[i] << " ";
      all_combinations.push_back(combination[i]);
  }
}

void Create_All_Unique_Combinations(int offset, int k, std::vector<int> &list_of_distances, std::vector<int> &all_combinations)
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
    Create_All_Unique_Combinations(i+1, k-1, list_of_distances, all_combinations);
    combinations.pop_back();
  }
}

std::vector<int>::iterator Get_Iterator_to_Best_Subarray(std::vector<int> &unique_sums_of_paths)
{
    std::vector<int>::iterator best_path = unique_sums_of_paths.end();
    int closest_path_to_maximum_distance = std::numeric_limits<int>::max(); //The closer to zero the value gets, the better the path.

    for(std::vector<int>::iterator it = unique_sums_of_paths.begin(); it != unique_sums_of_paths.end(); ++it)
    {
        if(*it >= 0)
        {
            if (*it < closest_path_to_maximum_distance)
            {
                closest_path_to_maximum_distance = *it;
                best_path = it;
            }
        }
    }

    if(best_path == unique_sums_of_paths.end())
        return unique_sums_of_paths.end();

    if(*best_path < 0 || *best_path == std::numeric_limits<int>::max()) //TODO: Change max int to something less buggy.
        return unique_sums_of_paths.end();

    return best_path;
}

int chooseBestSum(int max_distance, int towns_to_visit, std::vector<int>& list_of_distances)
{
    std::vector<int> all_combinations;
    Create_All_Unique_Combinations(0, towns_to_visit, list_of_distances, all_combinations);

    /* Sum each subarrays from 'all_combinations' vector. */
    const unsigned int subarrays_count = Number_of_Unique_Combinations(list_of_distances.size(), towns_to_visit);
    std::vector<int> unique_sums_of_paths;

    for(unsigned int current_array = 0; current_array < subarrays_count; ++current_array)
    {
        int sum = 0;
        int offset = current_array * towns_to_visit; //We have to multiply by 'towns_to_visit' so we can sum all elements of given array.
        for(int a = offset; a < offset + towns_to_visit; ++a)
        {
            sum += all_combinations[a];
        }
        unique_sums_of_paths.push_back(sum);
    }

    /* Count the difference between maximum allowed distance and path distances */
    for(auto &&path : unique_sums_of_paths)
    {
        path = max_distance - path; //Path must be smaller then max distance. If its bigger, then we must ignore it.
    }

    /* Take the iterator from the best sum of paths, and find its corresponding subarray. */
    std::vector<int>::iterator best_path = Get_Iterator_to_Best_Subarray(unique_sums_of_paths);
    if(best_path == unique_sums_of_paths.end())
        return -1;

    int best_subarray_number = std::distance(unique_sums_of_paths.begin(), best_path);
    int starting_index_of_best_subarray = best_subarray_number * towns_to_visit;
    int sum_of_best_path = 0;

    for(int i = starting_index_of_best_subarray ; i < starting_index_of_best_subarray + towns_to_visit; ++i)
    {
        sum_of_best_path += all_combinations[i];
    }

    return sum_of_best_path;
}



int main(int argc, char *argv[])
{
    std::vector<int> town = {50, 55, 57, 58, 60};
    cout << "Best sum: " << chooseBestSum(174, 3, town) << endl;

    std::vector<int> town_2 = {50, 100, 150, 200, 250};
    cout << "Best sum: " << chooseBestSum(100, 3, town_2) << endl; //In this TC, values are too big for max.

    std::vector<int> town_3 = {50, 100, 150, 200, 250};
    cout << "Best sum: " << chooseBestSum(1000, 3, town_3) << endl; //In this TC, max is too big for values. The correct result should be 600, because of exercise sentence:
    //"Which distances they will choose so that the sum of the distances is the biggest possible - to please Mary - but less than k - to please John?"

    return 0;
}
