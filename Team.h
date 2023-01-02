//
// Created by shlom on 28/11/2022.
//

#ifndef MAIN_CPP_TEAM_H
#define MAIN_CPP_TEAM_H
#include <memory>
#include "Player.h"
#include "RankTree.h"
#include "DoubleHashing.h"
#include "wet2util.h"

using namespace std;

class Team{

private:
    int m_teamId;
    int m_points;
    int m_sumOfGoals;
    int m_sumOfCards;
    int m_numOfPlayers;
    int m_numOfGoalKeepers;
    int m_gamesPlayed;
    int m_ability;
    permutation_t m_spiritTeam;
    bool m_kickedOut;
    Player* m_lastPlayer =nullptr;

private:

    RankTree<shared_ptr<Player>> m_teamPlayersByStats;
    RankTree<shared_ptr<Player>> m_teamPlayersByIds;
    Player* m_topScorer;
    shared_ptr<Player> m_rootPlayer;
    Team* m_closest_left;
    Team* m_closest_right;


public:
    explicit Team(int teamId, int point=0);
    ~Team() = default;
    Team (const Team& team) = delete;
    Team& operator = (const Team& team) = delete;

    bool operator> (const Team& other) const;
    bool operator<(const Team &other) const;

    void setRoot(shared_ptr<Player> mRootPlayer);
    shared_ptr<Player> getMRootPlayer() const;
    void setPoints (int points);
    void setGoals (int goals);
    void setCards (int cards);
    void setTeamPlayersByStats(const RankTree<shared_ptr<Player>>& TeamPlayersByStats);
    void setTeamPlayersByIds(const RankTree<shared_ptr<Player>>& TeamPlayersByIds);
    void setMNumOfPlayers(int mNumOfPlayers);
    void setClosestLeft (Team* left);
    void setClosestRight (Team* right);
    void setNumOfGoalKeepers(int mNumOfGoalKeepers);
    Player *getMLastPlayer() const;
    void setMLastPlayer(Player *mLastPlayer);

    int getMNumOfPlayers() const;

    void setMAbility(int mAbility);

    void setMKickedOut(bool mKickedOut);

    bool isMKickedOut() const;

    const permutation_t &getMSpiritTeam() const;

    void MulSpiritTeam(const permutation_t & mSpiritPlayer);

    int getMAbility() const;


    void removePlayer (shared_ptr<Player> player);
    void addPlayer (const shared_ptr<Player>& player);

    int getNumOfGoalKeepers() const;
    int size() const;
    Team* getClosestLeft() const;
    Team* getClosestRight() const;
    void get_all_players(int *const output);
    int getID () const;
    int getPoints () const;
    int getGoals () const;
    int getCards () const;
    Player* getTopScorer() const;
    int getGamesPlayed() const;

    void increaseGamesPlayed(int gamesPlayed);
    void update_top_scorer(shared_ptr<Player> player);
    bool isValid() const;


    RankTree<shared_ptr<struct Player>> & getTeamPlayerByStats ();
    RankTree<shared_ptr<struct Player>> & getTeamPlayerByIds ();



};
#endif //MAIN_CPP_TEAM_H
