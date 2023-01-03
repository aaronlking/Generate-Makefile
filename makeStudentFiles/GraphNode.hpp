#include<iostream>
#include<string>
#include<vector>
#include "systemInterface.hpp"

class GraphNode {
public:
    GraphNode( std::string name ) {_name = name;
    _listOfDependentNodes = new std::vector<GraphNode *>;
    _onPath = _isATarget = _wasMade = false;
    _timestamp = 0;}
    std::string getName() {return _name;} //getter
    void setName( std::string name ) {_name = name;} // setter, don't need to change name
    void setTimestamp(int ts) {_timestamp = ts;} //set timestamp
    int getTimestamp() {return _timestamp;} // get timestamp
    std::vector<GraphNode *> *dependentNodes() {return _listOfDependentNodes;} //refers to the vector of the node
    void setCommand(std::string cmnd) {_command = cmnd;} //when you realize you have the target you put the 
    std::string getCommand() {return _command;} //returns command
    void runCommand() { executeCommand(getCommand().c_str() );}  // execute the command associated with this node. Only for target nodes.
    void addDependentNode(GraphNode *child) {_listOfDependentNodes->push_back(child);} //everytime you read a name, you create a graphnode to the vector. 
    //Building of the graph is called from parser. Parser that calls make tree. parser keeps track of target 
    bool onPath(){return _onPath;} // helps catch loops, cycles in the graph if the graph has cycles
    void onPath(bool v){_onPath = v;} //
    bool wasMade() {return _wasMade;} //yes or no we made this particular target
    void wasMade(bool v) {_wasMade = v;} 
    bool isATarget() { return _isATarget;} //a target has a vector of dependencies
    void isATarget(bool v) {_isATarget = v;}
    int numDependentNodes() {return _listOfDependentNodes->size();} //tells how many elements are in the vector. size check
    void print(){
    std::cout << "Got Name: " << getName() << std::endl;
    std::cout << "Got Command: " << getCommand() << std::endl;
    std::cout << "Dependencies: " << std::endl;
    for(int i = 0; i < _listOfDependentNodes->size(); i++) {
        std::cout << _listOfDependentNodes->at(i)->getName() << std::endl;
    }
}

private:
    std::string _name, _command;
    int _timestamp;
    std::vector<GraphNode *> *_listOfDependentNodes;

    bool _onPath, _isATarget, _wasMade;
};
