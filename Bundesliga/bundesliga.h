#ifndef BUNDESLIGA_H
#define BUNDESLIGA_H

#include <vector>
#include <string>
#include <initializer_list>
#include <iostream>
#include <tuple>

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
    void Sort_By_Goals_Scored_Helper();
    void Sort_By_Name();


    bool Check_if_Identical_GoalDifference(const Club_in_Table &club_1, const Club_in_Table &club_2);
    bool Check_if_Identical_Everything(const Club_in_Table &club_1, const Club_in_Table &club_2);
    std::tuple<bool, std::vector<std::vector<Club_in_Table>::iterator>, std::vector<Club_in_Table>::iterator , std::vector<Club_in_Table>::iterator>
    Search_All (std::vector<Club_in_Table>::iterator club_to_analyse,
                std::vector<std::vector<Club_in_Table>::iterator> &copy_of_clubs);
    void Print_Clubs();
};


struct Club_in_Table
{
    std::string name;

    int matches_played = 0, matches_won = 0, matches_drawn = 0, matches_lost = 0;
    int goals_scored = 0, goals_conceded = 0;
    unsigned points = 0;


    bool operator==(const Club_in_Table &club) const
    {
        return club.name == this->name;
    }

    bool operator==(const std::string &name) const
    {
        return name == this->name;
    }

    static void Swap(Club_in_Table &lhs, Club_in_Table &other) //To do: Add function that swaps iterators in club vector.
    {
        std::cout << "Swapping: " << lhs.name << " with " << other.name << "\n";
        std::swap(lhs, other);
    }


    /* std::equal range needs 2 overloads:
     * Two elements, a and b are considered equivalent if (!(a<b) && !(b<a)) */

    /* Friend function is like static function; it cannot access member variables. */
    friend bool operator < (const int goals, const Club_in_Table &club)
    {
        return goals < club.goals_scored;
    }

    friend bool operator < (const Club_in_Table &club, const int goals)
    {
        return goals < club.goals_scored; //Called also when counting differences - bad!
    }

    friend bool operator < (const Club_in_Table &club_1, const Club_in_Table &club_2)
    {
        std::cout << "Comparing: " << club_1.name << " & " << club_2.name << "\n";
        return club_1.name < club_2.name;
    }

    static bool Iterator_Based_Comparator_for_Names (const std::vector<Club_in_Table>::iterator &club_1,
                            const std::vector<Club_in_Table>::iterator &club_2)
    {
        return club_1->name < club_2->name;
    }

    static bool Iterator_Based_Comparator_for_Goals_Scored (const std::vector<Club_in_Table>::iterator &club_1,
                            const std::vector<Club_in_Table>::iterator &club_2)
    {
        return club_1->goals_scored > club_2->goals_scored;
    }

    static bool Iterator_Based_Comparator_for_Clubs(const std::vector<Club_in_Table>::iterator &club_1,
                                                    const std::vector<Club_in_Table>::iterator &club_2)
    {
        return club_1->name == club_2->name && club_1->points == club_2->points; //I should compare every attribute, but that should be okay.
    }

    static bool Comparator_For_Unique_Iterators(const Club_in_Table &club_1,
                                                const Club_in_Table &club_2)
    {
        return &club_1 == &club_2; //Compare by memory addresess.
    }

    static bool Comparator_For_Range(const Club_in_Table &club_1, const Club_in_Table &club_2)
    {
        return club_1.points == club_2.points &&
       ((club_1.goals_scored - club_1.goals_conceded) == (club_2.goals_scored - club_2.goals_conceded));
    }
};

struct Comparator_For_Set
{
    bool operator()(const Club_in_Table &club_1, const Club_in_Table &club_2)
    {
        return club_1.points < club_2.points;
    }
};

#endif // BUNDESLIGA_H
