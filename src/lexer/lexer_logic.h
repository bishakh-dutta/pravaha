#ifndef LEXER_LOGIC_H
#define LEXER_LOGIC_H
#include "lexer.h"
using namespace std;
Lexer::Lexer(const string& input) : input(input),position(0){
    
}
vector<Token> Lexer::getTokens(){
    vector<Token> tokens;
    while(position<input.length()){
        Token t = {KEYWORD,input.substr(position,1)};
        tokens.push_back(t);
        position++;
    }
    return tokens;
}
#endif