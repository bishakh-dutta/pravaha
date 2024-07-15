#ifndef LEXER_LOGIC_H
#define LEXER_LOGIC_H
#include "lexer.h"
using namespace std;
Lexer::Lexer(const string& input) : input(input),position(0){
    indentLevel.push(0);
}
string Lexer::peek(){
    return input.substr(position,1);
}
bool Lexer::isSpace(){
    if(!string(" ").compare(peek())){
        return true;
    }
    return false;
}
bool Lexer::isNewLine(){
    if(input[position]=='\n'){
        return true;
    }
    return false;
}
Token Lexer::indentSet(){
    int i=0;
    while(isSpace()==1){
        position++;
        i++;
    }
    if(indentLevel.top()<i){
        indentLevel.push(i);
        return Token(INDENT,"INDENT");
    }else if(indentLevel.top()>i){
        indentLevel.pop();
        return Token(DEDENT,"DEDENT");
    }
    return Token(NUL,"");
}
vector<Token> Lexer::getTokens(){
    vector<Token> tokenList;
    while(position<input.length()){
        if(isSpace()==1){
            position++;
            continue;
        }else if(isNewLine()==1){
            position++;
            Token indentTok = indentSet();
            if(indentTok.type!=NUL){
                tokenList.push_back(indentTok);
            }
            continue;
        }
        Token token(KEYWORD,peek());
        tokenList.push_back(token);
        position++;
    }
    return tokenList;
}
#endif