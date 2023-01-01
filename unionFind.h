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
    Node() {
        //this->value = value;
    }
    Node(Value value) {
        m_value = value;
        m_father=nullptr;
    }
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

Value1* getMRootPlayer() const {
    return m_root;
}


};




template<typename Key, typename Value, typename Value1>
class unionFind{
private:
    //Array  of players
    DoubleHashing<Key, Node<Value, Value1>>* m_array;
    //Tree  of teams
    RankTree<Value1> m_teams;
    RankTree<Value1> m_graveyard_teams;
    RankTree<Value1> m_spirit_teams;

public:
    unionFind():
            m_array (new DoubleHashing<Key, Node<Value, Value1>>()),
            m_teams(new RankTree<Value1*>(BY_IDS)),
            m_graveyard_teams(new RankTree<Value1*>(BY_IDS)),
            m_spirit_teams(new RankTree<Value1*>(BY_PARTIAL_SPIRIT))
    {}


    Node<Value, Value1>* find(const Key &key);
    Value1 findGroup(const Key &key) const;
    void union_(Key key1, Key key2);
    int rankOfNode(Node<Value, Value1>* node);
    void makeSet(Value val, Key key);
    void print();
    void insertGroup(const Value1 &val,const Key &key);
    void removeGroup(const Key &key);
};



template<typename Key, typename Value, typename Value1>
void unionFind<Key, Value, Value1>::union_(Key key1, Key key2) {
    Value1 group1 = m_teams.findInt(m_teams.getRoot(), key1)->getValue();
    Value1 group2 = m_teams.findInt(m_teams.getRoot(),key2)->getValue();

    Node<Value, Value1>* rootOfGroup1 = find(group1->getMRootPlayer()->getID());
    Node<Value, Value1>* rootOfGroup2 = find(group2->getMRootPlayer()->getID());
    if(group1->getSize() > group2->getSize){
        rootOfGroup2->setFather(rootOfGroup1);
        rootOfGroup2->getValue()->setGamePlayed(-rootOfGroup1->getValue()->getGamesPlayed());
        m_teams.remove(m_teams.getRoot(), group2);
    }
    else{
        rootOfGroup1->setFather(rootOfGroup2);
        rootOfGroup1->getValue()->setGamePlayed(-rootOfGroup2->getValue()->getGamesPlayed());
        m_teams.remove(m_teams.getRoot(), group1);
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
    RankNode<Value1>* team = m_teams.findInt(m_teams.getRoot(), val->getTeamID());
    // if the team exist and the player doesnt exist
    if(team && !(m_array->get(key)))
    {
        // adding player to hash table
        this->m_array->put(val->getID(), *playerNode);

        // player is first one in team
        team->getValue()->setMAbility(val->getMAbility());
        team->getValue()->MulSpiritTeam(val->getMSpirit());

        shared_ptr<Player> father = team->getValue()->getMRootPlayer();

        // if not first one
        if(father)
            playerNode->setFather(m_array->get(team->getValue()->getMRootPlayer()->getID()));
        else {
            playerNode->setFather(nullptr);
            playerNode->setRoot(team->getValue());
        }
        if(!playerNode->getFather())
        {
            team->getValue()->setRoot(playerNode->getValue());
        }
    }
}

template<typename Key, typename Value, typename Value1>
void unionFind<Key, Value, Value1>::insertGroup(const Value1 &val,const Key &key) {
    if(!m_teams.findInt(m_teams.getRoot(), key))
    {
        m_teams.insert(val);
    }
}

template<typename Key, typename Value, typename Value1>
Value1 unionFind<Key, Value, Value1>::findGroup(const Key &key) const {
    if(m_teams.findInt(m_teams.getRoot(), key)){
        return m_teams.findInt(m_teams.getRoot(), key)->getValue();
    }
    return nullptr;
}

template<typename Key, typename Value, typename Value1>
void unionFind<Key, Value, Value1>::print() {
    m_array->print();
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
    if (tempNode) {
        while (tempNode->getFather())
        {
            if(tempNode->getFather())
                 tempNode=tempNode->getFather();
            //now tempNode is root
        }
        while (tempNode2Father) {
            tempNode2Father=tempNode2->getFather();
            tempNode2->setFather(tempNode);
            tempNode2 = tempNode2Father;
        }
        return m_array->get(key);
    }
    return nullptr;
}

template<typename Key, typename Value, typename Value1>
void unionFind<Key, Value, Value1>::removeGroup(const Key &key) {
    if (m_teams.findInt(m_teams.getRoot(), key)){
        Value1 temp = m_teams.findInt(m_teams.getRoot(), key)->getValue();
        m_teams.remove(m_teams.getRoot(), temp);
        m_spirit_teams.remove(m_teams.getRoot(), temp);
        m_graveyard_teams.insert(temp);
    }
}


#endif //AVLTREE_H_UNIONFIND_H
