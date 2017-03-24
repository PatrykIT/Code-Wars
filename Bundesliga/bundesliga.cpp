#include "bundesliga.h"
#include <iostream>
#include <array>
#include <map>
#include <algorithm>
#include <set>
#include <typeinfo>
#include <functional>


using std::cout;

using std::endl;

void Bundesliga::Print_Clubs()
{
    int index = 0;
    for(auto &club : clubs)
    {
         std::cout << index << ". " << club.name << " P: " << club.points << " G: " << club.goals_scored << ":" <<
                     club.goals_conceded << "\n";
         ++index;
    }
    std::cout << "\n\n";
}


std::string Bundesliga::table(std::vector<std::string> results)
{
    std::string delimeter = ":";
    std::string delimeter_2 = " ";
    std::string delimeter_3 = " - ";

    std::array<std::string, 2> teams_playing;

    std::string token;

    std::vector<int> numbers { 10, 10, 20, 30, 40 };
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> range;
    range = std::equal_range(numbers.begin(), numbers.end(), 10);
    //std::cout << "Begin: " << &*range.first << "\nEnd: " << &*range.second << "\n";


    for(auto match = results.begin(); match != results.end(); ++match)
    {
        int goals_team_1, goals_team_2;
        bool match_drawn = false;
        bool team_1_won;

        std::string match_string = *match;
        token = match_string.substr(0, match_string.find(delimeter));

        if(token == "-")
        {
            //I think we should ignore whole iteration, because it means the match wasn't played yet.
            continue;
        }
        else
        {
            /* [6]:0 FC Bayern München - Werder Bremen */
            goals_team_1 = std::stoi(token);
            match_string.erase(0, match_string.find(delimeter) + delimeter.length());

            /* 6:[0] FC Bayern München - Werder Bremen */
            token = match_string.substr(0, match_string.find(delimeter_2));
            goals_team_2 = std::stoi(token);
            match_string.erase(0, match_string.find(delimeter_2) + delimeter.length());

            /* 6:0 [FC Bayern München] - Werder Bremen */
            token = match_string.substr(0, match_string.find(delimeter_3));
            teams_playing[0] = token;
            match_string.erase(0, match_string.find(delimeter_3) + delimeter_3.length());

            /* 6:0 FC Bayern München - [Werder Bremen] */
            token = match_string.substr(0);
            teams_playing[1] = token;

            if(goals_team_1 > goals_team_2)
                team_1_won = true;
            else if(goals_team_1 < goals_team_2)
                team_1_won = false;
            else
                match_drawn = true;


            /* If both teams are non-existent. */
            if(std::find(clubs.begin(), clubs.end(), teams_playing[0]) == clubs.end() && std::find(clubs.begin(), clubs.end(), teams_playing[1]) == clubs.end())
            {
                Club_in_Table club_1, club_2;
                club_1.name = teams_playing[0];
                club_2.name = teams_playing[1];

                clubs.emplace_back(club_1);
                clubs.emplace_back(club_2);
            }
            /* If first team doesn't exist */
            else if(std::find(clubs.begin(), clubs.end(), teams_playing[0]) == clubs.end())
            {
                Club_in_Table club_1;
                club_1.name = teams_playing[0];
                clubs.emplace_back(club_1);
            }
            /* If second team doesn't exist */
            else if(std::find(clubs.begin(), clubs.end(), teams_playing[1]) == clubs.end())
            {
                Club_in_Table club_2;
                club_2.name = teams_playing[1];
                clubs.emplace_back(club_2);
            }

            /* Both team now exist. */
            auto club_1 = std::find(clubs.begin(), clubs.end(), teams_playing[0]);
            auto club_2 = std::find(clubs.begin(), clubs.end(), teams_playing[1]);

            club_1->matches_played++;
            club_2->matches_played++;

            club_1->goals_scored += goals_team_1;
            club_1->goals_conceded += goals_team_2;
            club_2->goals_scored += goals_team_2;
            club_2->goals_conceded += goals_team_1;

            /* If it was a draw */
            if(match_drawn)
            {
                club_1->matches_drawn = 1;
                club_2->matches_drawn = 1;
                club_1->points = 1;
                club_2->points = 1;
            }
            /* If team 1 won */
            else if(team_1_won)
            {
                club_1->matches_won = 1;
                club_1->points = 3;
                club_2->matches_lost = 1;
            }
            /* If team 2 won */
            else
            {
                club_2->matches_won = 1;
                club_2->points = 3;
                club_1->matches_lost = 1;
            }
        }
    }

    Sort_Table();
    return std::string();
}


