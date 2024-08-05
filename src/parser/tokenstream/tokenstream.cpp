#include<string>
#include "tokenstream.hpp"
using namespace std;

const Token NULT(TokenType::NUL,"",0,0);
TokenStream::TokenStream(const vector<Token>& tokens)
:tokens(tokens),position(0){};

bool TokenStream::isAtEnd(){
    return position>=tokens.size();
}

Token TokenStream::next(){
    if(!isAtEnd()){
        return tokens[position++];
    }
    return NULT;
}

Token TokenStream::peekNext(){
    if(!isAtEnd()){
        return tokens[position+1];
    }
    return NULT;
}

Token TokenStream::peek(){
    return tokens[position];
}

Token TokenStream::peekAhead(int steps){
    if(!isAtEnd()){
        return tokens[position+steps];
    }
    return NULT;
}

void TokenStream::consume(){
    if (!isAtEnd()) position++;
}

bool TokenStream::match(TokenType expectedType){
    if(tokens[position].type==expectedType){
        return true;
    }
    return false;
}

bool TokenStream::expect(TokenType expectedType){
    if(tokens[position].type==expectedType){
        return true;
    }
    return false;
}