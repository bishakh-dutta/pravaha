#ifndef LEXER_LOGIC_H
#define LEXER_LOGIC_H
#include "lexer_logic.h"
using namespace std;
Lexer::Lexer(const string& input) : input(input),position(0),line(1),col(1){
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
        col++;
    }
}
Token Lexer::indentSet(){
    int i=0;
    while(isSpace()==1){
        position++;
        col++;
        i++;
    }
    //checking if comment exist just after newline
    if (input.substr(position, 2) == "//"){
        skipComment();
        return Token(NUL,"",line,col+5);
    }
    // handling useless lines
    if (input.substr(position, 1) == "\n"){
        return Token(NUL,"",line,col+5);
    }
    if(indentLevel.top()<i){
        indentLevel.push(i);
        return Token(INDENT,"INDENT",line,col+5);
    }else if(indentLevel.top()>i){
        indentLevel.pop();
        return Token(DEDENT,"DEDENT",line,col+5);
    }
    return Token(NUL,"",line,col+5);
}
Token Lexer::isString(){
    position++;
    int start=position,end=0;
    while(input[position]!='\"'){
        end++;
        col++;
        position++;
    }
    return Token(STRING,input.substr(start,end),line,col);
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
                col=1;
                line++;
                position++;
                Token indentTok = indentSet();
                if (indentTok.type != NUL) {
                    addToList(indentTok);
                }
            } else {
                col++;
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
                    col++;
                    end++;
                    position++;
                }
                string str = input.substr(start,end);
                if(isKeyword(str)){
                    addToList(Token(KEYWORD,str,line,col));
                }else{
                    addToList(Token(IDENTIFIER,str,line,col));
                }
            }else if(isdigit(input[position])){
                // Number Section
                int start=position,end=1;
                while(isdigit(input[position+1])||input[position+1]=='.'){
                    col++;
                    end++;
                    position++;
                }
                string num = input.substr(start,end);
                if(isDecimal(num)){
                    addToList(Token(FLOAT,num,line,col));
                }else{
                    addToList(Token(INT,num,line,col));
                }
            }else{
                //Operator Section
                if(current=="="){
                    addToList(Token(EQUALS,current,line,col));
                }else{
                    if(current=="\""){
                        addToList(Token(LITERAL,current,line,col));
                        addToList(isString());
                        col++;
                        addToList(Token(LITERAL,current,line,col));
                    }else{
                        addToList(Token(OPERATOR,current,line,col));
                    }
                }
            }
        }
        position++;
        col++;
    }
    return tokenList;
}
#endif