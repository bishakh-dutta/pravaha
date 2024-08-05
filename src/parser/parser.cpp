#include "parser.hpp"
using namespace std;

Parser::Parser(TokenStream& tokenStream)
:tokenStream(tokenStream){};

string Parser::ErrMsg(ErrorTypes err,int line,int col){
    string errMsg = err + " at Line: "+line+"Col: "+col;
    return errMsg;
}

unique_ptr<ASTNode> Parser::parseProgram(){
    return parseStmtList();
}

unique_ptr<ASTNode> Parser::parseStmtList(){
    vector<unique_ptr<ASTNode>> stmtList;
    while(!tokenStream.isAtEnd()){
        stmtList.push_back(parseStmt());
    }
    return make_unique<stmtList>();
}

unique_ptr<ASTNode> Parser::parseStmt(){
    Token current = tokenStream.peek();
    if(dataType.find(current.lexeme) != dataType.end()){
        Token next = tokenStream.peekAhead(2);
        switch(next.lexeme){
            case "=":
                return make_unique<parseVarDecl>();
            case "(":
                return make_unique<parseFncDecl>();
            default:
                if(next.line==tokenStream.peekAhead(3).line){
                    //throw error
                    break;
                }
                return make_unique<parseVarDecl>();
        }
    }else if(current.type==IDENTIFIER){
        Token next = tokenStream.peekAhead(2);
        if(next.lexeme=="("){
            return make_unique<parseFncCall>();
        }else if(next.lexeme=="="){
            return make_unique<parseExprList>();
        }
        //throw error
    }else if(current.lexeme=="const"){
        return make_unique<parseConstDecl>();
    }else if(current.lexeme=="if"){
        return make_unique<parseCndStmt>();
    }
    //throw error
}

unique_ptr<ASTNode> Parser::parseVarDecl(){}
unique_ptr<ASTNode> Parser::parseConstDecl(){}
unique_ptr<ASTNode> Parser::parseFncDecl(){}
unique_ptr<ASTNode> Parser::parseFncCall(){}
unique_ptr<ASTNode> Parser::parseIfStmt(){}
unique_ptr<ASTNode> Parser::parseElsIfStmt(){}
unique_ptr<ASTNode> Parser::parseElsStmt(){}
unique_ptr<ASTNode> Parser::parseCndStmt(){}
unique_ptr<ASTNode> Parser::parseExprList(){}
unique_ptr<ASTNode> Parser::parseExpr(){}
unique_ptr<ASTNode> Parser::parseLiteral(){}
unique_ptr<ASTNode> Parser::parseParams(){}
