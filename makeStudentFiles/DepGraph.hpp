
#ifndef _DepGraph_hpp
#define _DepGraph_hpp

#include<iostream>
#include<cstring>

#include "MakeTree.hpp"
#include "Tokenizer.hpp"


class DepGraph {
public:
    DepGraph( std::string name );
    void print();
    void parseDepGraph();
    void runMake();
    bool isCyclic(){return isCyclic(_tree->getRoot()->graphNode());}

private:
 bool isCyclic(GraphNode *); //helper
 void parseSet(std::vector<Token *> assignmentStatement, int &position);
 void runMakeHelper(GraphNode *pNode);
 void oHelper(GraphNode *oGraphNode);
 void xHelper(GraphNode *xGraphNode);
    bool nothingToRun = true;
    std::string _fileToMake, _targetToMake;
    GraphNode *firstTarget;
    MakeTree *_tree;  // MakeTree implements a binary-search tree similar to BinSearchTree
};

#endif
