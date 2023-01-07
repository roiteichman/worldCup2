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
    increaseNumOfTeams();
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

    decreaseNumOfTeams();
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper) {

    if (teamId <= 0 || playerId <= 0 || gamesPlayed < 0 || cards < 0 || !spirit.isvalid()) {
        return StatusType::INVALID_INPUT;
    }

    if (m_players.find(playerId) || !m_players.findGroup(teamId)) {
        return StatusType::FAILURE;
    }

    // for games of player - sum the field of games play of player in the path
    shared_ptr<Team> team = m_players.findGroup(teamId);
    int gamesOfCaptain = 0;
    permutation_t invOfRoot = permutation_t::neutral();
    if (team->getMRootPlayer()) {
        gamesOfCaptain = team->getMRootPlayer()->getGamesPlayed();
        invOfRoot = team->getMRootPlayer()->getMSpirit().inv();
    }
    team->MulSpiritTeam(spirit);
    /// TODO: Your code goes here
    try {
        shared_ptr<Player> player(
                new Player(playerId, teamId, (invOfRoot)*team->getMSpiritTeam(), gamesPlayed - gamesOfCaptain, ability, cards, goalKeeper));
        m_players.makeSet(player, playerId);
        team->setMLastPlayer(player.get());
    } catch (const bad_alloc &e) {
        team->MulSpiritTeam(spirit.inv());
        return StatusType::ALLOCATION_ERROR;
    }

    if (goalKeeper)
        team->setNumOfGoalKeepers(1);
    team->setMNumOfPlayers(1);

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2) {

    if(teamId1==teamId2 || teamId1<=0 || teamId2<=0){
        return StatusType::INVALID_INPUT;
    }

    shared_ptr<Team> team1 = m_players.findGroup(teamId1);
    shared_ptr<Team> team2 = m_players.findGroup(teamId2);

    if (!team1.get() || !team2.get()) {
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
            int strength1 = team1->getMSpiritTeam().strength();
            int strength2 = team2->getMSpiritTeam().strength();
            if (strength1 < strength2) {
                team2->setPoints(VICTORY);
                winner = TEAM2WONSPIRIT;
            }
            else if (strength1 == strength2) {
                team1->setPoints(DRAW);
                team2->setPoints(DRAW);
                winner = NONE;
            }
            else{
                winner = TEAM1WONSPIRIT;
                team1->setPoints(VICTORY);
            }
        }
        else{
            winner = TEAM1WONPOINTS;
            team1->setPoints(VICTORY);
        }

        team1->getMRootPlayer()->increaseGamePlayed(1);
        team2->getMRootPlayer()->increaseGamePlayed(1);
    }

    return winner;
}



output_t<int> world_cup_t::num_played_games_for_player(int playerId) {
    if (playerId<=0)
        return StatusType::INVALID_INPUT;
    Node<shared_ptr<Player>, shared_ptr<Team>>* player = m_players.find(playerId);
    if(!player)
    {
        return StatusType::FAILURE;
    }
    int sum = 0;
    while(player){
        sum+=player->getValue()->getGamesPlayed();
        player=player->getFather();
    }

    return sum;
    // TODO: Your code goes here
    return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards) {

    if (playerId<=0 || cards<0){
        return StatusType::INVALID_INPUT;
    }
    Node<shared_ptr<Player>, shared_ptr<Team>>* playerNode = m_players.find(playerId);
    if(!playerNode)
    {
        return StatusType::FAILURE;
    }
    // after find, the playerNode is son of the root
    Node<shared_ptr<Player>, shared_ptr<Team>>* fatherNode = playerNode->getFather();
    shared_ptr<Team> team;
    if (fatherNode)
        team = fatherNode->getMRoot();
    else {
        team = playerNode->getMRoot();
    }
    // if the team kicked out
    if (team->isMKickedOut()){
        return StatusType::FAILURE;
    }
    playerNode->getValue()->setCards(cards);
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId) {

    if (playerId<=0){
        return StatusType::INVALID_INPUT;
    }
    // find in O(1) the player
    shared_ptr<Player> player = m_players.findPlayer(playerId);
    if (player){
        return player->getCardsReceived();
    }
    return StatusType::FAILURE;
}

output_t<int> world_cup_t::get_team_points(int teamId) {
    if(teamId<=0)
        return StatusType::INVALID_INPUT;
    if(m_players.findGroup(teamId))
        return m_players.findGroup(teamId)->getPoints();
    else
        return StatusType::FAILURE;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i) {

    if(!getMNumOfTeams() || getMNumOfTeams()<= i || i<0){
        return StatusType::FAILURE;
    }
    RankTree<shared_ptr<Team>>* tree = m_players.getMSpiritTeams();
    return tree->select(i+1, tree->getRoot())->getValue()->getID();
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId) {
    if(playerId<=0)
    {
        return  StatusType::INVALID_INPUT;
    }
    Node<shared_ptr<Player>, shared_ptr<Team>>* player = m_players.find(playerId);
    if(!player)
    {
        return StatusType::FAILURE;
    }
    Node<shared_ptr<Player>, shared_ptr<Team>>* fatherNode= player->getFather();
    permutation_t res = player->getValue()->getMSpirit();
    shared_ptr<Team> team;
    if (fatherNode)
        team = fatherNode->getMRoot();
    else {
        team = player->getMRoot();
    }
    // if there is no player like that or the team kicked out
    if (team->isMKickedOut() || !player->getValue()){
        return StatusType::FAILURE;
    }
    while(player->getFather())
    {
        res = (player->getFather()->getValue()->getMSpirit())*res;
        player = player->getFather();
    }

    return res;
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2) {

    if(teamId1==teamId2 || teamId1<=0 || teamId2<=0){
        return StatusType::INVALID_INPUT;
    }
    // find the groups in log(k)
    shared_ptr<Team> buyerTeam = m_players.findGroup(teamId1);
    shared_ptr<Team> boughtTeam = m_players.findGroup(teamId2);

    if (!buyerTeam || !boughtTeam){
        return StatusType::FAILURE;
    }
    try {
        m_players.union_(teamId1, teamId2);
    }
    catch (const bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }
    decreaseNumOfTeams();
    return StatusType::SUCCESS;
}

void world_cup_t::print() {
    m_players.print();
}

shared_ptr<Player> world_cup_t::getPlayer(int id) {
    return m_players.find(id)->getValue();
}

void world_cup_t::decreaseNumOfTeams() {
    m_numOfTeams--;
}
void world_cup_t::increaseNumOfTeams() {
    m_numOfTeams++;
}

int world_cup_t::getMNumOfTeams() const {
    return m_numOfTeams;
}
