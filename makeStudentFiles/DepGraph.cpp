#include <iostream>
#include "DepGraph.hpp"
#include "Tokenizer.hpp"


DepGraph::DepGraph(std::string name){
    _fileToMake = name;
}

void DepGraph::print(){
firstTarget->print();
}

void DepGraph::parseDepGraph(){
    //tokenizer
    //if find, get graphnode = find and edit
    //check to see if the name exists in the tree, if not then make graphnode
    //tokenizer, insert bst, GraphNode and 
    //collect tokens and
    //do not want duplicates in BST 
    //create a new graphnode and set all dependencies
    //set command while we parse it

    Tokenizer tokenizer = Tokenizer(_fileToMake);
    std::vector<Token *> assignmentStatement;
    Token *token = tokenizer.getToken();

    //The assumption is that there is at least one new-line character
    //to terminate the last statement before end-of-file gets detected.

    while (!token->eof()) {
       assignmentStatement.push_back(token);
       //token->print();
       token = tokenizer.getToken();
    }
    
    int position = 0;
    _tree = new MakeTree();
    while(!assignmentStatement.at(position)->eof()){
        if( position == assignmentStatement.size()){
            break;
        }
        parseSet(assignmentStatement, position);
        if( position == assignmentStatement.size()){
            break;
        }
    }
}


void DepGraph::parseSet(std::vector<Token *> assignmentStatement, int &position){


    GraphNode *tempNode = new GraphNode(assignmentStatement.at(position)->nameOfFile());
    
    if(position == assignmentStatement.size()){
        return;
    }

    if(assignmentStatement.at(position)->target()){
        if(_tree->getRoot() == nullptr){//tree is empty
        _tree->insert(tempNode);
        }
        else{ //tree has been populated
            if(_tree->find(assignmentStatement.at(position)->nameOfFile()) == nullptr){ //target is in tree already
                _tree->insert(tempNode);
                position++;
                if(position == assignmentStatement.size()){                
                return;
                }            
            }
            else{//target not in tree
                tempNode = _tree->find(assignmentStatement.at(position)->nameOfFile());
                position++;
                if(position == assignmentStatement.size()){            
                return;
                }
            }
        }
        long time;
        timestamp(tempNode->getName().c_str(), &time);
        tempNode->setTimestamp(time);
    }

    if(assignmentStatement.at(position)->colon()){//should be a colon
        position++;
        if(position == assignmentStatement.size()){
            return;
        }
    }
    
    if(assignmentStatement.at(position)->dependency()){
        while (assignmentStatement.at(position)->dependency()){
            GraphNode *dependencyGNode;
            if(_tree->find(assignmentStatement.at(position)->nameOfFile()) == nullptr){//dependency not in tree
                dependencyGNode = new GraphNode(assignmentStatement.at(position)->nameOfFile());
                _tree->insert(dependencyGNode);
                position++;
                if(position == assignmentStatement.size()){
                    return;
                }
                long time;
                timestamp(dependencyGNode->getName().c_str(), &time);
                dependencyGNode->setTimestamp(time);
            }   
            else{//dependency in tree
                dependencyGNode = _tree->find(assignmentStatement.at(position)->nameOfFile());
                position++;
                if(position == assignmentStatement.size()){
                    return;
                }
            }
            tempNode->addDependentNode(dependencyGNode);
        }
    }

    if(assignmentStatement.at(position)->eol()){
        position++;
        if(position == assignmentStatement.size()){
            return;
        }
    }

    if(assignmentStatement.at(position)->tab()){
        position++;
        if(position == assignmentStatement.size()){
            return;
        }
    }

    if(assignmentStatement.at(position)->command()){ //DO I NEED ELSE?
        tempNode->setCommand(assignmentStatement.at(position)->nameOfFile());
        position++;
        if(position == assignmentStatement.size()){
            return;
        }
    }

    if(assignmentStatement.at(position)->eol()){
        position++;
        if(position == assignmentStatement.size()){
            //std::cout<<"line 307: " << std::endl;
            return;
        }
    }

    if(assignmentStatement.at(position)->eof()){
        firstTarget = _tree->getRoot()->graphNode();
    }

}


void DepGraph::runMake(){//looks like is cyclic but with something else
    //should be the same as make
    //this function identifies the targets that are 
    //not up-to-date and runs the commands associated with them.
    //look at all the timestamps. Helper function that sets all the timestamps before running
    //or run in parseDepGraph 
    for(int i = 0; i < _tree->getRoot()->graphNode()->numDependentNodes(); i++)//loop dep of .x which is root
    {
        oHelper(_tree->getRoot()->graphNode()->dependentNodes()->at(i));
    }
    xHelper(_tree->getRoot()->graphNode());

    if(nothingToRun){
        std::cout<< "make: '" << _tree->getRoot()->graphNode()->getName() << "' is up to date." << std::endl;
    }
}

void DepGraph::runMakeHelper(GraphNode *pNode){
//checking timestamps of parent and child. If the child is greater than parent then runCommand
    if(pNode->numDependentNodes() == 0){
        return;
    }

    for(int i = 0; i < pNode->numDependentNodes(); i++ ){
        runMakeHelper(pNode->dependentNodes()->at(i));
        if(pNode->getTimestamp() < pNode->dependentNodes()->at(i)->getTimestamp()){
            pNode->runCommand();
            long time;
            timestamp(pNode->getName().c_str(), &time);
            pNode->setTimestamp(time);

        }
    }
}

void DepGraph::oHelper(GraphNode *oGraphNode){
    if(oGraphNode->numDependentNodes() == 0){
        return;
    }

    for(int i = 0; i < oGraphNode->numDependentNodes(); i++ ){
        oHelper(oGraphNode->dependentNodes()->at(i));
        if(oGraphNode->getTimestamp() < oGraphNode->dependentNodes()->at(i)->getTimestamp()){
            oGraphNode->runCommand();
            nothingToRun = false;
            long time;
            timestamp(oGraphNode->getName().c_str(), &time);
            oGraphNode->setTimestamp(time);

        }
    }
}

void DepGraph::xHelper(GraphNode *xGraphNode){
    if(xGraphNode->numDependentNodes() == 0){
            return;
        }

        for(int i = 0; i < xGraphNode->numDependentNodes(); i++ ){
            if(xGraphNode->getTimestamp() < xGraphNode->dependentNodes()->at(i)->getTimestamp()){
                xGraphNode->runCommand();
                nothingToRun = false;
                long time;
                timestamp(xGraphNode->getName().c_str(), &time);
                xGraphNode->setTimestamp(time);

            }
        }
}



bool DepGraph::isCyclic(GraphNode * cNode){
    
    if(cNode == nullptr){
        return false;
    }

    if(cNode->onPath()){
        return true;
    }

    cNode->onPath(true);

    for (int i = 0; i < cNode->numDependentNodes(); i++){
        bool checker = isCyclic(cNode->dependentNodes()->at(i));
        if(checker == true){
            return true;
        }
    }
    cNode->onPath(false);
    
return false;
}
