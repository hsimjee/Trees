#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include "Node.h"

using namespace std;

class AVLTree {
    private:
        Node* root;
        
    public:
        AVLTree();
        void insert(const string &);
        int balanceFactor(Node*);
        void printBalanceFactors();
        void visualizeTree(const string &);
    
    private:
        Node* findUnbalancedNode(Node*);
        Node* insertBalanced(const string &);
        void rightleft(Node*);
        void leftright(Node*);
        void rotateLeft(Node*);
        void rotateRight(Node*);
        void printBalanceFactors(Node *);
        void visualizeTree(ofstream &, Node *);
        int height(Node*) const;
        // void delete(Node*);
};

#endif