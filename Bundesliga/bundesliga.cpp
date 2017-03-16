#include "bundesliga.h"
#include <iostream>
#include <array>
#include <algorithm>
#include <set>
#include <typeinfo>
#include <functional>


using std::cout;
using std::endl;


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
    //Sort_By_Goals_Scored();

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

























void Bundesliga::Sort_By_Goals_Scored() //This doesn't work properly.
{
   /* std::set will hold all clubs with unique points */
    std::set<Club_in_Table, Comparator_For_Set> unique_clubs;
    for(const auto &club : clubs)
    {
        Club_in_Table tmp;
        tmp.points = club.points;
        tmp.goals_scored = club.goals_scored;
        tmp.goals_conceded = club.goals_conceded;
        unique_clubs.insert(tmp);
    }

   while(!unique_clubs.empty())
   {
       Club_in_Table club = *unique_clubs.begin();
       std::pair<std::vector<Club_in_Table>::iterator, std::vector<Club_in_Table>::iterator> ranges;
       ranges = std::equal_range(clubs.begin(), clubs.end(), club, Club_in_Table::Comparator_For_Range);

       std::sort(ranges.first, ranges.second, [](const Club_in_Table &club_1, const Club_in_Table &club_2)
       { return club_1.goals_scored < club_2.goals_scored; });

        unique_clubs.erase(unique_clubs.begin());
   }
}



bool Bundesliga::Check_if_Identical(const Club_in_Table &club_1, const Club_in_Table &club_2)
{
    int goal_difference_club_1 = club_1.goals_scored - club_1.goals_conceded;
    int goal_difference_club_2 = club_2.goals_scored - club_2.goals_conceded;
    return (club_1.points == club_2.points && goal_difference_club_1 == goal_difference_club_2 && club_1.goals_scored == club_2.goals_scored);
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
        if(Check_if_Identical(*club_iter, *(club_iter +1)) == true)
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
















