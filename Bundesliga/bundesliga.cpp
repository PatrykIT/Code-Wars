#include "bundesliga.h"
#include <iostream>
#include <array>
#include <algorithm>
#include <set>


using std::cout;
using std::endl;


std::string Bundesliga::table(std::vector<std::string> results)
{
    std::string delimeter = ":";
    std::string delimeter_2 = " ";
    std::string delimeter_3 = " - ";

    std::array<std::string, 2> teams_playing;

    std::string token;



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

    Sort_By_Goals();
    Sort_By_Goals_Scored();

    for(auto &club : clubs)
         std::cout << club.name << " P: " << club.points << " G: " << club.goals_scored << ":" <<
                     club.goals_conceded << "\n";
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
//       ranges = std::equal_range(clubs.begin(), clubs.begin(), points, [&](const int points, const Club_in_Table &club)
//       { return points < club.points; } ); //Why doesn't this work when operator < is commented out? Shouldn't lambda replace it?
       ranges = std::equal_range(clubs.begin(), clubs.end(), points);

       std::sort(ranges.first, ranges.second, [](const Club_in_Table &club_1, const Club_in_Table &club_2)
       { return (club_1.goals_scored - club_1.goals_conceded) > (club_2.goals_scored - club_2.goals_conceded); });

        unique_points.erase(unique_points.begin());
   }
}




void Bundesliga::Sort_By_Goals_Scored()
{
   /* std::set will hold all unique goal differences that are in table */
   std::set<int> unique_goals;
   for(const auto &club : clubs)
       unique_goals.insert(club.goals_scored - club.goals_conceded);

   while(!unique_goals.empty())
   {
       int goals = *unique_goals.begin();
       std::pair<std::vector<Club_in_Table>::iterator, std::vector<Club_in_Table>::iterator> ranges;
       ranges = std::equal_range(clubs.begin(), clubs.end(), goals); //This worked, but I think its a bug :D It compares by points.

       //ranges = std::equal_range(clubs.begin(), clubs.end(), goals, [](const int goal, const Club_in_Table &club)
       //{ return goal < (club.goals_scored - club.goals_conceded); } );
       //Two elements, a and b are considered equivalent if (!(a<b) && !(b<a)). I need 2 overloads for goal differences.

       std::sort(ranges.first, ranges.second, [](const Club_in_Table &club_1, const Club_in_Table &club_2)
       { return club_1.goals_scored > club_2.goals_scored; });

        unique_goals.erase(unique_goals.begin());
   }
}

















