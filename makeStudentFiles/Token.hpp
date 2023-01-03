//
// Created by Ali A. Kooshesh on 10/11/21.
//

#ifndef MAKESTUDENTFILES_TOKEN_HPP
#define MAKESTUDENTFILES_TOKEN_HPP

#include <vector>
#include <string>

/*

    This class represent the notion of a token; the building blocks of
    Roman expressions. In this context, a token either represents an
            operator (the addition, subtraction, multiplication, division, or
    modulo arithmetic operators), open or close parentheses, a variable, or a Roman
    number.

    To create a token, you pass an argument to it that characterizes the token.
    For example, to create a token to represent the addition operator, you would do:

    Token *tok = new Token('+'); // create a token to represent the addition op.

    However, for certain tokens, (eof, eol, variable) you will have to create a token
    first and set it later.

    Token *tok = new Token();  // an uninitialized token
    tok->eof(true);            // make it represent EOF token.

*/


class Token {

public:
    Token() { init(); }
    Token(char c) { init(); _symbol = c; }

    std::string nameOfFile() const     { return _nameOfFile; }
    void nameOfFile(const std::string &str ) { _nameOfFile = str; }
    
    bool &eof()  { return _eof; }
    bool &eol()  { return _eol; }
    bool &tab()  { return _tab; }
    bool &colon() {return _colon; }
    bool &command() {return _command; }
    bool &target() {return _target; }
    bool &dependency() {return _dependency; }

    char &variable()              { return _symbol; }

    void print();

private:
    void init();
    std::string _nameOfFile;
    bool _eof, _eol,_command, _dependency, _tab, _colon, _target;
    char _symbol;
};

#endif //MAKESTUDENTFILES_TOKEN_HPP
