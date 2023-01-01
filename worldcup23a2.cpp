#include "worldcup23a2.h"

const int VICTORY = 3;
const int DRAW = 1;
const int NONE = 0;
const int TEAM1WONPOINTS = 1;
const int TEAM1WONSPIRIT = 2;
const int TEAM2WONPOINTS = 3;
const int TEAM2WONSPIRIT = 4;



world_cup_t::world_cup_t() {
    // TODO: Your code goes here
}

world_cup_t::~world_cup_t() {
    // TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId) {

    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }


    if (!m_players.findGroup(teamId)) {
        shared_ptr<Team> team(new Team(teamId));
        try {
            m_players.insertGroup(team, teamId);
        } catch (const bad_alloc &e) {
            return StatusType::ALLOCATION_ERROR;
        }

    } else {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId) {
    ///TODO: checks
    if (teamId <= 0) {
        return StatusType::INVALID_INPUT;
    }


    if (m_players.findGroup(teamId)) {
        try {
            m_players.removeGroup(teamId);
        } catch (const bad_alloc &e) {
            return StatusType::ALLOCATION_ERROR;
        }

    } else {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper) {

    if (teamId <= 0 || playerId <= 0 || gamesPlayed < 0 || cards < 0 || !spirit.isvalid() ||
        (gamesPlayed == 0 && cards > 0)) {
        return StatusType::INVALID_INPUT;
    }

    if (m_players.find(playerId) || !m_players.findGroup(teamId)) {
        return StatusType::FAILURE;
    }

    // for games of player - sum the field of games play of player in the path
    shared_ptr<Team> team = m_players.findGroup(teamId);
    int gamesOfCaptain = 0;
    if (team->getMRootPlayer()) {
        gamesOfCaptain = team->getMRootPlayer()->getGamesPlayed();
    }

    /// TODO: Your code goes here
    try {
        shared_ptr<Player> player (new Player(playerId, teamId, spirit, gamesPlayed - gamesOfCaptain, ability, cards, goalKeeper));

        m_players.makeSet(player, playerId);
    } catch (const bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    if (goalKeeper){
        team->setNumOfGoalKeepers(1);
    }

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2) {



    shared_ptr<Team> team1 = m_players.findGroup(teamId1);
    shared_ptr<Team> team2 = m_players.findGroup(teamId2);

    if (!team1 || !team2) {
        return StatusType::FAILURE;
    }

    if (!team1->isValid() || !team2->isValid()) {
        return StatusType::FAILURE;
    }

    int winner;
    if (team1->isValid() && team2->isValid()) {
        if (team1->getMAbility() + team1->getPoints() < team2->getMAbility() + team2->getPoints()) {
            team2->setPoints(VICTORY);
            winner = TEAM2WONPOINTS;
        }
        else if (team1->getMAbility() + team1->getPoints() == team2->getMAbility() + team2->getPoints()) {
            if (team1->getMSpiritTeam().strength() < team2->getMSpiritTeam().strength()) {
                team2->setPoints(VICTORY);
                winner = TEAM2WONSPIRIT;
            }
            else if (team1->getMSpiritTeam().strength() == team2->getMSpiritTeam().strength()) {
                team1->setPoints(DRAW);
                team2->setPoints(DRAW);
                winner = NONE;
            }
            else{
                winner = TEAM1WONSPIRIT;
            }
        }
        else{
            winner = TEAM1WONPOINTS;
            team1->setPoints(VICTORY);
        }

        team1->getMRootPlayer()->setGamePlayed(1);
        team2->getMRootPlayer()->setGamePlayed(1);
    }

    return winner;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId) {
    if (playerId<=0)
        return StatusType::INVALID_INPUT;
    if(!m_players.find(playerId))
    {
        return StatusType::FAILURE;
    }
    // TODO: Your code goes here
}

StatusType world_cup_t::add_player_cards(int playerId, int cards) {
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId) {
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId) {
    // TODO: Your code goes here
    return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i) {
    // TODO: Your code goes here
    return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId) {
    // TODO: Your code goes here
    return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2) {
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

void world_cup_t::print() {
    m_players.print();
}

shared_ptr<Player> world_cup_t::getPlayer(int id) {
    return m_players.find(id)->getValue();
}
