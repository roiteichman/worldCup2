//
// Created by teich on 27/11/2022.
//

#include "Team.h"


const int VALID_TEAM = 11;
/// TODO: change for test or real

Team::Team(int teamId, int point):
        m_teamId(teamId), m_points(point), m_sumOfGoals(0), m_sumOfCards(0), m_numOfPlayers(0), m_numOfGoalKeepers(0),
        m_gamesPlayed(0), m_ability(0), m_spiritTeam(permutation_t::neutral()), m_kickedOut(false),
        m_teamPlayersByStats(RankTree<shared_ptr<Player>>(BY_PARTIAL_SPIRIT)),
        m_teamPlayersByIds(RankTree<shared_ptr<Player>>(BY_IDS)),
        m_topScorer(nullptr), m_rootPlayer(nullptr), m_closest_left(nullptr), m_closest_right(nullptr)
{}

void Team::setPoints(int points) {
    m_points += points;
}

void Team::setGoals(int goals) {
    m_sumOfGoals+=goals;
}

void Team::setCards(int cards) {
    m_sumOfCards+=cards;
}

int Team::getID() const {
    return m_teamId;
}

int Team::getPoints() const {
    return m_points;
}

int Team::getGoals() const {
    return m_sumOfGoals;
}

int Team::getCards() const {
    return m_sumOfCards;
}

int Team::size() const {
    return m_numOfPlayers;
}

bool Team::operator>(const Team &other) const {
    return m_teamId>other.m_teamId;
}


void Team::removePlayer(shared_ptr<Player> player) {
    m_sumOfGoals -= player->getGoalsScored();
    m_sumOfCards -= player->getCardsReceived();
    m_numOfPlayers--;
    if (player->isGoalkeeper()){
        m_numOfGoalKeepers--;
    }


    RankNode<shared_ptr<Player>>* playerNode = m_teamPlayersByStats.find(m_teamPlayersByStats.getRoot(), player);

    // update top scorer
    if (player.get()==m_topScorer){
        // if the top scorer has a parent he is the new top scorer
        if (playerNode->getParent()){
            m_topScorer = &*(playerNode->getParent()->getValue());
            playerNode->getLeft() ? m_topScorer=&*(playerNode->getLeft()->getValue()): nullptr;
        }
        else if (playerNode->getLeft()){
            m_topScorer=&*(playerNode->getLeft()->getValue());///TODO ?
        }
        else{
            m_topScorer = nullptr;
        }
    }

    m_teamPlayersByStats.remove(m_teamPlayersByStats.getRoot(), player);
    m_teamPlayersByIds.remove(m_teamPlayersByIds.getRoot(), player);

}

void Team::addPlayer(const shared_ptr<Player> &player) {
    m_teamPlayersByStats.insert(player);
    m_teamPlayersByIds.insert(player);
    m_numOfPlayers++;
    m_sumOfGoals += player->getGoalsScored();
    m_sumOfCards += player->getCardsReceived();
    if (player->isGoalkeeper()){
        m_numOfGoalKeepers++;
    }
    update_top_scorer(player);
}

void Team::setClosestLeft(Team* left) {
    m_closest_left=left;
}

void Team::setClosestRight(Team* right) {
    m_closest_right=right;
}


Team* Team::getClosestLeft() const {
    return m_closest_left;
}

Team* Team::getClosestRight() const {
    return m_closest_right;
}

RankTree<shared_ptr<Player>> &Team::getTeamPlayerByStats() {
    return m_teamPlayersByStats;
}


RankTree<shared_ptr<Player>> &Team::getTeamPlayerByIds(){
    return m_teamPlayersByIds;
}

int Team::getNumOfGoalKeepers() const {
    return m_numOfGoalKeepers;
}

int Team::getGamesPlayed() const {
    return m_gamesPlayed;
}

void Team::increaseGamesPlayed(int gamesPlayed) {
    m_gamesPlayed+=gamesPlayed;
}

void Team::update_top_scorer(shared_ptr<Player> player) {

    // first player is the top scorer
    if (!m_topScorer){
        m_topScorer=&*player;
        return;
    }
    ///TODO forget cards
    if (m_topScorer->getGoalsScored() < player->getGoalsScored())
    {
        m_topScorer = &*player;
        return;
    }
    if(((m_topScorer->getGoalsScored() == player->getGoalsScored()))) {
        if (m_topScorer->getCardsReceived() > player->getCardsReceived()) {
            m_topScorer = &*player;
            return;
        } else if (m_topScorer->getCardsReceived() == player->getCardsReceived())
            if (m_topScorer->getID() < player->getID())
                m_topScorer = &*player;
    }
}


Player* Team::getTopScorer() const {
    return m_topScorer;
}

void Team::get_all_players(int *const output) {

    int i = 0;
    m_teamPlayersByStats.printInOrderByID(m_teamPlayersByStats.getRoot(), output, i);
}

void Team::setTeamPlayersByStats(const RankTree<shared_ptr<Player>>& TeamPlayersByStats) {
    m_teamPlayersByStats = TeamPlayersByStats;
}

void Team::setTeamPlayersByIds(const RankTree<shared_ptr<Player>>& TeamPlayersByIds) {
    m_teamPlayersByIds = TeamPlayersByIds;
}

void Team::setMNumOfPlayers(int mNumOfPlayers) {
    m_numOfPlayers = mNumOfPlayers;
}

void Team::setNumOfGoalKeepers(int mNumOfGoalKeepers) {
    m_numOfGoalKeepers += mNumOfGoalKeepers;
}

bool Team::isValid() const {
    return m_numOfGoalKeepers;
}

void Team::setRoot(shared_ptr<Player> mRootPlayer) {
    m_rootPlayer = mRootPlayer;
}

shared_ptr<Player> Team::getMRootPlayer() const {
    return m_rootPlayer;
}

void Team::setMAbility(int mAbility) {
    m_ability += mAbility;
}

int Team::getMAbility() const {
    return m_ability;
}

const permutation_t &Team::getMSpiritTeam() const {
    return m_spiritTeam;
}

void Team::MulSpiritTeam(const permutation_t & mSpiritTeam) {
    m_spiritTeam = this->m_spiritTeam.operator*(mSpiritTeam);
}

void Team::setMKickedOut(bool mKickedOut) {
    m_kickedOut = mKickedOut;
}

bool Team::isMKickedOut() const {
    return m_kickedOut;
}

bool Team::operator<(const Team &other) const {
    if (this->m_ability < other.getMAbility())
        return true;
    if (this->m_ability == other.getMAbility()) {
        if (this->m_teamId < other.getID())
            return true;
    }
    return false;
}

