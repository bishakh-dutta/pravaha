#ifndef LEXER_H
#define LEXER_H

#include<string>
#include<vector>
using namespace std;

enum TokenType{
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    LITERAL,
    EQUALS,
    INT,
    FLOAT,
    BOOL,
    CHAR,
    STRING
};

struct Token{
    TokenType type;
    string lexeme;
};

class Lexer{
    public:
        Lexer(const string& input);
        vector<Token> getTokens();
        Token peek();
        Token isSpace();
        Token isComment();
    private:
        string input;
        int position;
};
#endif