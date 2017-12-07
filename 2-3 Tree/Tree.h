#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
    Node *root;

public:
    Tree( );
    ~Tree( );
    void insert(const string &);
    void preOrder( ) const;
    void inOrder( ) const;
    void postOrder( ) const;
    void remove(const string &);
    bool search (const string &) const;

private:
    void inOrder(Node *) const;
    void postOrder(Node *) const;
    void preOrder(Node *) const;
    Node* searchNode(const string& searchString) const;
    void split(Node*, string, Node*, Node*);
    Node* swap(Node*, string);
    void fix(Node*);
    Node* merge(Node*);
    void redistribute(Node*);
    bool noChildren(Node*);
    Node* findLeafNode(Node*, string);
    string outputMidVal(Node*, string);
    void balance();
    int checkBalance(Node* searchNode);
    int height(Node*);
};

#endif
