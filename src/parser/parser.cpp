#include "parser.hpp"
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

unique_ptr<ASTNode> Parser::parseBinaryOp(){
    if(!tokenStream.match(IDENTIFIER)){
        // throw error
    }
    Token identifer = tokenStream.next();
    unique_ptr<ASTNode> left = make_unique<Literal>(identifer.type,identifer.lexeme);
    string op = tokenStream.next().lexeme;
    unique_ptr<ASTNode> right = parseExpr();
    return make_unique<ExprNode>(op,std::move(left),std::move(right));
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
        unordered_set<string> binaryOp = {"=","+=","-=","*=","/=","==","<","<=",">",">=","and","or"};
        Token next = tokenStream.peekNext();
        if(next.lexeme=="("){
            return parseFncCall();
        }else if(binaryOp.find(next.lexeme) != binaryOp.end()){
            return parseBinaryOp();
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
    if(!tokenStream.match(IDENTIFIER)){
        //throw error
    }
    string identifier = tokenStream.next().lexeme;
    if(!tokenStream.match(EQUALS)&&tokenStream.peek().line==tokenStream.peekNext().line){
        //throw error
    }else{
        tokenStream.consume();
        unique_ptr<ASTNode> expr = parseExpr();
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
// unique_ptr<ASTNode> Parser::parseExprList(){
//     vector<unique_ptr<ASTNode>> exprList;
//     while(!tokenStream.isAtEnd()){
//         exprList.push_back(parseExpr());
//     }
//     return make_unique<ExprListNode>(std::move(exprList));
// }
bool precedence(string op1,string op2){
    char op = op1[0];
    char top = op2[0];

    switch(op){
        case '+':
            if(top=='*'||top=='/'){
                return true;
            }
            return false;
        case '-':
            if(top=='*'||top=='/'){
                return true;
            }
            return false;
        case '/':
            if(top=='*'){
                return true;
            }
            return false;
        default:
            if(top=='/'){
                return true;
            }
            return false;
    }
}
unique_ptr<ASTNode> Parser::parseExpr(){
    int currentLine = tokenStream.peek().line;
    string op;
    if(!tokenStream.match(INT)&&!tokenStream.match(FLOAT)){
        //throw error
    }
    Token literal = tokenStream.next();
    unique_ptr<ASTNode> node = make_unique<Literal>(literal.type,literal.lexeme);
    exprTree.push(std::move(node));
    while(tokenStream.peek().line==currentLine){
        if(!tokenStream.match(OPERATOR)){
            //throw error
        }
        op = tokenStream.next().lexeme;
        if(!tokenStream.match(INT)&&!tokenStream.match(FLOAT)){
            //throw error
        }
        literal = tokenStream.next();
        node = make_unique<Literal>(literal.type,literal.lexeme);
        if(!exprOp.empty()){
            auto top = exprOp.top();
            if(precedence(op,top)){
                if(!exprTree.empty()){
                    auto treeTop1 = std::move(exprTree.top());
                    exprTree.pop();
                    auto treeTop2 = std::move(exprTree.top());
                    exprTree.pop();
                    auto treeOp = exprOp.top();
                    exprOp.pop();
                    unique_ptr<ASTNode> treeNode = make_unique<ExprNode>(treeOp,std::move(treeTop2),std::move(treeTop1));
                    exprTree.push(std::move(treeNode));
                    exprTree.push(std::move(node));
                }
            }else{
                exprTree.push(std::move(node));
            }
        }else{
            exprTree.push(std::move(node));
        }

        exprOp.push(op);
    }
    while (!exprOp.empty()) {
        auto op = exprOp.top();
        exprOp.pop();
        auto treeTop1 = std::move(exprTree.top());
        exprTree.pop();
        auto treeTop2 = std::move(exprTree.top());
        exprTree.pop();
        unique_ptr<ASTNode> treeNode = make_unique<ExprNode>(op,std::move(treeTop2),std::move(treeTop1));
        exprTree.push(std::move(treeNode));
    }
    return std::move(exprTree.top());
}
unique_ptr<ASTNode> Parser::parseLiteral(){
return nullptr;
}
unique_ptr<ASTNode> Parser::parseParams(){
    return nullptr;
}
