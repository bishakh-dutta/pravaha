#ifndef LEXER_H
#define LEXER_H

#include<string>
#include<vector>
#include<stack>
#include <unordered_set>

using namespace std;

enum TokenType{
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    EQUALS,
    LITERAL,
    INT,
    FLOAT,
    BOOL,
    STRING,
    INDENT,
    DEDENT,
    NUL
};

unordered_set<string> keywords = {
    "if", "else", "for", "while", "return",
    "int", "float","string", "bool", "class", "private",
    "public", "switch", "case", "default", "break",
    "const","print","true","false"
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
        bool isKeyword(string s);
        bool isDecimal(string num);
        Token isString();
        bool checkAlpha();
        void skipComment();
        void addToList(Token);
    private:
        string input;
        int position;
        stack<int> indentLevel;
        vector<Token> tokenList;
};

#endif