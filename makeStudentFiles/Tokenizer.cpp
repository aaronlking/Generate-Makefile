//
// Created by Ali A. Kooshesh on 10/11/21.
//

#include "Tokenizer.hpp"
#include <iostream>


Tokenizer::Tokenizer(std::string nameOfInputFileToTokenize): nameOfInputFile{nameOfInputFileToTokenize} {
    std::ifstream file(nameOfInputFileToTokenize);
    _inStream.open(nameOfInputFile, std::ios::in);
    if (!_inStream.is_open()) {
        std::cout << "Unable to open " << nameOfInputFile << ". Terminating...";
        exit(1);
    }
}

Token *Tokenizer::getToken(){
Token *token = new Token();
    
char c;
while ( _inStream.get(c) && c != '\n' && c == ' ' );

    if(c == '\t'){
        std::string tokenTemp;
        while(_inStream.get(c) && c!= '\n'){
        tokenTemp += c;
        }
        token->command() = true;
        token->nameOfFile(tokenTemp);
    
        return token;
    }         
    else if(_inStream.eof()) { //if the token is EOF
        token->eof() = true;
    }
    else if(c == '\n') { //if token is newline
        token->eol() = true; 
    }
    else if(c == ':'){
        token->colon() = true;
        token->variable() = c;
    }
    else if(!(c == ':')&& !(c == '\n') && !isspace(c)){ //not a tab or new line means everything
        std::string tokenTemp;
        while(!isspace(c) && c != '\n' && c != ':'){ //can't be a whitespace
            
            tokenTemp += c;
            _inStream.get(c);
            
       }
       if(c == ':'){//if we find a colon then we have finished a target
             token->target() = true;
             token->nameOfFile(tokenTemp);
        }
        else{
        token->dependency() = true;
        token->nameOfFile(tokenTemp);
        }
        _inStream.putback(c);
    }
    else {
        std::cout << "Encountered an unknown character ->" << c << "<- in getToken. Terminating...";
        exit(1);
    }
    return token;
    }