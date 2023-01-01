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

    void setRoot(Value1* player) {
    m_root = player;
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

public:
    unionFind():
            m_array (new DoubleHashing<Key, Node<Value, Value1>>()),
            m_teams(new RankTree<Value1*>())
    {}


    Value* find(const Key &key, bool whichArr);
    bool findGroup(const Key &key) const;
    int union_(Key key1, Key key2);
    int rankOfNode(Node<Value, Value1>* node);
    void makeSet(Value val, Key key);
    void print();
    void insertGroup(const Value1 &val,const Key &key);
};



template<typename Key, typename Value, typename Value1>
int unionFind<Key, Value, Value1>::union_(Key key1, Key key2) {
    Value1* group1= m_teams->find(key1)->getValue();
    Value1* group2 = m_teams->find(key2)->getValue();
    if(group1->getSize() > group2->getSize){
        {
            Value* rootOfGroup1 = find(group1->getRoot()->getID());
            Value* rootOfGroup2 = find(group2->getRoot()->getID());
            rootOfGroup2->setFather(rootOfGroup1);
            m_teams.remove(m_teams.getRoot(), group2);
        }
    }
    return 1;
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
    Node<Value, Value1>* tmp = new Node<Value, Value1>(val);
    RankNode<Value1>* team = m_teams.findInt(m_teams.getRoot(), val->getTeamID());
    if(team && !(m_array->get(key)))
    {
        this->m_array->put(val->getID(), *tmp);
        shared_ptr<Player> father = team->getValue()->getMRootPlayer();
        if(father)
            tmp->setFather(m_array->get(team->getValue()->getMRootPlayer()->getID()));
        else
            tmp->setFather(nullptr);
        if(!tmp->getFather())
        {
            team->getValue()->setRoot(tmp->getValue());
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
bool unionFind<Key, Value, Value1>::findGroup(const Key &key) const {
    return m_teams.findInt(m_teams.getRoot(), key);
}

template<typename Key, typename Value, typename Value1>
void unionFind<Key, Value, Value1>::print() {
    m_array->print();
}


#endif //AVLTREE_H_UNIONFIND_H
