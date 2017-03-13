#ifndef BUNDESLIGA_H
#define BUNDESLIGA_H

#include <vector>
#include <string>
#include <initializer_list>

struct Club_in_Table;

class Bundesliga
{
public:
    std::string table(std::vector<std::string> results);

    std::vector<Club_in_Table> clubs;
};


struct Club_in_Table
{
    std::string name;

    int matches_played = 0, matches_won = 0, matches_drawn = 0, matches_lost = 0;
    int goals_scored = 0, goals_conceded = 0;
    int points = 0;

    bool operator==(const Club_in_Table &club)
    {
        return club.name == this->name;
    }

    bool operator==(const std::string &name)
    {
        return name == this->name;
    }

};



#endif // BUNDESLIGA_H
