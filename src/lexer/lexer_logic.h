#ifndef LEXER_LOGIC_H
#define LEXER_LOGIC_H
#include "lexer.h"
using namespace std;
Lexer::Lexer(const string& input) : input(input),position(0){
    indentLevel.push(0);
}
void Lexer::addToList(Token token){
    tokenList.push_back(token);
}
string Lexer::peek(){
    return input.substr(position,1);
}
bool Lexer::isSpace(){
    return peek() == " ";
}
bool Lexer::isNewLine(){
    return input[position] == '\n';
}
void Lexer::skipComment() {
    while (position < input.length() && input[position] != '\n') {
        position++;
    }
}
Token Lexer::indentSet(){
    int i=0;
    while(isSpace()==1){
        position++;
        i++;
    }
    //checking if comment exist just after newline
    if (input.substr(position, 2) == "//"){
        skipComment();
        return Token(NUL,"");
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
Token Lexer::isString(){
    position++;
    int start=position,end=0;
    while(input[position]!='\"'){
        end++;
        position++;
    }
    return Token(STRING,input.substr(start,end));
}
bool Lexer::isKeyword(string s){
    return keywords.find(s) != keywords.end();
}
bool Lexer::isDecimal(string num){
     return num.find('.') != string::npos;
}
bool Lexer::checkAlpha(){
    if(isalpha(input[position+1])||isdigit(input[position+1])||input[position+1]=='_'){
        return true;
    }
    return false;
}
vector<Token> Lexer::getTokens(){
    while(position<input.length()){
        string current = peek();
        if(isSpace()||isNewLine()){
            if (isNewLine()) {
                position++;
                Token indentTok = indentSet();
                if (indentTok.type != NUL) {
                    addToList(indentTok);
                }
            } else {
                position++;
            }
            continue;
        }else if (input.substr(position, 2) == "//") {
            skipComment();
            continue;
        }else{
            if(isalpha(input[position])){
                //Identifier and Keyword section
                int start=position,end=1;
                while(checkAlpha()){
                    end++;
                    position++;
                }
                string str = input.substr(start,end);
                if(isKeyword(str)){
                    addToList(Token(KEYWORD,str));
                }else{
                    addToList(Token(IDENTIFIER,str));
                }
            }else if(isdigit(input[position])){
                // Number Section
                int start=position,end=1;
                while(isdigit(input[position+1])||input[position+1]=='.'){
                    end++;
                    position++;
                }
                string num = input.substr(start,end);
                if(isDecimal(num)){
                    addToList(Token(FLOAT,num));
                }else{
                    addToList(Token(INT,num));
                }
            }else{
                //Operator Section
                if(current=="="){
                    addToList(Token(EQUALS,current));
                }else{
                    if(current=="\""){
                        addToList(Token(LITERAL,current));
                        addToList(isString());
                        addToList(Token(LITERAL,current));
                    }else{
                        addToList(Token(OPERATOR,current));
                    }
                }
            }
        }
        position++;
    }
    return tokenList;
}
#endif