void Bundesliga::Sort_Table()
{
    std::sort(clubs.begin(), clubs.end(), [](const Club_in_Table &club_1, const Club_in_Table &club_2)
    { return club_1.points > club_2.points; } );

    std::cout << "SORTED BY POINTS:\n";
    for(auto &club : clubs)
         std::cout << club.name << " P: " << club.points << " G: " << club.goals_scored << ":" <<
                     club.goals_conceded << "\n"; std::cout << "\n\n";

    Sort_By_Goals();

    std::cout << "SORTED BY GOALS:\n";
    for(auto &club : clubs)
         std::cout << club.name << " P: " << club.points << " G: " << club.goals_scored << ":" <<
                     club.goals_conceded << "\n"; std::cout << "\n\n";

    std::cout << "SORTED BY SCORED GOALS:\n";
    Sort_By_Goals_Scored();

    for(auto &club : clubs)
         std::cout << club.name << " P: " << club.points << " G: " << club.goals_scored << ":" <<
                     club.goals_conceded << "\n"; std::cout << "\n\n";

    //Sort_By_Name();

    //4. Otherwise: The teams share the same place, but ordered by the name of the team (case-insensitive).
    //So now I need to mark teams that have in common: points, difference of goals, goals scored (So actually all of these 3 must be the same)

    std::cout << "FINAL TABLE: \n\n";
    for(auto &club : clubs)
         std::cout << club.name << " P: " << club.points << " G: " << club.goals_scored << ":" <<
                     club.goals_conceded << "\n"; std::cout << "\n";
}


void Bundesliga::Sort_By_Goals()
{
   /* std::set will hold all unique points that are in table */
   std::set<unsigned> unique_points;
   for(const auto &club : clubs)
       unique_points.insert(club.points);

   while(!unique_points.empty())
   {
       unsigned points = *unique_points.begin();
       std::pair<std::vector<Club_in_Table>::iterator, std::vector<Club_in_Table>::iterator> ranges;

       std::vector<Club_in_Table>::iterator first_iter;
       std::vector<Club_in_Table>::iterator last_iter;

       first_iter = std::find_if(clubs.begin(), clubs.end(), [points](const Club_in_Table &club) { return club.points == points; } );
       for(auto iter = clubs.begin(); iter != clubs.end(); ++iter)
       {
           if(iter->points == points)
               last_iter = iter;
       }

       ranges.first = first_iter;
       ranges.second = last_iter +1; //+1 because all algorithms use [first, last).

       std::sort(ranges.first, ranges.second, [](const Club_in_Table &club_1, const Club_in_Table &club_2)
       { return (club_1.goals_scored - club_1.goals_conceded) > (club_2.goals_scored - club_2.goals_conceded); });

        unique_points.erase(unique_points.begin());
   }
}



std::tuple<bool, std::vector<Club_in_Table>::iterator, std::vector<Club_in_Table>::iterator>
Bundesliga::Search_All()
{
    for(auto club_iterator = clubs.begin(); club_iterator != clubs.end() -1; ++club_iterator)
    {
        for(auto club_iterator_2 = clubs.begin() +1; club_iterator_2 != clubs.end(); ++club_iterator)
        {
            if(Check_if_Identical_GoalDifference(*club_iterator, *club_iterator_2) == true)
            {
                return std::tuple<bool, std::vector<Club_in_Table>::iterator, std::vector<Club_in_Table>::iterator>
                {true, club_iterator, club_iterator_2};
            }
        }
    }
    return std::tuple<bool, std::vector<Club_in_Table>::iterator, std::vector<Club_in_Table>::iterator>
    {false, clubs.end(), clubs.end()};
}


std::pair<std::vector<Club_in_Table>::iterator, std::vector<Club_in_Table>::iterator>
Find_Clubs_for_Swapping(std::map<size_t, std::vector<Club_in_Table>::iterator> &iterators_indexes_before_sorting_FINAL,
                        std::vector<Club_in_Table> &clubs, size_t &counter, std::map<size_t, std::vector<Club_in_Table>::iterator> &iterators_indexes_after_sorting)
{
    /* This loop is for finding second club in original vector, and swapping them. */
    for(auto iter = iterators_indexes_after_sorting.begin(); iter != iterators_indexes_after_sorting.end(); ++iter)
    {
        if(iterators_indexes_before_sorting_FINAL.at(counter) == iter->second)
        {
            std::vector<Club_in_Table>::iterator first_club;
            /* Find first club in original vector. */
            for(auto club_iter = clubs.begin(); club_iter != clubs.end(); ++club_iter)
                if(club_iter == iterators_indexes_before_sorting_FINAL.at(counter))
                    first_club = club_iter;

            std::vector<Club_in_Table>::iterator second_club = clubs.begin() + iter->first;

            std::cout << "Comparing from: " << first_club->name << "\n";
            std::cout << "Comparing to: " << second_club->name << "\n";

            return {first_club, second_club};
        }
    }
    return {clubs.end(), clubs.end()};
}


