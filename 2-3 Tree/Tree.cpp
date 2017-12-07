#include <iostream>

#include "Tree.h"

using namespace std;

Tree::Tree(){
    root = 0;
}

Tree::~Tree(){
    Node* currNode = root;

    if(currNode -> left != 0){
        delete(currNode -> left);
    }
    
    if(currNode -> right != 0){
        delete(currNode -> right);
    }
    
    if(currNode -> left == 0 && currNode -> right == 0){
        if(currNode == currNode -> parent -> right){
            currNode -> parent -> right = 0;
        }
        
        if(currNode == currNode -> parent -> left){
            currNode -> parent -> left = 0;
        }
        
        currNode -> parent = 0;
        delete currNode;
    }
    
    return;
}

Node* Tree::findLeafNode(Node* currNode, string nodeString){
    while(!noChildren(currNode)){
        if(nodeString < currNode -> small){
            currNode = currNode -> left;
        }
        else if(currNode -> is3Node && nodeString > currNode -> small && nodeString < currNode -> large){
            currNode = currNode -> middle;
        }
        else{
            currNode = currNode -> right;
        }
    }
    
    return currNode;
}

bool Tree::noChildren(Node* checkChildren){
    if(checkChildren -> right == 0 && checkChildren -> left == 0 && checkChildren -> middle == 0){
        return true;
    }
    return false;
}

string Tree::outputMidVal(Node* checkStrings, string check){
    if(check > checkStrings -> small && check < checkStrings -> large){
        return check;
    }
    
    else if(checkStrings -> small > check){
        return checkStrings -> small;
    }
    
    else{
        return checkStrings -> large;
    }
}

void Tree::insert(const string& nodeString){
    if(root == 0){
        root = new Node(nodeString);
        return;
    }
    
    Node* currNode = root;
    
    currNode = findLeafNode(currNode, nodeString);
    
    if(!currNode -> is3Node){
        if(currNode -> small < nodeString){
            currNode -> large = nodeString;
        }
        else{
            currNode -> large = currNode -> small;
            currNode -> small = nodeString;
        }
        currNode -> is3Node = true;
        return;
    }
    
    else{
        split(currNode, nodeString, root, root);
    }
    balance();
}

void Tree::balance(){
    if(root == 0){
        return;
    }
    if(checkBalance(root) > 0){
        if(!root -> is3Node && !root -> left -> is3Node){
            root -> large = root -> small;
            root -> small = root -> left -> small;
            root -> is3Node = true;
            if(!noChildren(root -> left)){
                root -> middle = root -> left -> right;
                root -> middle -> parent = root;
                Node* del = root -> left;
                root -> left = root -> left -> left;
                root -> left -> parent = root;
                del -> parent = 0;
                delete del;
            }
        }
    }
    if(checkBalance(root) < 0){
        if(!root -> is3Node && !root -> right -> is3Node){
            root -> large = root -> right -> small;
            root -> is3Node = true;
            if(!noChildren(root -> right)){
                root -> middle = root -> right -> left;
                root -> middle -> parent = root;
                Node* del = root -> right;
                root -> right = root -> right -> right;
                root -> right -> parent = root;
                del -> parent = 0;
                delete del;
            }
        }
    }
    return;
}

int Tree::checkBalance(Node* balanceNode){
    int leftHeight;
    int rightHeight;
    leftHeight = height(balanceNode -> left);
    rightHeight = height(balanceNode -> right);

    return leftHeight - rightHeight;
}

