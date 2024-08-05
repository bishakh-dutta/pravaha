#include<string>
#include "tokenstream.hpp"
using namespace std;

const Token NUL(TokenType::NUL,"",0,0);
TokenStream::TokenStream(const vector<Token>& tokens)
:tokens(tokens),position(0){};

bool TokenStream::isAtEnd(){
    return position>=tokens.size();
}

Token TokenStream::next(){
    if(!isAtEnd()){
        position++;
        return tokens.at(position);
    }
    return NUL;
}

Token TokenStream::peekNext(){
    if(!isAtEnd()){
        return tokens.at(position+1);
    }
    return NUL;
}

Token TokenStream::peek(){
    return tokens.at(position);
}

Token TokenStream::peekAhead(int steps){
    if(!isAtEnd()){
        return tokens.at(position+steps);
    }
    return NUL;
}

void TokenStream::consume(){
    if !isAtEnd() position++;
}

bool TokenStream::match(TokenType expectedType){
    if(tokens.at(position).type==expectedType){
        return true;
    }
    return false;
}

bool TokenStream::expect(TokenType expectedType){
    consume();
    if(tokens.at(position).type==expectedType){
        return true;
    }
    return false;
}