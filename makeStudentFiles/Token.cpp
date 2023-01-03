//
// Created by Ali A. Kooshesh on 10/11/21.
//

#include <iostream>
#include "Token.hpp"

void Token::print() {
    if( eol() ) std::cout << "EOL" << std::endl;
    else if( eof())  std::cout << "EOF" << std::endl;
    else if(tab()) std::cout << "Tab" << std::endl;
    else if(colon()) std::cout << ":" << std::endl;
    else if(target()) std::cout << "Target: "<< nameOfFile() <<std::endl;
    else if(command()) std::cout << "Command: "<< nameOfFile() <<std::endl;
    else if(dependency()) std::cout<< "Dependency: " <<nameOfFile() <<std::endl;
    else {
        std::cout << "Token::print -- Came across an unknown token: " << int(_symbol) << " Terminating...\n";
        exit(1);
    }
}

void Token::init() {
    _nameOfFile = "";
    _eof = _eol = _command = _dependency = _colon = _target = _tab = false;
    _symbol = '\0';
}

