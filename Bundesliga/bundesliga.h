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

private:
    std::vector<Club_in_Table> clubs;
    void Sort_Table();
    void Sort_By_Goals();
    void Sort_By_Goals_Scored();
};


struct Club_in_Table
{
    std::string name;

    int matches_played = 0, matches_won = 0, matches_drawn = 0, matches_lost = 0;
    int goals_scored = 0, goals_conceded = 0;
    unsigned points = 0;

    bool operator==(const Club_in_Table &club)
    {
        return club.name == this->name;
    }

    bool operator==(const std::string &name)
    {
        return name == this->name;
    }

//    bool operator < (const int points)
//    {
//        return points < this->points;
//    }

    friend bool operator < (const unsigned points, const Club_in_Table &club)
    {
        return points < club.points;
    }

    friend bool operator < (const Club_in_Table &club, const unsigned points)
    {
        return points < club.points;
    }

    friend bool operator < (const int goals, const Club_in_Table &club)
    {
        return goals < club.goals_scored;
    }

    friend bool operator < (const Club_in_Table &club, const int goals)
    {
        return goals < club.goals_scored;
    }
};



#endif // BUNDESLIGA_H
