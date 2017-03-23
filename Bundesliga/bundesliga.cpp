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
    std::pair<size_t, size_t> range_to_correct;
    std::pair<std::vector<Club_in_Table>::iterator, std::vector<Club_in_Table>::iterator> range_to_correct_iterators;

    bool found_first = false;

    for(auto club_iter = clubs.begin(); club_iter != clubs.end(); ++club_iter)
    {
        if(Check_if_Identical_GoalDifference(*club_iter, *(club_iter +1)) == true) //If this doesnt catch everything, write a function that compares all elements.
        {
            if(!found_first)
            {
                size_t range_begin = std::distance(clubs.begin(), club_iter);
                range_to_correct.first = range_begin;
                range_to_correct_iterators.first = club_iter;
                found_first = true;
            }


            iterators.emplace_back(club_iter);
            iterators.emplace_back(club_iter +1);
        }
        /* Sort currently saved iterators and erase them, so the next ones can be saved & sorted. */
        else
        {
            /* Remove repeating iterators */
            for(auto iter = iterators.begin(); iter != iterators.end() -1; ++iter)
            {
                Club_in_Table *club_1 = &(**iter);
                Club_in_Table *club_2 = &(**(iter +1));

                if(Club_in_Table::Comparator_For_Unique_Iterators(*club_1, *club_2) == true)
                {
                    iterators.erase(iter);
                    iter = iterators.begin();
                }
            }

            size_t range_end = std::distance(clubs.begin(), club_iter -1);
            range_to_correct.second = range_end;
            range_to_correct_iterators.second = club_iter -1;

            std::cout << "Before: \n";
            for(auto club : iterators) { std::cout << club->name << "\n"; }

            std::sort(iterators.begin(), iterators.end(), Club_in_Table::Iterator_Based_Comparator_for_Goals_Scored); //Check if this sorts original vector too. If not, then assign original here.
            /* After sorting, I could find which elements were sorted. When I find them, I swap them in original clubs vector.
             * For example, if element 4 changed with element 2, then I can change them in original vector. */

            std::cout << "After: \n";
            for(auto club : iterators) { std::cout << club->name << "\n"; }


            /* Now when you have range saved - find it in clubs vector, erase it, at put at the same places new iteratos */
            std::vector<Club_in_Table>::iterator pos = clubs.erase(range_to_correct_iterators.first, range_to_correct_iterators.second);
            clubs.insert(pos, range_to_correct_iterators.first, range_to_correct_iterators.second);


            found_first = false;
            iterators.clear();

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
