void Add_Matching_Iterators(std::vector<Club_in_Table>::iterator &club_iter, std::vector<Club_in_Table>::iterator &club_iter_next, std::vector<std::vector<Club_in_Table>::iterator> &iterators,
                                        std::map<size_t, std::vector<Club_in_Table>::iterator> &iterators_indexes_before_sorting, int &index)
{
        iterators.emplace_back(club_iter);
        iterators.emplace_back(club_iter_next);

        iterators_indexes_before_sorting[index] = club_iter;
        ++index;
        iterators_indexes_before_sorting[index] = club_iter_next;
        ++index;
}

void Add_Sorted_Matching_Iterators(std::vector<std::vector<Club_in_Table>::iterator> &iterators,
                                   std::map<size_t, std::vector<Club_in_Table>::iterator> &iterators_indexes_after_sorting, int &index_sorted)
{
    for(auto iter = iterators.begin(); iter != iterators.end(); ++iter)
    {
        iterators_indexes_after_sorting[index_sorted] = *iter;
        ++index_sorted;
    }
}


void Recount_Indexes(std::map<size_t, std::vector<Club_in_Table>::iterator> &iterators_indexes_before_sorting, std::map<size_t,
                     std::vector<Club_in_Table>::iterator> &iterators_indexes_before_sorting_FINAL, int &index_FINAL)
{
    for(auto iter = iterators_indexes_before_sorting.begin(); iter != iterators_indexes_before_sorting.end(); ++iter)
    {
        iterators_indexes_before_sorting_FINAL.emplace(index_FINAL, iter->second);
        ++index_FINAL;
    }
}


void Remove_Repeating_Iterators(std::vector<std::vector<Club_in_Table>::iterator> &iterators,
                                std::map<size_t, std::vector<Club_in_Table>::iterator> &iterators_indexes_before_sorting)
{
    /* Remove repeating iterators */
    for(auto iter = iterators.begin(); iter != iterators.end() -1; ++iter)
    {
        Club_in_Table *club_1 = &(**iter);
        Club_in_Table *club_2 = &(**(iter +1));

        if(Club_in_Table::Comparator_For_Unique_Iterators(*club_1, *club_2) == true)
        {
            /* Remove repeating iterator from map */
            for(auto iter_map = iterators_indexes_before_sorting.begin(); iter_map != iterators_indexes_before_sorting.end(); ++iter_map)
            {
                if(iter_map->second == *iter)
                {
                    iterators_indexes_before_sorting.erase(iter_map->first);
                    break;
                }
            }
            iterators.erase(iter);
            iter = iterators.begin();
        }
    }
}



void Erase_Elements_from_Map(std::map<size_t, std::vector<Club_in_Table>::iterator> &iterators_indexes_before_sorting_FINAL,
                             std::map<size_t, std::vector<Club_in_Table>::iterator> &iterators_indexes_after_sorting,
                             std::vector<Club_in_Table>::iterator &first_club, std::vector<Club_in_Table>::iterator &second_club)
{
    /* Take the key from second map, see what club it is, find this club in this map (so search by value) and erase it. */
    std::vector<Club_in_Table>::iterator club_to_erase = first_club;
    std::vector<Club_in_Table>::iterator club_to_erase_second = second_club;

    /* Remove swapped elements. */
    for(auto eraser = iterators_indexes_before_sorting_FINAL.begin(); eraser != iterators_indexes_before_sorting_FINAL.end(); ++eraser)
    {
        if(eraser->second == club_to_erase)
        {
            std::cout << "Removing (1_1): " << eraser->second->name << "\n";
            iterators_indexes_before_sorting_FINAL.erase(eraser->first);
            eraser = iterators_indexes_before_sorting_FINAL.begin();
        }
        if(eraser->second == club_to_erase_second)
        {
            std::cout << "Removing (2_1): " << eraser->second->name << "\n";
            iterators_indexes_before_sorting_FINAL.erase(eraser->first);
            eraser = iterators_indexes_before_sorting_FINAL.begin();
        }
    }

    for(auto eraser = iterators_indexes_after_sorting.begin(); eraser != iterators_indexes_after_sorting.end(); ++eraser)
    {
        if(eraser->second == club_to_erase)
        {
            std::cout << "Removing_C2 (2_1): " << iterators_indexes_after_sorting.at(eraser->first)->name << "\n";
            iterators_indexes_after_sorting.erase(eraser->first);
            eraser = iterators_indexes_after_sorting.begin();
        }
        if(eraser->second == club_to_erase_second)
        {
            std::cout << "Removing_C2 (2_2): " << iterators_indexes_after_sorting.at(eraser->first)->name << "\n";
            iterators_indexes_after_sorting.erase(eraser->first);
            eraser = iterators_indexes_after_sorting.begin();
        }
    }
}



