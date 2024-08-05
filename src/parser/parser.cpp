#include "parser.hpp"
#include<iostream>
using namespace std;

Parser::Parser(TokenStream& tokenStream)
:tokenStream(tokenStream){};


unique_ptr<ASTNode> Parser::parseProgram(){
    return parseStmtList();
}

unique_ptr<ASTNode> Parser::parseStmtList(){
    vector<unique_ptr<ASTNode>> stmtList;
    while(!tokenStream.isAtEnd()){
        stmtList.push_back(parseStmt());
    }
    return make_unique<StmtList>(std::move(stmtList));
}

unique_ptr<ASTNode> Parser::parseStmt(){
    Token current = tokenStream.peek();
    if(dataType.find(current.lexeme) != dataType.end()){
        Token next = tokenStream.peekAhead(2);

        if(next.lexeme=="="){
                return parseVarDecl();
        }else if(next.lexeme=="("){
                return parseFncDecl();
        }else{
            if(tokenStream.peek().line==tokenStream.peekAhead(2).line){
                //throw error
            }
            return parseVarDecl();
        }
    }else if(current.type==IDENTIFIER){
        Token next = tokenStream.peekAhead(2);
        if(next.lexeme=="("){
            return parseFncCall();
        }else if(next.lexeme=="="){
            return parseExprList();
        }
        //throw error
    }else if(current.lexeme=="const"){
        return parseConstDecl();
    }else if(current.lexeme=="if"){
        return parseCndStmt();
    }
    //throw error
    return nullptr;
}

unique_ptr<ASTNode> Parser::parseVarDecl(){
    string type = tokenStream.next().lexeme;
    if(!tokenStream.expect(IDENTIFIER)){
        //throw error
    }
    string identifier = tokenStream.next().lexeme;
    if(!tokenStream.expect(EQUALS)&&tokenStream.peek().line==tokenStream.peekNext().line){
        //throw error
    }else{
        unique_ptr<ASTNode> expr = parseExprList();
        return make_unique<VariableDeclNode>(type,identifier,std::move(expr));
    }
    return make_unique<VariableDeclNode>(type,identifier);
}
unique_ptr<ASTNode> Parser::parseConstDecl(){
return nullptr;
}
unique_ptr<ASTNode> Parser::parseFncDecl(){
return nullptr;
}
unique_ptr<ASTNode> Parser::parseFncCall(){
return nullptr;
}
unique_ptr<ASTNode> Parser::parseIfStmt(){
return nullptr;
}
unique_ptr<ASTNode> Parser::parseElsIfStmt(){
return nullptr;
}
unique_ptr<ASTNode> Parser::parseElsStmt(){
return nullptr;
}
unique_ptr<ASTNode> Parser::parseCndStmt(){
return nullptr;
}
unique_ptr<ASTNode> Parser::parseExprList(){
return make_unique<TestNode>();
}
unique_ptr<ASTNode> Parser::parseExpr(){
return nullptr;
}
unique_ptr<ASTNode> Parser::parseLiteral(){
return nullptr;
}
unique_ptr<ASTNode> Parser::parseParams(){
    return nullptr;
}
