#ifndef __NODE_H__
#define __NODE_H__
#include <string>
#include <iostream>

using namespace std;

class Node{
    friend class Tree;
    
    private:
        string small;
        string large;
        Node* left;
        Node* middle;
        Node* right;
        Node* parent;
        
    public:
        Node(string small) : small(small), large(""), 
        left(0), middle(0), right(0), parent(0), is3Node(false) {}
        Node(string small, string large) : small(small), large(large), 
        left(0), middle(0), right(0), parent(0), is3Node(true) {}
        
    private:
        bool is3Node;
};

#endif