bool Bundesliga::Check_if_Identical_GoalDifference(const Club_in_Table &club_1, const Club_in_Table &club_2)
{
    int goal_difference_club_1 = club_1.goals_scored - club_1.goals_conceded;
    int goal_difference_club_2 = club_2.goals_scored - club_2.goals_conceded;
    return (club_1.points == club_2.points && goal_difference_club_1 == goal_difference_club_2);
}




void Bundesliga::Sort_By_Goals_Scored_Helper()
{
    /* We know that teams will be already grouped by points and goal difference. Now I need to sort clubs that have the same goal difference,
     * but more goals scored. */


    std::vector<std::vector<Club_in_Table>::iterator> iterators;
    std::map<size_t, std::vector<Club_in_Table>::iterator> iterators_indexes_before_sorting;
    int index = 0;
    std::map<size_t, std::vector<Club_in_Table>::iterator> iterators_indexes_before_sorting_FINAL;
    int index_FINAL = 0;
    std::map<size_t, std::vector<Club_in_Table>::iterator> iterators_indexes_after_sorting;
    int index_sorted = 0;

    bool need_sorting = false;

    for(auto club_iter = clubs.begin(); club_iter != clubs.end(); ++club_iter)
    {
        auto searcher { Search_All() };
        if(std::get<0>(searcher) == true)
        {
            Add_Matching_Iterators(std::get<1>(searcher), std::get<2>(searcher), iterators, iterators_indexes_before_sorting, index);
            need_sorting = true;
        }
        /* Sort currently saved iterators and erase them, so the next ones can be saved & sorted. */
        else if(need_sorting == true)
        {
            Remove_Repeating_Iterators(iterators, iterators_indexes_before_sorting);

            /* Count again indexes, because repeating iterators made them +1 bigger each. */
            Recount_Indexes(iterators_indexes_before_sorting, iterators_indexes_before_sorting_FINAL, index_FINAL);

            std::sort(iterators.begin(), iterators.end(), Club_in_Table::Iterator_Based_Comparator_for_Goals_Scored);
            /* After sorting, I can find which elements were sorted. When I find them, I swap them in original clubs vector.
             * For example, if element 4 changed with element 2, then I can change their positions in original vector. */
            Add_Sorted_Matching_Iterators(iterators, iterators_indexes_after_sorting, index_sorted);

            /* So now i have two maps (before sorting, after sorting). I can compare all keys and iterators. If some keys do not have same
             * iterators, that means they were sorted. So, then: Take the key of before, and see where is after key. For example if before was 2,
             * and after is 4, that means the in clubs vector i should swap (2, 4) ;) */


            /* Compare iterators. If they do not match, find matching iterator in a loop. Then, count the indexes difference and swap iterators
             * by positions. */
            size_t start_position = index_FINAL - iterators.size();
            for(size_t counter = start_position; counter != index_FINAL; ++counter)
            {
                /* If this is false, then that means that lhs team was sorted with some other. We need to find that other, and swap them in original container. */
                if(iterators_indexes_before_sorting_FINAL.at(counter) != iterators_indexes_after_sorting.at(counter))
                {
                    auto clubs_to_swap = Find_Clubs_for_Swapping(iterators_indexes_before_sorting_FINAL, clubs, counter, iterators_indexes_after_sorting);
                    Club_in_Table::Swap(*clubs_to_swap.first, *clubs_to_swap.second);
                    //std::iter_swap(clubs_to_swap.first, clubs_to_swap.second);

                    Erase_Elements_from_Map(iterators_indexes_before_sorting_FINAL, iterators_indexes_after_sorting, clubs_to_swap.first, clubs_to_swap.second);

                    Print_Clubs();
                    break;
                }
            }

            std::cout << "After: \n";
            for(auto club : iterators) { std::cout << club->name << "\n"; }


            iterators.clear();
            iterators_indexes_before_sorting.clear();
            iterators_indexes_before_sorting_FINAL.clear();
            iterators_indexes_after_sorting.clear();
            need_sorting = false;
        }
    }
}


