#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H
#include "../lexer/lexer.hpp"
#include<vector>
using namespace std;
class TokenStream{
    public:
        TokenStream(const vector<Token>& tokens);

        Token next();
        Token peekNext();
        Token peekAhead(int steps);
        Token peek();
        bool isAtEnd();
        void consume();
        bool match(TokenType expectedType);
        bool expect(TokenType expectedType);
    private:
     vector<Token> tokens;
     int position;
};

#endif