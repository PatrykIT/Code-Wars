#include "bundesliga.h"
#include <iostream>
#include <array>
#include <algorithm>


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

    return std::string();
}
