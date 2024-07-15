#ifndef LEXER_H
#define LEXER_H

#include<string>
#include<vector>
#include<stack>

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
    STRING,
    INDENT,
    DEDENT,
    NUL
};

struct Token{
    TokenType type;
    string lexeme;
    Token(TokenType type,string lexeme):type(type),lexeme(lexeme){}
};

class Lexer{
    public:
        Lexer(const string& input);
        vector<Token> getTokens();
        string peek();
        bool isSpace();
        bool isNewLine();
        Token indentSet();
        Token isComment();
    private:
        string input;
        int position;
        stack<int> indentLevel;
};
#endif