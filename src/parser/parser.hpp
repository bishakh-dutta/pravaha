#ifndef PARSER_H
#define PARSER_H
#include "tokenstream/tokenstream.hpp"
#include "ast.hpp"
#include <memory>
#include<unordered_set>

enum ErrorTypes{
    MSG = "Error at",
};

class Parser{
    public:
        Parser(TokenStream& tokenStream);

        string ErrMsg(ErrorTypes err,int line,int col);
        unique_ptr<ASTNode> parseProgram();

    private:
        TokenStream& tokenStream;
        unique_ptr<ASTNode> parseStmtList();
        unique_ptr<ASTNode> parseStmt();
        unique_ptr<ASTNode> parseVarDecl();
        unique_ptr<ASTNode> parseConstDecl();
        unique_ptr<ASTNode> parseFncDecl();
        unique_ptr<ASTNode> parseFncCall();
        unique_ptr<ASTNode> parseIfStmt();
        unique_ptr<ASTNode> parseElsIfStmt();
        unique_ptr<ASTNode> parseElsStmt();
        unique_ptr<ASTNode> parseCndStmt();
        unique_ptr<ASTNode> parseExprList();
        unique_ptr<ASTNode> parseExpr();
        unique_ptr<ASTNode> parseLiteral();
        unique_ptr<ASTNode> parseParams();
        unordered_set<string> dataType = {
            "int","float","string","bool"
        };
};

#endif