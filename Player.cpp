//
// Created by shlom on 27/11/2022.
//

#include "Player.h"
#include <cstdlib>


Player::Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int CardsReceived, bool goalKeeper) :
        m_id(playerId), m_team(teamId), m_gamePlayed(gamesPlayed), m_ability(ability), m_cards(CardsReceived),
        m_goalKeeper(goalKeeper), m_spirit(spirit),
        m_closest_left(nullptr), m_closest_right(nullptr) {}

bool Player::operator<(const Player &other) const {
    if (this->m_ability < other.getGoalsScored())
        return true;
    if (this->m_ability == other.getGoalsScored()) {
        if (this->m_cards > other.getCardsReceived())
            return true;
        if (this->m_cards == other.getCardsReceived())
            if (this->m_id < other.getID())
                return true;
    }
    return false;
}

bool Player::operator>(const Player &other) const {
    return m_id > other.getID();
}


void Player::setGamePlayed(int gamesPlayed) {
    m_gamePlayed = gamesPlayed;
}

void Player::increaseGamePlayed(int gamesPlayed) {
    m_gamePlayed += gamesPlayed;
}

void Player::setGoals(int goals) {
    m_ability += goals;
}

void Player::setCards(int cardsReceived) {
    m_cards += cardsReceived;
}

int Player::getGamesPlayed() const {
    return m_gamePlayed;
}

int Player::getGoalsScored() const {
    return m_ability;
}

int Player::getCardsReceived() const {
    return m_cards;
}

int Player::getID() const {
    return m_id;
}

/*void Player::setTeam(const shared_ptr<Team>& newTeam) {
    m_team->removePlayer(this);
    newTeam->addPlayer(this);
    m_team=newTeam;
}*/

void Player::setClosestLeft(Player *left) {
    m_closest_left = left;
}

void Player::setClosestRight(Player *right) {
    m_closest_right = right;
}


Player *Player::getClosestRight() const {
    return m_closest_right;
}

Player *Player::getClosestLeft() const {
    return m_closest_left;
}


/*shared_ptr<Team> Player::getTeam() const {
    return m_team;
}*/

Player *Player::getClosest() const {
    if (!m_closest_left && !m_closest_right) {
        return nullptr;
    }
    if (!m_closest_left) {
        return m_closest_right;
    }
    if (!m_closest_right) {
        return m_closest_left;
    }

    int distanceGoalsLeft = abs(m_ability - m_closest_left->getGoalsScored());
    int distanceGoalsRight = abs(m_closest_right->getGoalsScored() - m_ability);
    int distanceCardsLeft = abs(m_cards - m_closest_left->getCardsReceived());
    int distanceCardsRight = abs(m_closest_right->getCardsReceived() - m_cards);
    int distanceIdsLeft = abs(m_id - m_closest_left->getID());
    int distanceIdsRight = abs(m_closest_right->getID() - m_id);

    if (distanceGoalsLeft < distanceGoalsRight)
        return m_closest_left;
    if (distanceGoalsLeft == distanceGoalsRight) {
        if (distanceCardsLeft < distanceCardsRight)
            return m_closest_left;
        if (distanceCardsLeft == distanceCardsRight)
            if (distanceIdsLeft < distanceIdsRight)
                return m_closest_left;
    }
    return m_closest_right;
}

int Player::getTeamID() const {
    return m_team;
}


Player::~Player() {
    m_closest_right = nullptr;
    m_closest_left = nullptr;
}

bool Player::isGoalkeeper() const {
    return m_goalKeeper;
}

int Player::getMAbility() const {
    return m_ability;
}

const permutation_t& Player::getMSpirit() const {
    return m_spirit;
}

void Player::MulSpiritPlayer(const permutation_t &mSpiritPlayer) {
    m_spirit = (mSpiritPlayer)*this->m_spirit;

}

void Player::MulSpiritPlayerInv(const permutation_t &mSpiritPlayer) {
    m_spirit = this->m_spirit*(mSpiritPlayer);
}


