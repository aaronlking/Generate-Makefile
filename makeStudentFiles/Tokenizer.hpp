//
// Created by Ali A. Kooshesh on 10/11/21.
//

#ifndef MAKESTUDENTFILES_TOKENIZER_HPP
#define MAKESTUDENTFILES_TOKENIZER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include "Token.hpp"

class Tokenizer {
public:
    Tokenizer(std::string nameOfInputFileToTokenize);
    Token *getToken();
    
private:
    std::string nameOfInputFile;
    std::fstream _inStream;
};


#endif //MAKESTUDENTFILES_TOKENIZER_HPP
