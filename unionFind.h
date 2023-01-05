//
// Created by shlom on 29/12/2022.
//

#ifndef AVLTREE_H_UNIONFIND_H
#define AVLTREE_H_UNIONFIND_H

#include "DoubleHashing.h"
#include "RankTree.h"
#include "Team.h"

const bool FIRST_ARRAY = true;
const bool SECOND_ARRAY = false;

template<typename Value, typename Value1>
struct Node {
private:
    Value m_value;
    Node<Value, Value1>*  m_father;
    Value1 m_root;

public:
    Node(): m_father(nullptr), m_root(nullptr)
    {}
    Node(Value value): m_value(value), m_father(nullptr), m_root(nullptr)
    {}
    void setFather(Node<Value, Value1> *father)
    {
        this->m_father=father;
    }
    Node* getFather()
    {
        return m_father;
    }
    Value getValue()
    {
        return m_value;
    }

    void setRoot(Value1 team) {
    m_root = team;
}

Value1 getMRoot() const {
    return m_root;
}


};




template<typename Key, typename Value, typename Value1>
class unionFind{
private:
    //Array  of players
    DoubleHashing<Key, Node<Value, Value1>>* m_array;
    //Tree  of teams
    RankTree<Value1>* m_teams;
    RankTree<Value1>* m_ability_teams;

public:
    unionFind():
            m_array (new DoubleHashing<Key, Node<Value, Value1>>()),
            m_teams(new RankTree<Value1>(BY_IDS)),
            m_ability_teams(new RankTree<Value1>(BY_ABILITY))
    {}

    ~unionFind(){
        delete m_ability_teams;
        delete m_teams;
        delete m_array;
    }

    Node<Value, Value1>* find(const Key &key);
    Value findPlayer(const Key &key) const;
    Value1 findGroup(const Key &key) const;
    void union_(Key key1, Key key2);
    int rankOfNode(Node<Value, Value1>* node);
    void makeSet(Value val, Key key);
    void print();
    void insertGroup(const Value1 &val,const Key &key);
    void removeGroup(const Key &key);

    RankTree<Value1>* getMSpiritTeams() const;
};



template<typename Key, typename Value, typename Value1>
void unionFind<Key, Value, Value1>::union_(Key key1, Key key2) {
    Value1 buyerTeam = m_teams->findInt(m_teams->getRoot(), key1)->getValue();
    Value1 boughtTeam = m_teams->findInt(m_teams->getRoot(), key2)->getValue();

    if(!buyerTeam->getMRootPlayer()) {
        m_teams->remove(m_teams->getRoot(), buyerTeam);
        m_ability_teams->remove(m_ability_teams->getRoot(), buyerTeam);
        m_ability_teams->remove(m_ability_teams->getRoot(), boughtTeam);
        m_teams->remove(m_teams->getRoot(), boughtTeam);
        boughtTeam->setMTeamId(key1);
        m_teams->insert(boughtTeam);
        m_ability_teams->insert(boughtTeam);
        return;
    }
    if(!boughtTeam->getMRootPlayer()) {
        m_teams->remove(m_teams->getRoot(), boughtTeam);
        m_ability_teams->remove(m_ability_teams->getRoot(), boughtTeam);
        return;
    }

    Node<Value, Value1>* rootOfBuyerTeam = find(buyerTeam->getMRootPlayer()->getID());
    Node<Value, Value1>* rootOfBoughtTeam = find(boughtTeam->getMRootPlayer()->getID());

    if(buyerTeam->size() >= boughtTeam->size()){
        // making the union + "boxes" method
        rootOfBoughtTeam->getValue()->increaseGamePlayed(-buyerTeam->getMRootPlayer()->getGamesPlayed());
        rootOfBoughtTeam->getValue()->MulSpiritPlayer(buyerTeam->getMSpiritTeam()*buyerTeam->getMRootPlayer()->getMSpirit().inv());

        rootOfBoughtTeam->setFather(rootOfBuyerTeam);
        rootOfBoughtTeam->setRoot(nullptr);

        // update new team fields
        buyerTeam->setPoints(boughtTeam->getPoints());
        buyerTeam->setMNumOfPlayers(boughtTeam->size());
        buyerTeam->MulSpiritTeam(boughtTeam->getMSpiritTeam());
        m_ability_teams->remove(m_ability_teams->getRoot(), buyerTeam);
        buyerTeam->setMAbility(boughtTeam->getMAbility());
        m_ability_teams->insert( buyerTeam);
        buyerTeam->setNumOfGoalKeepers(boughtTeam->getNumOfGoalKeepers());

        // remove the bought team
        m_teams->remove(m_teams->getRoot(), boughtTeam);
        m_ability_teams->remove(m_ability_teams->getRoot(), boughtTeam);
    }
    else{
        // making the union + "boxes" method
        rootOfBuyerTeam->getValue()->increaseGamePlayed(-boughtTeam->getMRootPlayer()->getGamesPlayed());
        boughtTeam->getMRootPlayer()->MulSpiritPlayer(buyerTeam->getMSpiritTeam());
        buyerTeam->getMRootPlayer()->MulSpiritPlayer(boughtTeam->getMRootPlayer()->getMSpirit().inv());

        rootOfBuyerTeam->setFather(rootOfBoughtTeam);
        rootOfBuyerTeam->setRoot(nullptr);

        // update new team fields
        boughtTeam->setPoints(buyerTeam->getPoints());
        boughtTeam->setMNumOfPlayers(buyerTeam->size());
        boughtTeam->MulSpiritTeam(buyerTeam->getMSpiritTeam());
        m_ability_teams->remove(m_ability_teams->getRoot(), boughtTeam);
        boughtTeam->setMAbility(buyerTeam->getMAbility());
        m_ability_teams->insert( boughtTeam);
        boughtTeam->setNumOfGoalKeepers(buyerTeam->getNumOfGoalKeepers());
        // remove the unite team from tree  by ID
        m_teams->remove(m_teams->getRoot(), boughtTeam);
        // update id
        boughtTeam->setMTeamId(buyerTeam->getID());

        // remove the bought team
        m_teams->remove(m_teams->getRoot(), buyerTeam);
        m_ability_teams->remove(m_ability_teams->getRoot(), buyerTeam);
        // return the unite team to the team after remove the other one
        m_teams->insert(boughtTeam);
    }
}