struct Points_GoalsDifference
{
    static bool Comparator(const Club_in_Table &club_1, const Club_in_Table &club_2)
    {
        return club_1.points == club_2.points &&
                (club_1.goals_scored - club_1.goals_conceded) == (club_2.goals_scored - club_2.goals_conceded);
    }
};


//I need to group teams that have the same points and goal differences. Rest of teams - I do not care.
//So I can do vector of vectors. I will push iterators of clubs to those vectors
//Each vector means: teams with same points and goal differences
//After inserting teams, vectors with size 0 will be removed -
// because it means those teams are unique, and do not need sorting. They are in good place in table (maybe only names bad, but its not for this func ;p)
void Bundesliga::Sort_By_Goals_Scored() //This doesn't work properly.
{

    Sort_By_Goals_Scored_Helper();
}













bool Bundesliga::Check_if_Identical_Everything(const Club_in_Table &club_1, const Club_in_Table &club_2)
{
    return Check_if_Identical_GoalDifference(club_1, club_2) && club_1.goals_scored == club_2.goals_scored;
}


//Alternative: std::find_if. Maybe I wouldn't need to save iterators manually.
//This function (not find_if): Why do I convert iterators to indexes if later do I convert it back to original?
//This can be merged!
void Bundesliga::Sort_By_Name()
{
    //So now I need to mark teams that have in common: points, difference of goals, goals scored (So actually all of these 3 must be the same)
    //We know that clubs are already sorted how they should be. We should only compare clubs that have identical [points, difference goals, goals scored].

    std::vector<std::set<size_t>> indexes (18);
    int current_set = 0;

    /* CONVERT ITERATORS OF CLUBS THAT HAVE THE SAME [POINTS, GOALS SCORED, GOALS DIFFERENCE] TO INDEXES */
    for(std::vector<Club_in_Table>::iterator club_iter = clubs.begin(); club_iter != clubs.end() -1; ++club_iter)
    {
        /* Save indexes of teams that are identical. Later, those indexes will be sorted by name. */
        if(Check_if_Identical_Everything(*club_iter, *(club_iter +1)) == true)
        {
            size_t index_1 = std::distance(clubs.begin(), club_iter);
            size_t index_2 = std::distance(clubs.begin(), club_iter +1);

            indexes.at(current_set).emplace(index_1);
            indexes.at(current_set).emplace(index_2);
        }
        else //Means we moved on to the next group of teams
        {
            current_set++;
        }
    }

    /* REMOVE EMPTY SETS */
    for(std::vector<std::set<size_t>>::iterator it = indexes.begin(); it != indexes.end(); ++it)
    {
        if(it->empty())
        {
           indexes.erase(it);
           it = indexes.begin();
        }
    }

    /* Vector of iterators */
    std::vector<std::vector<std::vector<Club_in_Table>::iterator>> iterators (18);
    int current_vector = 0;

    /* Now I should have vector, that has vectors. Each of those vectors holds indexes to the group of same teams, that needs to be sorted by name. */
    /* CONVERT INDEXES TO ITERATORS */
    for(std::set<size_t> current_vec : indexes)
    {
        /* Convert indexes to iterators. */
        for(size_t index : current_vec)
        {
            std::vector<Club_in_Table>::iterator current_iter = clubs.begin() + index;
            iterators.at(current_vector).push_back(current_iter);
        }

        ++current_vector;
    }

    /* Erase the rest of vectors that were not filled. */
    iterators.erase(iterators.begin() + current_vector, iterators.end());

    /* Sort elements by names. */
    for(std::vector<std::vector<Club_in_Table>::iterator> &iter : iterators)
    {
        std::sort(iter.begin(), iter.end(), Club_in_Table::Iterator_Based_Comparator_for_Names);
    }


    std::vector<Club_in_Table> final_table;
    for(std::vector<std::vector<Club_in_Table>::iterator> &iter : iterators)
    {
        for(auto temp : iter)
            final_table.push_back(*temp);
    }

    /* For every element in "clubs": If element is not in "final_table", insert him, with position that he had in original
     * vector.  */
    for(auto iter = clubs.begin(); iter != clubs.end(); ++iter)
    {
        std::vector<Club_in_Table>::iterator position = std::find(final_table.begin(), final_table.end(), *iter);
        /* Means club is not in final table - we need to put it, with appriopriate position */
        if(position == final_table.end())
        {
            size_t index = std::distance(clubs.begin(), iter);
            final_table.insert(final_table.begin() + index, *iter);
        }
    }

    clubs = final_table;
}
















