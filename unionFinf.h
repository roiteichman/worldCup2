//
// Created by shlom on 29/12/2022.
//

#ifndef AVLTREE_H_UNIONFINF_H
#define AVLTREE_H_UNIONFINF_H

#include "DoubleHashing.h"
#include "AVLTree.h"

const bool FIRST_ARRAY = true;
const bool SECOND_ARRAY = false;

template<typename Value>
struct Node {
private:
    Value* m_value;
    Node<Value>* m_father;

public:
    Node() {
        //this->value = value;
    }
    Node(Value* value) {
        m_value = value;
    }
    void setFather(Node<Value> *father)
    {
        this->m_next=father;
    }
    Node* getFather(Node<Value> *father)
    {
        return m_father;
    }
    Value* getValue()
    {
        return m_value;
    }

};




template<typename Key, typename Value, typename Value1>
class unionFind{
private:
    //Array  of players
    DoubleHashing<Key, Node<Value>>* m_array;
    //Tree  of teams
    AVLTree<Value1*> m_teams;

public:
    unionFind():
            m_array (new DoubleHashing<Key, Node<Value>>()),
            m_teams(new AVLTree<Value1*>())
    {}


    Value* find(Key key, bool whichArr);
    int union_(Key key1, Key key2);
    int rankOfNode(Node<Value>* node);
    void insert(Value* val);
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
int unionFind<Key, Value, Value1>::rankOfNode(Node<Value>* node) {
    int i=0;
    while(node->getFather())
    {
        i++;
        node = node->getFather();
    }
    return node->getTeam.getSize();
}

template<typename Key, typename Value, typename Value1>
void unionFind<Key, Value, Value1>::insert(Value *val) {
    Node<Value> p(val);
    this->m_array->put(val->getID(), p);
}

#endif //AVLTREE_H_UNIONFINF_H
