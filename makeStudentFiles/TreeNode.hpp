
#ifndef _TreeNode_hpp
#define _TreeNode_hpp

#include<iostream>
#include<string>
#include "GraphNode.hpp"

//This is our BST that stores pointers to GraphNodes

class TreeNode {
public:
    TreeNode( GraphNode *nNode ): leftSubtree(nullptr), rightSubtree(nullptr), makeNode(nNode) {}

    TreeNode *left() {return leftSubtree; }
    void left( TreeNode *leftPtr ) { leftSubtree = leftPtr; }
    TreeNode *right() {return rightSubtree; }
    void right( TreeNode *rightPtr ) { rightSubtree = rightPtr; }
    void print() {makeNode->print();}
    GraphNode *graphNode() {return makeNode;}

private:
    GraphNode *makeNode;
    TreeNode *leftSubtree, *rightSubtree;
};

#endif