template<typename Key, typename Value, typename Value1>
int unionFind<Key, Value, Value1>::rankOfNode(Node<Value, Value1>* node) {
    int i=0;
    while(node->getFather())
    {
        i++;
        node = node->getFather();
    }
    return node->getTeam.getSize();
}

template<typename Key, typename Value, typename Value1>
void unionFind<Key, Value, Value1>::makeSet(Value val, Key key) {
    Node<Value, Value1>* playerNode = new Node<Value, Value1>(val);
    RankNode<Value1>* team = m_teams->findInt(m_teams->getRoot(), val->getTeamID());
    // if the team exist and the player doesnt exist
    if(team && !(m_array->get(key)))
    {
        // update the team ability
        m_ability_teams->remove(m_ability_teams->getRoot(), team->getValue());
        team->getValue()->setMAbility(val->getMAbility());
        m_ability_teams->insert(team->getValue());


        shared_ptr<Player> father = team->getValue()->getMRootPlayer();

        // if not first one
        if(father)
            playerNode->setFather(m_array->get(team->getValue()->getMRootPlayer()->getID()));
        else {
            playerNode->setFather(nullptr);
            playerNode->setRoot(team->getValue());
            team->getValue()->setRoot(val);
        }
        // adding player to hash table
        this->m_array->put(val->getID(), *playerNode);

        delete playerNode;
    }
}

template<typename Key, typename Value, typename Value1>
void unionFind<Key, Value, Value1>::insertGroup(const Value1 &val,const Key &key) {
    if(!m_teams->findInt(m_teams->getRoot(), key))
    {
        m_teams->insert(val);
        m_ability_teams->insert(val);
    }
}

template<typename Key, typename Value, typename Value1>
Value1 unionFind<Key, Value, Value1>::findGroup(const Key &key) const {
    if(m_teams->findInt(m_teams->getRoot(), key)){
        return m_teams->findInt(m_teams->getRoot(), key)->getValue();
    }
    return nullptr;
}

template<typename Key, typename Value, typename Value1>
void unionFind<Key, Value, Value1>::print() {
    m_array->print();
}

template<typename Key, typename Value, typename Value1>
Value unionFind<Key, Value, Value1>::findPlayer(const Key &key) const {
    if (m_array->get(key))
        return m_array->get(key)->getValue();
    return nullptr;
}

template<typename Key, typename Value, typename Value1>
    Node<Value, Value1>* unionFind<Key, Value, Value1>::find(const Key &key) {
    Node<Value, Value1>* tempNode = m_array->get(key);
    Node<Value, Value1>* tempNode2 = tempNode;
    Node<Value, Value1>* tempNode2Father;

        if(tempNode)
        tempNode2Father= tempNode2->getFather();
    else
        tempNode2Father = nullptr;
    int sumGames = 0;
    int toSub =0;
    if (tempNode) {
        // first round searching the root
        while (tempNode->getFather())
        {
            if(tempNode->getFather()) {
                // sum all the gamesPlayed without the root
                sumGames += tempNode->getValue()->getGamesPlayed();
                tempNode = tempNode->getFather();
            }
            //now tempNode is root
        }
        // second round making all the nodes in the path from the leaf to the root, sons of the root
        while (tempNode2Father) {
            tempNode2Father=tempNode2->getFather();
            if(!tempNode2Father)
                break;
            int temp = tempNode2->getValue()->getGamesPlayed();
            tempNode2->getValue()->setGamePlayed(sumGames - toSub);
            toSub += temp;
            tempNode2->setFather(tempNode);
            tempNode2 = tempNode2Father;
        }
        return m_array->get(key);
    }
    return nullptr;
}

template<typename Key, typename Value, typename Value1>
void unionFind<Key, Value, Value1>::removeGroup(const Key &key) {
    if (m_teams->findInt(m_teams->getRoot(), key)){
        Value1 temp = m_teams->findInt(m_teams->getRoot(), key)->getValue();
        m_teams->remove(m_teams->getRoot(), temp);
        m_ability_teams->remove(m_teams->getRoot(), temp);
        temp->setMKickedOut(true);
    }
}

template<typename Key, typename Value, typename Value1>
RankTree<Value1>* unionFind<Key, Value, Value1>::getMSpiritTeams() const{
    return m_ability_teams;
}


#endif //AVLTREE_H_UNIONFIND_H
