//
// Created by teich on 27/11/2022.
//


#ifndef WORLD_CUP_PLAYER_H
#define WORLD_CUP_PLAYER_H


#include <memory>
#include "wet2util.h"
//#include "team.h"

using namespace std;

class Player{
private:
    int m_id;
    int m_team;
    int m_gamePlayed;
    int m_ability;
    int m_cards;
    bool m_goalKeeper;
    permutation_t m_spirit;
    Player* m_closest_left;
    Player* m_closest_right;


public:
    Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int scoredGoals, int CardsReceived, bool goalKeeper);
    ~Player();
    Player (const Player& player) = delete;
    Player& operator = (const Player& player) = delete;
    bool operator< (const Player& other) const;
    bool operator> (const Player& other) const;
    void setGamePlayed (int gamesPlayed);
    void increaseGamePlayed(int gamesPlayed);
    void setGoals (int goals);
    void setCards (int cardsReceived);
    void setClosestLeft (Player* left);
    void setClosestRight (Player* right);

    int getID() const;
    int getTeamID() const;
    int getGamesPlayed () const;
    int getGoalsScored () const;
    int getCardsReceived () const;
    bool isGoalkeeper() const;

    int getMAbility() const;

    const permutation_t& getMSpirit() const;
    void MulSpiritPlayer(const permutation_t & mSpiritPlayer);
    void MulSpiritPlayerInv(const permutation_t & mSpiritPlayer);

    Player* getClosestLeft() const;
    Player* getClosestRight() const;
    Player* getClosest() const;
};




#endif //WORLD_CUP_PLAYER_H
