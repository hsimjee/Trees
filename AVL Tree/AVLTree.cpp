#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "AVLTree.h"

using namespace std;

AVLTree::AVLTree(){
    root = 0;
}

// // AVLTree::~AVLTree() {
// //     delete(root);
// // }

// void AVLTree::delete(Node* currNode){
//     if(currNode == 0){
//         return;
//     }
    
//     if(currNode -> left != 0){
//         delete(currNode -> left);
//     }
//     if(currNode -> right != 0){
//         delete(currNode -> right);
//     }
//     delete currNode;
// }

void AVLTree::insert(const string& newNode){
    Node* insertNode = insertBalanced(newNode);
    
    if(insertNode == 0){
        return;
    }
    
    if(height(root) > 1){
        Node *fix = findUnbalancedNode(insertNode);
        
        if(fix == 0){
            return;
        }
        
        int bFactorN = balanceFactor(fix);
        int bFactorL = balanceFactor(fix -> left);
        int bFactorR = balanceFactor(fix -> right);
        if(bFactorN == 2){
            if(bFactorL == 1){
                bFactorL = 2;
                bFactorR = 1;
            }
            else{
                bFactorL = 2;
                bFactorR = -1;
            }
        }
        
        else {
            if(bFactorR == 1) {
                bFactorL = -2;
                bFactorR = 1;
            }
            else{
                bFactorL = -2;
                bFactorR = -1;
            }
        }
        
        if(bFactorL == 2 && bFactorR == 1){
            rotateRight(fix);
        }
        else if(bFactorL == 2 && bFactorR == -1){
            leftright(fix);
        }
        else if(bFactorL == -2 && bFactorR == 1){
            rightleft(fix);
        }
        else if(bFactorL == -2 && bFactorR == -1){
            rotateLeft(fix);
        }
    }
    
    return;
}

Node* AVLTree::insertBalanced(const string& nodeVal){
    Node* newNode = new Node(1, nodeVal);
    if(root == 0){
        root = newNode;
        return root;
    }
    Node* currNode = root;
    while(currNode != 0){
        if(currNode -> data == nodeVal){
            return 0;
        }
        else if(nodeVal < currNode -> data){
            if(currNode -> left == 0){
                currNode -> left = newNode;
                newNode -> parent = currNode;
                return newNode;
            }
            currNode = currNode -> left;
        }
        else{
            if(currNode -> right == 0){
                currNode -> right = newNode;
                newNode -> parent = currNode;
                return newNode;
            }
            currNode = currNode -> right;
        }
    }
    return newNode;
}

int AVLTree::balanceFactor(Node* balanceNode){
    if(balanceNode == 0){
        return -1;
    }
    
    int leftHeight;
    int rightHeight;
    
    leftHeight = height(balanceNode -> left);
    rightHeight = height(balanceNode -> right);

    return leftHeight - rightHeight;
}

void AVLTree::printBalanceFactors(){
    if(root == 0){
        return;
    }
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node* printNode){
    
    if(printNode -> left != 0){
        printBalanceFactors(printNode -> left);
    }
    
    cout << printNode -> data << "(" << balanceFactor(printNode) << "), ";
    
    if(printNode -> right != 0){
        printBalanceFactors(printNode -> right);
    }
    
    return;
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

Node* AVLTree::findUnbalancedNode(Node* currNode){
    Node* nodeParent = 0;
    if(currNode == 0){
        return 0;
    }
    else{
        if(balanceFactor(currNode) >= 2 || balanceFactor(currNode) <= -2){
            return currNode;
        }
        nodeParent = findUnbalancedNode(currNode -> parent);
    }
    
    if(nodeParent != 0){
        return nodeParent;
    }
    
    return 0;
}

void AVLTree::rotateLeft(Node* currNode){
    Node* nodeParent = currNode -> parent;
    bool onLeft;
    
    if(nodeParent != 0){
        if(nodeParent -> left == currNode){
            onLeft = true;
        }
        else if(nodeParent -> right == currNode){
            onLeft = false;
        }
        else{
            return;
        }
    }
    
    Node* curr = currNode;
    Node* currNodeR = currNode -> right;
    Node* currNodeRL = currNode -> right -> left;
    
    currNodeR -> parent = nodeParent;
    
    if(nodeParent == 0){
        root = currNodeR;
    }
    currNodeR -> left = curr;
    curr -> parent = currNodeR;
    curr -> right = currNodeRL;
    
    if(currNodeRL != 0){
        currNodeRL -> parent = curr;
    }
    
    if(nodeParent != 0){
        if(onLeft){
            nodeParent -> left = currNodeR;
        }
        else{
            nodeParent -> right = currNodeR;
        }
    }
}

void AVLTree::rotateRight(Node* currNode){
    Node* nodeParent = currNode -> parent;
    bool onLeft;
    
    if(nodeParent != 0){
        if(nodeParent -> left == currNode){
            onLeft = true;
        }
        else if(nodeParent -> right == currNode){
            onLeft = false;
        }
        else{
            return;
        }
    }
    
    Node* curr = currNode;
    Node* currNodeL = currNode -> left;
    Node* currNodeLR = currNode -> left -> right;
    
    currNodeL -> parent = nodeParent;
    
    if(nodeParent == 0){
        root = currNodeL;
    }
    currNodeL -> right = curr;
    curr -> parent = currNodeL;
    curr -> left = currNodeLR;
    
    if(currNodeLR != 0){
        currNodeLR -> parent = curr;
    }
    
    if(nodeParent != 0){
        if(onLeft){
            nodeParent -> left = currNodeL;
        }
        else{
            nodeParent -> right = currNodeL;
        }
    }
}

void AVLTree::leftright(Node* currNode){
    rotateLeft(currNode -> left);
    rotateRight(currNode);
}

void AVLTree::rightleft(Node* currNode){
    rotateRight(currNode -> right);
    rotateLeft(currNode);
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}


int AVLTree::height(Node* searchNode) const{
    if (searchNode == 0) {
        return -1;
    }
    
    if(searchNode -> left == 0 && searchNode -> right == 0){
        return 0;
    }
    
    
    int leftH = 0;
    int rightH = 0;
    
    if(searchNode -> left != 0){
        leftH = height(searchNode -> left);
    }
    
    if(searchNode -> right != 0){
        rightH = height(searchNode -> right);
    }
    
    if(rightH >= leftH){
        return 1 + rightH;
    }
    
    else{
        return 1 + leftH;
    }
}