int Tree::height(Node* searchNode){
    if(searchNode == 0){
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

void Tree::split(Node* currNode, string nodeString, Node* nL, Node* nR){
    Node* p;
    Node* newL;
    Node* newR;
    Node* newRoot;
    if(currNode == root){
        string midVal = outputMidVal(currNode, nodeString);
        if(midVal == nodeString){
            newRoot = new Node(midVal);
            newL = new Node(root -> small);
            newR = new Node(root -> large);
        }
        else if(midVal == root -> small){
            newRoot = new Node(root -> small);
            newL = new Node(midVal);
            newR = new Node(root -> large);
        }
        else{
            newRoot = new Node(root -> large);
            newL = new Node(root -> small);
            newR = new Node(midVal);
        }
    
        if(!noChildren(root)){
            if(nL -> small == currNode -> right -> small){
                newL -> left = currNode -> left;
                currNode -> left -> parent = newL;
                newL -> right = currNode -> right;
                currNode -> right -> parent = newL;
                newR -> left = nL;
                nL -> parent = newR;
                newR -> right = nR;
                nR -> parent = newR;
            }
            else if(nL -> small == currNode -> left -> small){
                newL -> left = nL;
                nL -> parent = newL;
                newL -> right = nR;
                nR -> parent = newL;
                newR -> left = currNode -> middle;
                currNode -> middle -> parent = newR;
                newR -> right = currNode -> right;
                currNode -> right -> parent = newR;
            }
            else{
                newL -> left = currNode -> left;
                currNode -> left -> parent = newL;
                newL -> right = nL;
                nL -> parent = newL;
                newR -> right = currNode -> right;
                currNode -> right -> parent = newR;
                newR -> left = nR;
                nR -> parent = newR;
            }
        }
        
        newRoot -> left = newL;
        newL -> parent = newRoot;
        newRoot -> right = newR;
        newR -> parent = newRoot;
        root = newRoot;
        return;
    }
    
    else{
        p = currNode -> parent;
    }
    
    string midVal = outputMidVal(currNode, nodeString);
    if(midVal == nodeString){
        newL = new Node(currNode -> small);
        newR = new Node(currNode -> large);
    }
    else if(midVal == currNode -> small){
        newL = new Node(nodeString);
        newR = new Node(currNode -> large);
    }
    else{
        newL = new Node(currNode -> small);
        newR = new Node(nodeString);
    }
    
    if(!noChildren(currNode)){
        if(nL -> small == currNode -> right -> small){
            newL -> left = currNode -> left;
            currNode -> left -> parent = newL;
            newL -> right = currNode -> right;
            currNode -> right -> parent = newL;
            newR -> left = nL;
            nL -> parent = newR;
            newR -> right = nR;
            nR -> parent = newR;
        }
        else if(nL -> small == currNode -> left -> small){
            newL -> left = nL;
            nL -> parent = newL;
            newL -> right = nR;
            nR -> parent = newL;
            newR -> left = currNode -> middle;
            currNode -> middle -> parent = newR;
            newR -> right = currNode -> right;
            currNode -> right -> parent = newR;
        }
        else{
            newL -> left = currNode -> left;
            currNode -> left -> parent = newL;
            newL -> right = nL;
            nL -> parent = newL;
            newR -> right = currNode -> right;
            currNode -> right -> parent = newR;
            newR -> left = nR;
            nR -> parent = newR;
        }
    }
    
    if(p -> is3Node){
        split(p, midVal, newL, newR);
    }
    else{
        p -> is3Node = true;
        if(p -> right == currNode){
            p -> large = midVal;
            p -> middle = newL;
            newL -> parent = p;
            p -> right = newR;
            newR -> parent = p;
        }
        else if(p -> left == currNode){
            p -> large = p -> small;
            p -> small = midVal;
            p -> middle = newR;
            newL -> parent = p;
            p -> left = newL;
            newR -> parent = p;
        }
    }
    return;
}

void Tree::inOrder(Node* currNode) const{
    if(currNode == 0){
        return;
    }
    
    if(currNode -> left != 0){
        inOrder(currNode -> left);
    }
    
    cout << currNode -> small << ", ";
    
    if(currNode -> middle != 0){
        inOrder(currNode -> middle);
    }
    
    if(currNode -> large != ""){
        cout << currNode -> large << ", ";
    }
    
    if(currNode -> right != 0){
        inOrder(currNode -> right);
    }   
    
    return;
}

void Tree::inOrder() const{
    inOrder(root);
    cout << endl;
}

void Tree::postOrder(Node* currNode) const{
    if(currNode == 0){
        return;
    }
    
    if(currNode -> is3Node){
        if(currNode -> left != 0){
            postOrder(currNode -> left);
        }
    
        if(currNode -> middle != 0){
            postOrder(currNode -> middle);
        }
        
        cout << currNode -> small << ", ";
        
        if(currNode -> right != 0){
            postOrder(currNode -> right);
        }
        
        if(currNode -> large != ""){
            cout << currNode -> large << ", ";
        }
    }
    
    else{
    
        if(currNode -> left != 0){
            postOrder(currNode -> left);
        }
        
        if(currNode -> middle != 0){
            postOrder(currNode -> middle);
        }
        
        if(currNode -> right != 0){
            postOrder(currNode -> right);
        }
        
        cout << currNode -> small << ", ";
        
        if(currNode -> large != ""){
            cout << currNode -> large << ", ";
        }
    }
}

void Tree::postOrder() const{
    postOrder(root);
    cout << endl;
}

void Tree::preOrder(Node* currNode) const{
    if(currNode == 0){
        return;
    }
    
    cout << currNode -> small << ", ";
    
    if(currNode -> left != 0){
        preOrder(currNode -> left);
    }
    
    if(currNode -> large != ""){
        cout << currNode -> large << ", ";
    }
    
    if(currNode -> middle != 0){
        preOrder(currNode -> middle);
    }
    
    if(currNode -> right != 0){
        preOrder(currNode -> right);
    }
    
    return;
}

void Tree::preOrder() const{
    preOrder(root);
    cout << endl;
}

void Tree::remove(const string& removeString){
    Node* leafNode;
    if(root == 0){
        return;
    }
    
    Node* currNode = searchNode(removeString);
    if (currNode == 0){
        return;
    }
    
    if(!noChildren(currNode)){
        leafNode = swap(currNode, removeString);
        remove(removeString);
        return;
    }
    else{
        leafNode = currNode;
    }
    
    if(leafNode -> small == removeString){
        if(leafNode -> is3Node){
            leafNode -> is3Node = false;
            leafNode -> small = leafNode -> large;
            leafNode -> large = "";
        }
        else{
            leafNode -> small = "";
            fix(leafNode);
        }
    }
    else{
        leafNode -> is3Node = false;
        leafNode -> large = "";
    }
}

Node* Tree::swap(Node* currNode, string removeS){
    string temp;
    
    if(currNode -> small == removeS){
        if(currNode -> left -> is3Node){
            temp = currNode -> left -> large;
            currNode -> left -> large = currNode -> small;
            currNode -> small = temp;
        }
        else if(currNode -> is3Node){
            if(currNode -> middle -> is3Node){
                temp = currNode -> middle -> small;
                currNode -> middle -> small = currNode -> small;
                currNode -> small = temp;
            }
            else if(currNode -> right -> is3Node){
                temp = currNode -> middle -> small;
                currNode -> middle -> small = currNode -> small;
                currNode -> small = temp;
                temp = currNode -> middle -> small;
                currNode -> middle -> small = currNode -> large;
                currNode -> large = temp;
                temp = currNode -> right -> small;
                currNode -> right -> small = currNode -> large;
                currNode -> large = temp;
            }
        }
        else if(currNode -> right -> is3Node){
            temp = currNode -> small;
            currNode -> small = currNode -> right -> small;
            currNode -> right -> small = temp;
        }
        else if(!currNode -> is3Node){
            temp = currNode -> small;
            currNode -> small = currNode -> right -> small;
            currNode -> right -> small = temp;
        }
        else{
            temp = currNode -> small;
            currNode -> small = currNode -> middle -> small;
            currNode -> middle -> small = temp;
        }
    }
    else{
        if(currNode -> right -> is3Node){
            temp = currNode -> right -> small;
            currNode -> right -> small = currNode -> large;
            currNode -> large = temp;
        }
        else if(currNode -> middle -> is3Node){
            temp = currNode -> middle -> large;
            currNode -> middle -> large = currNode -> large;
            currNode -> large = temp;
        }
        else if(currNode -> left -> is3Node){
            temp = currNode -> middle -> small;
            currNode -> middle -> small = currNode -> large;
            currNode -> large = temp;
            temp = currNode -> middle -> small;
            currNode -> middle -> small = currNode -> small;
            currNode -> small = temp;
            temp = currNode -> left -> large;
            currNode -> left -> large = currNode -> small;
            currNode -> small = temp;
        }
        else{
            temp = currNode -> large;
            currNode -> large = currNode -> right -> small;
            currNode -> right -> small = temp;
        }
    }
    
    return currNode;
}

void Tree::fix(Node* currNode){
    string temp;
    
    if(currNode == root){
        root = 0;
        return;
    }
    
    Node* p = currNode -> parent;
    if(p -> is3Node){
        if(currNode == p -> left){
            if(p -> middle -> is3Node){
                currNode -> small = p -> small;
                temp = p -> middle -> small;
                remove(temp);
                p -> small = temp;
            }
            else if(p -> right -> is3Node){
                currNode -> small = p -> small;
                string temp = currNode -> middle -> small;
                remove(temp);
                p -> small = temp;
            }
            else{
                p -> left -> small = p -> small;
                temp = p -> middle -> small;
                remove(p -> middle -> small);
                p -> left -> large = temp;
                p -> left -> is3Node;
                redistribute(p -> left);
            }
        }
        else if(currNode == p -> middle){
            if(p -> right -> is3Node){
                currNode -> small = p -> large;
                temp = p -> right -> small;
                remove(temp);
                p -> large = temp;
            }
            else if(p -> left -> is3Node){
                currNode -> small = p -> small;
                temp = p -> left -> large;
                remove(temp);
                p -> small = temp;
            }
            else{
                if(p -> left -> small != p -> small){
                    p -> left -> large = p -> small;
                    p -> left -> is3Node = true;
                    redistribute(p -> left);
                }
                p -> small = p -> large;
                p -> large = "";
                p -> is3Node = false;
                p -> middle = 0;
            }
        }
    }
    else{
        currNode = merge(currNode);
        remove(currNode -> small);
        if(p -> small == ""){
            fix(p);
        }
    }
}

void Tree::redistribute(Node* currNode){
    if(noChildren(currNode)){
        return;
    }
    
    if(!currNode -> right -> is3Node){
        currNode -> right -> large = currNode -> right -> small;
        currNode -> right -> small = currNode -> large;
        currNode -> large = "";
        currNode -> is3Node = false;
        redistribute(currNode -> right);
    }
    else if(!currNode -> left -> is3Node){
        currNode -> left -> large = currNode -> small;
        currNode -> small = currNode -> large;
        currNode -> large = "";
        currNode -> is3Node = false;
        redistribute(currNode -> left);
    }
    else{
        split(currNode -> right, currNode -> large, root, root);
        currNode -> large = "";
        currNode -> is3Node = false;
    }
}
    
Node* Tree::merge(Node* currNode){
    Node* par = currNode -> parent;
    if(!par -> is3Node){
        if(currNode == par -> right){
            par -> left -> large = par -> small;
            if(par -> parent != 0){
                par -> left -> parent = par -> parent;
            }
            else{
                root = par -> left;
            }
            par -> left -> is3Node = true;
            par -> left = 0;
            par -> right = 0;
            currNode -> parent = 0;
            par -> parent = 0;
            delete par;
            delete currNode;
        }
        else if(currNode == par -> left){
            par -> right -> large = par -> right -> small;
            par -> right -> small = par -> small;
            if(par -> parent != 0){
                par -> right -> parent = par -> parent;
            }
            else{
                root = par -> right;
            }
            par -> right -> is3Node = true;
            par -> right = 0;
            par -> left = 0;
            currNode -> parent = 0;
            par -> parent = 0;
            delete par;
            delete currNode;
        }
    }
    else{
        if(currNode == par -> left){
            currNode -> small = par -> small;
            currNode -> large = par -> middle -> small;
            currNode -> is3Node = true;
            if(!par -> middle -> is3Node){
                par -> middle -> parent = 0;
                par -> middle = 0;
            }
            else{
                par -> middle -> left = par -> middle -> right;
                par -> middle -> large = "";
                par -> middle -> is3Node = false;
            }
            par -> small = par -> large;
            par -> large = "";
            par -> is3Node = false;
        }
        else if(currNode == par -> middle){
            currNode -> left -> large = par -> small;
            par -> is3Node = false;
            par -> small = par -> large;
            par -> middle = 0;
            par -> large = "";
            par -> is3Node = false;
        }
    }
}


    
    
    
//     if(currNode -> is3Node && noChildren(currNode)){
//         if (currNode -> small == removeString){
//             currNode -> small = currNode -> large;
//             currNode -> large = "";
//             currNode -> is3Node = false;
//             return;
//         }
//         else{
//             currNode -> large = "";
//             currNode -> is3Node = false;
//             return;
//         }
//     }
    
//     if(noChildren(currNode) && currNode == root){
//         delete currNode;
//         root = 0;
//         return;
//     }
    
//     if(currNode == root){
//         if(!currNode -> left -> is3Node){
//             currNode -> small = currNode -> left -> small;
//             currNode -> left -> large = "";
//             currNode -> left -> is3Node = false;
//         }
//         if(!currNode -> right -> is3Node){
//             currNode -> large = currNode -> right -> small;
//             if(noChildren(currNode -> left)){
//             currNode -> left = 0;
//             }
//         }
        
//         if(noChildren(currNode -> right)){
//             currNode -> right = 0;
//         }
//         return;
//     }
    
//     if(!currNode -> is3Node && !currNode -> parent -> is3Node && noChildren(currNode)){
//         if(currNode == currNode -> parent -> left){
//             currNode -> parent -> large = currNode -> parent -> right -> small;
//             currNode -> parent -> right = 0;
//             currNode -> parent -> left = 0;
//             return;
//         }
//         else{
//             currNode -> parent -> large = currNode -> parent -> small;
//             currNode -> parent -> small = currNode -> parent -> left -> small;
//             currNode -> parent -> left = 0;
//             currNode -> parent -> right = 0;
//             return;
//         }
//     }
    
//     if(currNode -> parent -> is3Node && !currNode -> is3Node){
//         if(currNode == currNode -> parent -> right){
//             if(currNode -> parent -> middle -> is3Node){
                
//             }
//             else{
//                 currNode -> small = currNode -> parent -> middle -> small;
//                 currNode -> large = currNode -> parent -> large;
//                 currNode -> parent -> large = "";
//                 currNode -> parent -> middle -> parent = 0;
//                 currNode -> parent -> middle = 0;
//                 currNode -> is3Node = true;
//                 currNode -> parent -> is3Node = false;
//                 return;
//             }
//         }
//         else if(currNode == currNode -> parent -> middle){
//             if(currNode -> parent -> left -> is3Node){
                
//             }
//             else{
//                 currNode -> parent -> left -> large = currNode -> parent -> small;
//                 currNode -> parent -> left -> is3Node = true;
//                 currNode -> parent -> small = currNode -> parent -> large;
//                 currNode -> parent -> large = "";
//                 currNode -> parent -> is3Node = false;
//                 currNode -> parent -> middle = 0;
//                 currNode -> parent = 0;
//                 delete currNode;
//                 return;
//             }
//         }
//         else{
//             currNode -> small = currNode -> parent -> small;
//             currNode -> parent -> small = currNode -> parent -> large;
//             currNode -> parent -> large = "";
//             currNode -> parent -> is3Node = false;
//             if(currNode -> parent -> middle -> is3Node){
                
//             }
//             else{
//                 currNode -> large = currNode -> parent -> middle -> small;
//                 currNode -> parent -> middle -> parent = 0;
//                 currNode -> parent -> middle = 0;
//                 currNode -> is3Node = true;
//             }
//             return;
//         }
//     }
// }

Node* Tree::searchNode(const string& searchString) const{
    
    Node* currNode = root;
    
    while(true){
        if(currNode -> small == searchString || 
        currNode -> large == searchString){
            return currNode;
        }
        
        if(currNode -> small > searchString){
            if (currNode -> left == 0){
                return 0;
            }
            currNode = currNode -> left;
        }
        
        else if(currNode -> is3Node && currNode -> large > searchString){
            if (currNode -> middle == 0){
                return 0;
            }
            currNode = currNode -> middle;
        }
        
        else{
            if(currNode -> right == 0){
                return 0;
            }
            currNode = currNode -> right;
        }
    }
    
    return 0;
}

bool Tree::search(const string& searchString) const{
    if(searchNode(searchString) != 0){
        return true;
    }
    return false;
}