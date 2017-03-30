#include "bundesliga.h"
#include <iostream>
#include <array>
#include <algorithm>
#include <set>

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

    for(auto match = results.begin(); match != results.end(); ++match)
    {
        int goals_team_1, goals_team_2;
        bool match_drawn = false;
        bool team_1_won;

        std::string match_string = *match;
        token = match_string.substr(0, match_string.find(delimeter));

        if(token == "-")
        {
            goals_team_1 = 0;
            match_string.erase(0, match_string.find(delimeter) + delimeter.length());

            /* 6:[0] FC Bayern München - Werder Bremen */
            token = match_string.substr(0, match_string.find(delimeter_2));
            goals_team_2 = 0;
            match_string.erase(0, match_string.find(delimeter_2) + delimeter.length());

            /* 6:0 [FC Bayern München] - Werder Bremen */
            token = match_string.substr(0, match_string.find(delimeter_3));
            teams_playing[0] = token;
            match_string.erase(0, match_string.find(delimeter_3) + delimeter_3.length());

            /* 6:0 FC Bayern München - [Werder Bremen] */
            token = match_string.substr(0);
            teams_playing[1] = token;

            Club_in_Table club_1, club_2;
            club_1.name = teams_playing[0];
            club_2.name = teams_playing[1];

            clubs.emplace_back(club_1);
            clubs.emplace_back(club_2);
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
    Add_Positions();

    return Return_Final_Table();
}


std::string Bundesliga::Return_Final_Table()
{
    std::string final = "";
    std::string line = "";

    for(Club_in_Table &club : clubs)
    {
        line.append(std::to_string(club.position));
        if(line.length() == 1)
            line.insert(line.begin(), ' ');

        line.append(". ");

        int spaces_needed = 30 - club.name.length();
        std::string fill_up (spaces_needed, ' ');
        line.append(club.name + fill_up);

        line.append(std::to_string(club.matches_played) + "  " + std::to_string(club.matches_won) + "  " +
                    std::to_string(club.matches_drawn) + "  " + std::to_string(club.matches_lost));
        line.append("  " + std::to_string(club.goals_scored) + ":" + std::to_string(club.goals_conceded));
        line.append("  " + std::to_string(club.points) + "\n");

        final.append(line);
        line.clear();
    }
    std::cout << "\n\n\t\tFINAL: \n" << final << "\n";
    return final;
}

void Bundesliga::Add_Positions()
{
    clubs.front().position = 1;
    int position = 2;

    for(auto club_iter = clubs.begin() +1; club_iter != clubs.end(); ++club_iter)
    {
        const Club_in_Table &club_before = *(club_iter -1);
        if(Check_if_Identical_Everything(club_before, *club_iter) == true)
        {
            club_iter->position = club_before.position;
        }
        else
        {
            club_iter->position = position;
        }
        ++position;
    }
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

    Sort_By_Name();

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


std::tuple<bool, std::vector<std::vector<Club_in_Table>::iterator>, std::vector<Club_in_Table>::iterator , std::vector<Club_in_Table>::iterator>
Bundesliga::Search_All_Equal_Goal_Difference(std::vector<Club_in_Table>::iterator club_to_analyse,
                       std::vector<std::vector<Club_in_Table>::iterator> &copy_of_clubs)
{
    std::tuple<bool, std::vector<std::vector<Club_in_Table>::iterator>, std::vector<Club_in_Table>::iterator,
        std::vector<Club_in_Table>::iterator> /* [Bool if found identical clubs, iterators, first iterator, last iterator] */
        return_value;

    std::vector<std::vector<Club_in_Table>::iterator> identical_clubs;
    std::vector<std::vector<Club_in_Table>::iterator> copy_of_copy_clubs = copy_of_clubs;
    std::vector<Club_in_Table>::iterator first;
    std::vector<Club_in_Table>::iterator last;
    bool found_identical_goal_difference = false, found_first = false;

    for(auto club_iterator = copy_of_copy_clubs.begin(); club_iterator != copy_of_copy_clubs.end(); ++club_iterator)
    {
        if(Check_if_Identical_GoalDifference(*club_to_analyse, **club_iterator) == true)
        {
            if(found_first == false)
            {
                first = *club_iterator; //Save first iterator
                found_first = true;
            }

            if(club_to_analyse->name != (*club_iterator)->name)
                found_identical_goal_difference = true;

            identical_clubs.push_back(*club_iterator);
            club_iterator = copy_of_copy_clubs.erase(club_iterator) -1; //-1 because on repeat of the loop, the counter will be +1
            last = identical_clubs.back(); //Save last iterator
        }
    }

    if(found_identical_goal_difference)
        std::get<0>(return_value) = true;
    else
        std::get<0>(return_value) = false;

    std::get<1>(return_value) = identical_clubs;
    std::get<2>(return_value) = first;
    std::get<3>(return_value) = last;

    return return_value;
}


std::tuple<bool, std::vector<std::vector<Club_in_Table>::iterator>, std::vector<Club_in_Table>::iterator , std::vector<Club_in_Table>::iterator>
Bundesliga::Search_All_Equal_Everything (std::vector<Club_in_Table>::iterator club_to_analyse,
            std::vector<std::vector<Club_in_Table>::iterator> &copy_of_clubs)
{
    std::tuple<bool, std::vector<std::vector<Club_in_Table>::iterator>, std::vector<Club_in_Table>::iterator,
            std::vector<Club_in_Table>::iterator> /* [Bool if found identical clubs, iterators, first iterator, last iterator] */
            return_value;

        std::vector<std::vector<Club_in_Table>::iterator> identical_clubs;
        std::vector<std::vector<Club_in_Table>::iterator> copy_of_copy_clubs = copy_of_clubs;
        std::vector<Club_in_Table>::iterator first;
        std::vector<Club_in_Table>::iterator last;
        bool found_identical_goal_difference = false, found_first = false;

        for(auto club_iterator = copy_of_copy_clubs.begin(); club_iterator != copy_of_copy_clubs.end(); ++club_iterator)
        {
            if(Check_if_Identical_Everything(*club_to_analyse, **club_iterator) == true)
            {
                if(found_first == false)
                {
                    first = *club_iterator; //Save first iterator
                    found_first = true;
                }

                if(club_to_analyse->name != (*club_iterator)->name)
                    found_identical_goal_difference = true;

                identical_clubs.push_back(*club_iterator);
                club_iterator = copy_of_copy_clubs.erase(club_iterator) -1; //-1 because on repeat of the loop, the counter will be +1
                last = identical_clubs.back(); //Save last iterator
            }
        }

        if(found_identical_goal_difference)
            std::get<0>(return_value) = true;
        else
            std::get<0>(return_value) = false;

        std::get<1>(return_value) = identical_clubs;
        std::get<2>(return_value) = first;
        std::get<3>(return_value) = last;

        return return_value;
}

void Add_Matching_Iterators(std::vector<std::vector<Club_in_Table>::iterator> identical_clubs, std::vector<std::vector<Club_in_Table>::iterator> &iterators)
{
        for(auto current_club = identical_clubs.begin(); current_club != identical_clubs.end(); ++current_club)
        {
            iterators.emplace_back(*current_club);
        }
}


bool Bundesliga::Check_if_Identical_GoalDifference(const Club_in_Table &club_1, const Club_in_Table &club_2)
{
    int goal_difference_club_1 = club_1.goals_scored - club_1.goals_conceded;
    int goal_difference_club_2 = club_2.goals_scored - club_2.goals_conceded;
    return (club_1.points == club_2.points && goal_difference_club_1 == goal_difference_club_2);
}


void Bundesliga::Custom_Sort(std::function<bool(std::vector<Club_in_Table>::iterator, std::vector<Club_in_Table>::iterator)> iterator_comparision,
                 std::function<bool(std::vector<Club_in_Table>::iterator, std::vector<Club_in_Table>::iterator)> iterator_sort_comparision,
                 std::function<std::tuple<bool, std::vector<std::vector<Club_in_Table>::iterator>,
                             std::vector<Club_in_Table>::iterator, std::vector<Club_in_Table>::iterator>
                 (std::vector<Club_in_Table>::iterator, std::vector<std::vector<Club_in_Table>::iterator>)> search_function)
{
    std::vector<std::vector<Club_in_Table>::iterator> iterators;
    bool need_sorting = false;

    std::vector<std::vector<Club_in_Table>::iterator> copy_of_clubs;
    for(auto iter = clubs.begin(); iter != clubs.end(); ++iter)
        copy_of_clubs.push_back(iter);

    for(auto club_iter = clubs.begin(); club_iter != clubs.end(); ++club_iter)
    {
        auto searcher { search_function(club_iter, copy_of_clubs) };
        if(std::get<0>(searcher) == true)
        {
            Add_Matching_Iterators(std::get<1>(searcher), iterators);
            need_sorting = true;
        }
        /* Sort currently saved iterators and erase them, so the next ones can be saved & sorted. */
        if(need_sorting == true)
        {
            std::vector<Club_in_Table>::iterator first = std::get<2>(searcher);
            std::vector<Club_in_Table>::iterator last = std::get<3>(searcher);

            /* Find first iterator of range of unsorted clubs. */
            std::vector<std::vector<Club_in_Table>::iterator>::iterator find_first = std::find_if(copy_of_clubs.begin(), copy_of_clubs.end(),
                                                                                                  [&first, &iterator_comparision]
                                                                                                  (std::vector<Club_in_Table>::iterator current)
                    -> bool {return iterator_comparision(first, current); });

            /* Find last iterator of range of unsorted clubs. */
            std::vector<std::vector<Club_in_Table>::iterator>::iterator find_last = std::find_if(copy_of_clubs.begin(), copy_of_clubs.end(),
                                                                                                 [&last, &iterator_comparision]
                                                                                                 (std::vector<Club_in_Table>::iterator current)
                    -> bool {return iterator_comparision(last, current); } );

            /* Remove range of unsorted clubs. */
            std::vector<std::vector<Club_in_Table>::iterator>::iterator position_to_insert_sorted_iterators =
                    copy_of_clubs.erase(find_first, find_last +1);

            std::sort(iterators.begin(), iterators.end(), iterator_sort_comparision);

            /* Insert already sorted clubs. */
            copy_of_clubs.insert(position_to_insert_sorted_iterators, iterators.begin(), iterators.end());

            /* Remove sorted iterators, so the next ranges of clubs could be sorted. */
            iterators.clear();
            need_sorting = false;
        }
    }


    /* Save new club hierarchy */
    std::vector<Club_in_Table> clubs_finished;
    for(auto iter = copy_of_clubs.begin(); iter != copy_of_clubs.end(); ++iter)
    {
        clubs_finished.emplace_back(**iter);
    }
    clubs = clubs_finished;
}



void Bundesliga::Sort_By_Goals_Scored()
{

    /* We know that teams will be already grouped by points and goal difference. Now I need to sort clubs that have the same goal difference,
     * but more goals scored. */

    std::vector<std::vector<Club_in_Table>::iterator> iterators;
    bool need_sorting = false;

    std::vector<std::vector<Club_in_Table>::iterator> copy_of_clubs;
    for(auto iter = clubs.begin(); iter != clubs.end(); ++iter)
        copy_of_clubs.push_back(iter);

    for(auto club_iter = clubs.begin(); club_iter != clubs.end(); ++club_iter)
    {
        auto searcher { Search_All_Equal_Goal_Difference(club_iter, copy_of_clubs) };
        if(std::get<0>(searcher) == true)
        {
            Add_Matching_Iterators(std::get<1>(searcher), iterators);
            need_sorting = true;
        }
        /* Sort currently saved iterators and erase them, so the next ones can be saved & sorted. */
        if(need_sorting == true)
        {
            std::vector<Club_in_Table>::iterator first = std::get<2>(searcher);
            std::vector<Club_in_Table>::iterator last = std::get<3>(searcher);

            /* Find first iterator of range of unsorted clubs. */
            std::vector<std::vector<Club_in_Table>::iterator>::iterator find_first = std::find_if(copy_of_clubs.begin(), copy_of_clubs.end(),
                                                                                                  [&first] (std::vector<Club_in_Table>::iterator current)
                    -> bool {return Club_in_Table::Iterator_Based_Comparator_for_Clubs(first, current); });

            /* Find last iterator of range of unsorted clubs. */
            std::vector<std::vector<Club_in_Table>::iterator>::iterator find_last = std::find_if(copy_of_clubs.begin(), copy_of_clubs.end(),
                                                                                                 [&last] (std::vector<Club_in_Table>::iterator current)
                    -> bool {return Club_in_Table::Iterator_Based_Comparator_for_Clubs(last, current); } );

            /* Remove range of unsorted clubs. */
            std::vector<std::vector<Club_in_Table>::iterator>::iterator position_to_insert_sorted_iterators =
                    copy_of_clubs.erase(find_first, find_last +1);

            std::sort(iterators.begin(), iterators.end(), Club_in_Table::Iterator_Based_Comparator_for_Goals_Scored);

            /* Insert already sorted clubs. */
            copy_of_clubs.insert(position_to_insert_sorted_iterators, iterators.begin(), iterators.end());

            /* Remove sorted iterators, so the next ranges of clubs could be sorted. */
            iterators.clear();
            need_sorting = false;
        }
    }


    /* Save new club hierarchy */
    std::vector<Club_in_Table> clubs_finished;
    for(auto iter = copy_of_clubs.begin(); iter != copy_of_clubs.end(); ++iter)
    {
        clubs_finished.emplace_back(**iter);
    }
    clubs = clubs_finished;
}


bool Bundesliga::Check_if_Identical_Everything(const Club_in_Table &club_1, const Club_in_Table &club_2)
{
    return Check_if_Identical_GoalDifference(club_1, club_2) && club_1.goals_scored == club_2.goals_scored;
}


void Bundesliga::Sort_By_Name()
{
    //So now I need to mark teams that have in common: points, difference of goals, goals scored (So actually all of these 3 must be the same)
    //We know that clubs are already sorted how they should be. We should only compare clubs that have identical [points, difference goals, goals scored].

    std::vector<std::vector<Club_in_Table>::iterator> iterators;
    bool need_sorting = false;

    std::vector<std::vector<Club_in_Table>::iterator> copy_of_clubs;
    for(auto iter = clubs.begin(); iter != clubs.end(); ++iter)
        copy_of_clubs.push_back(iter);

    for(auto club_iter = clubs.begin(); club_iter != clubs.end(); ++club_iter)
    {
        auto searcher { Search_All_Equal_Everything(club_iter, copy_of_clubs) };
        if(std::get<0>(searcher) == true)
        {
            Add_Matching_Iterators(std::get<1>(searcher), iterators);
            need_sorting = true;
        }
        /* Sort currently saved iterators and erase them, so the next ones can be saved & sorted. */
        if(need_sorting == true)
        {
            std::vector<Club_in_Table>::iterator first = std::get<2>(searcher);
            std::vector<Club_in_Table>::iterator last = std::get<3>(searcher);

            /* Find first iterator of range of unsorted clubs. */
            std::vector<std::vector<Club_in_Table>::iterator>::iterator find_first = std::find_if(copy_of_clubs.begin(), copy_of_clubs.end(),
                                                                                                  [&first] (std::vector<Club_in_Table>::iterator current)
                    -> bool {return Club_in_Table::Iterator_Based_Comparator_for_Clubs(first, current); });

            /* Find last iterator of range of unsorted clubs. */
            std::vector<std::vector<Club_in_Table>::iterator>::iterator find_last = std::find_if(copy_of_clubs.begin(), copy_of_clubs.end(),
                                                                                                 [&last] (std::vector<Club_in_Table>::iterator current)
                    -> bool {return Club_in_Table::Iterator_Based_Comparator_for_Clubs(last, current); } );

            /* Remove range of unsorted clubs. */
            std::vector<std::vector<Club_in_Table>::iterator>::iterator position_to_insert_sorted_iterators =
                    copy_of_clubs.erase(find_first, find_last +1);

            std::sort(iterators.begin(), iterators.end(), Club_in_Table::Iterator_Based_Comparator_for_Names);

            /* Insert already sorted clubs. */
            copy_of_clubs.insert(position_to_insert_sorted_iterators, iterators.begin(), iterators.end());

            /* Remove sorted iterators, so the next ranges of clubs could be sorted. */
            iterators.clear();
            need_sorting = false;
        }
    }


    /* Save new club hierarchy */
    std::vector<Club_in_Table> clubs_finished;
    for(auto iter = copy_of_clubs.begin(); iter != copy_of_clubs.end(); ++iter)
    {
        clubs_finished.emplace_back(**iter);
    }
    clubs = clubs_finished;
}














