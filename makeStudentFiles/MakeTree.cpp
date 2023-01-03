#include <iostream>
#include "MakeTree.hpp"


MakeTree::MakeTree() { 
    _root = nullptr;
}

GraphNode *MakeTree::find(std::string name){
    
    TreeNode *temp = _root;

    while(temp != nullptr) {
        if (temp->graphNode()->getName() == name)
            return temp->graphNode();
        else if(name < temp->graphNode()->getName()) {
            temp = temp->left();
        }
        else
        {
            temp = temp->right();
        }

    }
    return nullptr;
};

TreeNode *MakeTree::insert(TreeNode *tNode, GraphNode *nNode){
if(tNode == nullptr){
    return new TreeNode(nNode); //create a new Node
}

if(tNode->graphNode()->getName() > nNode->getName()){
    tNode->left(insert(tNode->left(),nNode));
    }
else if(tNode->graphNode()->getName() < nNode->getName())
    {
    tNode->right(insert(tNode->right(),nNode));
    }
    return tNode;
}

void MakeTree::print(TreeNode *root){
    if(root == nullptr)
        return;
    print(root->left());
    root->print();
    std::cout << std::endl;
    print(root->right());
}

