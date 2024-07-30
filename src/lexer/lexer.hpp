#ifndef LEXER_H
#define LEXER_H

#include<string>
#include<vector>
#include<stack>
#include<unordered_set>


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

struct Token{
    TokenType type;
    string lexeme;
    int line,column;
    Token(TokenType type,string lexeme,int line,int column)
    :type(type),lexeme(lexeme),line(line),column(column-(lexeme.length()-1)){}
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
        int line;
        int col;
        stack<int> indentLevel;
        vector<Token> tokenList;
        unordered_set<string> keywords = {
        "if", "else","elif", "for", "while", "return",
        "int", "float","string", "bool", "class", "private",
        "public", "switch", "case", "default", "break",
        "const","print","true","false","or","and","not","noteq"
        };
};

#endif