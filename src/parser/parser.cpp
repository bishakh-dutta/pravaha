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

// main parse statement
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
        unordered_set<string> binaryOp = {"=","+=","-=","*=","/="};
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


// parsing variable declaration
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

// parse any block with this
vector<unique_ptr<ASTNode>> Parser::parseBlock(){
    vector<unique_ptr<ASTNode>> block;
    int level = 0;
    while(!tokenStream.isAtEnd()){
        if(tokenStream.peek().lexeme=="INDENT"){
            level++;
            tokenStream.consume();
        }
        if(tokenStream.peek().lexeme=="DEDENT"){
            level--;
            tokenStream.consume();
            if(level==0) break;
        }
        block.push_back(parseStmt());
    }
    return block;
}

// parse function declaration
unique_ptr<ASTNode> Parser::parseFncDecl(){

    string type = tokenStream.next().lexeme;
    int paramFlag = 0;
    if(!tokenStream.match(IDENTIFIER)){
        // throw err
    }
    string identifier = tokenStream.next().lexeme;
    tokenStream.consume();
    vector<unique_ptr<ASTNode>> paramList;
    vector<unique_ptr<ASTNode>> fnBlock;
    Token current = tokenStream.peek();
    if(dataType.find(current.lexeme) != dataType.end()){
        paramFlag=1;
        paramList = parseParams();
    }
    if(tokenStream.peek().lexeme==")"){
        tokenStream.consume();
        fnBlock = parseBlock();
    }else{
        // throw err
    }
    if(paramFlag==1) return make_unique<FunctionDeclNode>(type,identifier,std::move(paramList),std::move(fnBlock));
    return make_unique<FunctionDeclNode>(type,identifier,std::move(fnBlock));
}

unique_ptr<ASTNode> Parser::parseFncCall(){
    vector<unique_ptr<ASTNode>> argList;
    string identifier = tokenStream.next().lexeme;
    tokenStream.consume();
    if(tokenStream.peek().lexeme!=")"){
        argList = parseArgList();
        tokenStream.consume();
        return make_unique<FunctionCallNode>(identifier,std::move(argList));
    }
    tokenStream.consume();
    return make_unique<FunctionCallNode>(identifier);
}

// parse if block
unique_ptr<ASTNode> Parser::parseIfStmt(){
    tokenStream.consume();
    if(tokenStream.peek().lexeme!="("){
        // throw error
    }
    tokenStream.consume();
    unique_ptr<ASTNode> cndList = parseCndExpr();
    vector<unique_ptr<ASTNode>> ifBlock = parseBlock();
    return make_unique<IfStmtNode>(std::move(cndList),std::move(ifBlock));
}

// parse ElseIF block
unique_ptr<ASTNode> Parser::parseElsIfStmt(){
    if(tokenStream.peek().lexeme!="("){
        // throw error
    }
    tokenStream.consume();
    unique_ptr<ASTNode> cndList = parseCndExpr();
    vector<unique_ptr<ASTNode>> elsIfBlock = parseBlock();
    return make_unique<ElsIfStmtNode>(std::move(cndList),std::move(elsIfBlock));
}

// parse Else block
unique_ptr<ASTNode> Parser::parseElsStmt(){
    vector<unique_ptr<ASTNode>> elsBlock = parseBlock();
    return make_unique<ElseStmtNode>(std::move(elsBlock));
}

// Wrapper for conditional statement
unique_ptr<ASTNode> Parser::parseCndStmt(){
    bool elsIf = false,els = false;
    unique_ptr<ASTNode> ifStmt = parseIfStmt();
    unique_ptr<ASTNode> elsStmt;
    vector<unique_ptr<ASTNode>> elsIfList;
    while(tokenStream.peek().lexeme=="elif"){
        tokenStream.consume();
        elsIfList.push_back(parseElsIfStmt());
        elsIf = true;
    }
    if(tokenStream.peek().lexeme=="else"){
        tokenStream.consume();
        elsStmt = parseElsStmt();
        els = true;
    }
    if(elsIf&&els){
        return make_unique<ConditionNode>(std::move(ifStmt),std::move(elsIfList),std::move(elsStmt));
    }else if(elsIf){
        return make_unique<ConditionNode>(std::move(ifStmt),std::move(elsIfList));
    }else if(els){
        return make_unique<ConditionNode>(std::move(ifStmt),std::move(elsStmt));
    }
    return make_unique<ConditionNode>(std::move(ifStmt));
}
// unique_ptr<ASTNode> Parser::parseExprList(){
//     vector<unique_ptr<ASTNode>> exprList;
//     while(!tokenStream.isAtEnd()){
//         exprList.push_back(parseExpr());
//     }
//     return make_unique<ExprListNode>(std::move(exprList));
// }


// check precedence for condtional operators
bool cndPrecedence(string op1,string op2){
    if(op1=="or"){
        if(op2!="or") return true;
    }else if(op1=="and"){
        if(op2!="or"&&op2!="and") return true;
    }else if(op1=="noteq"){
        if(op2!="and"&&op2!="or") return true;
    }else if(op1=="=="){
        if(op2!="noteq"&&op2!="and"&&op2!="or") return true;
    }else if(op1==">="){
        if(op2==">"||op2=="<="||op2=="<"||op2=="not") return true;
    }else if(op1==">"){
        if(op2=="<="||op2=="<"||op2=="not") return true;
    }else if(op1=="<="){
        if(op2=="<"||op2=="not") return true;
    }else if(op1=="<"){
        if(op2=="not") return true;
    }
    return false;
}


// check precedence for expression operator
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

// parsing condition block
unique_ptr<ASTNode> Parser::parseCndExpr(){
    // not isn't implemented yet
    // will do it later
    int currentLine = tokenStream.peek().line;
    string op;
    if(!tokenStream.match(IDENTIFIER)&&tokenStream.peek().lexeme!="not"){
        //throw error
    }
    // if(tokenStream.peek().lexeme=="not"){
    //     exprOp.push(tokenStream.next().lexeme);
    // }
    Token literal = tokenStream.next();
    unique_ptr<ASTNode> node = make_unique<Literal>(literal.type,literal.lexeme);
    exprTree.push(std::move(node));
    while(tokenStream.peek().line==currentLine){
        if(tokenStream.peekNext().line!=currentLine&&tokenStream.peek().lexeme==")"){
            tokenStream.consume();
            break;
        }else{
            // throw error
        }
        if(!tokenStream.match(OPERATOR)){
            // throw error
        }
        op = tokenStream.next().lexeme;
        // if(tokenStream.peek().lexeme=="not"){
            
        // }
        if(!tokenStream.match(IDENTIFIER)){
            // throw error
        }
        literal = tokenStream.next();
        node = make_unique<Literal>(literal.type,literal.lexeme);
        if(!exprOp.empty()){
            auto top = exprOp.top();
            if(cndPrecedence(op,top)){
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


// parsing variable assignments
unique_ptr<ASTNode> Parser::parseExpr(){
    int currentLine = tokenStream.peek().line;
    string op;
    if(!tokenStream.match(INT)&&!tokenStream.match(FLOAT)&&!tokenStream.match(IDENTIFIER)){
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

// parsing function parameters
vector<unique_ptr<ASTNode>> Parser::parseParams(){
    vector<unique_ptr<ASTNode>> paramList;
    while(!tokenStream.isAtEnd()){
        Token current = tokenStream.peek();
        if(!(dataType.find(current.lexeme) != dataType.end())){
            // throw error
        }
        string type = tokenStream.next().lexeme;
        if(tokenStream.match(IDENTIFIER)){
            // throw error
        }
        string identifier = tokenStream.next().lexeme;
        if(tokenStream.peek().lexeme==","){
            tokenStream.consume();
        }
        paramList.push_back(make_unique<ParamNode>(type,identifier));
        if(tokenStream.peek().lexeme==")"){
            break;
        }
    }
    return paramList;
}

vector<unique_ptr<ASTNode>> Parser::parseArgList(){
    vector<unique_ptr<ASTNode>> argList;
    while(!tokenStream.isAtEnd()){
        if(tokenStream.match(IDENTIFIER)){
            // throw error
        }
        string identifier = tokenStream.next().lexeme;
        if(tokenStream.peek().lexeme==","){
            tokenStream.consume();
        }
        argList.push_back(make_unique<ArgNode>(identifier));
        if(tokenStream.peek().lexeme==")"){
            break;
        }
    }
    return argList;
}