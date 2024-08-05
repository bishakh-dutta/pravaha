#ifndef AST_H
#define AST_H
#include <string>
#include <vector>
#include <memory>
using namespace std;

class ASTNode{
    public:
        virtual ~ASTNode() = default;
};

class ProgramNode : public ASTNode{
    public:
        ProgramNode(const unique_ptr<ASTNode> stmtList)
        :stmltList(stmtList){};
        unique_ptr<ASTNode> stmtList;
};

class StmtList : public ASTNode{
    public:
        StmtList(const vector<unique_ptr<ASTNode>> statements)
        :statements(statements){};
        vector<unique_ptr<ASTNode>> statements;
};

class VariableDeclNode : public ASTNode{
    public:
        VariableDeclNode(const string type,const string indentifier,const unique_ptr<ASTNode> expr)
        :type(type),indentifier(indentifier),expr(expr){};
        string type,indentifier;
        unique_ptr<ASTNode> expr;
};

class ConstDeclNode : public ASTNode{
    public:
        ConstDeclNode(const unique_ptr<ASTNode> declNode)
        :declNode(declNode){};
        string type = "const";
        unique_ptr<ASTNode> declNode;
};

class FunctionDeclNode : public ASTNode{
    public:
        FunctionDeclNode(const string type,const string identifier, const vector<unique_ptr<ASTNode>> paramList,const vector<unique_ptr<ASTNode>>functionBody)
        :type(type),identifier(identifier),paramList(paramList),functionBody(functionBody){};
        string type;
        string identifier;
        vector<unique_ptr<ASTNode>> paramList;
        vector<unique_ptr<ASTNode>> functionBody;
};

class FunctionCallNode : public ASTNode{
    public:
        FunctionCallNode(const string identifier,const vector<unique_ptr<ASTNode>> argList)
        :identifier(identifier),argList(argList){};
        string identifier;
        vector<unique_ptr<ASTNode>> argList;
};

class IfStmtNode : public ASTNode{
    public:
        IfStmtNode(const vector<unique_ptr<ASTNode>> expr,const vector<unique_ptr<ASTNode>> ifblock)
        :expr(expr),ifblock(ifblock){};
        vector<unique_ptr<ASTNode>> expr;
        vector<unique_ptr<ASTNode>> ifblock;
};

class ElsIfStmtNode : public ASTNode{
    public:
        ElsIfStmtNode(const vector<unique_ptr<ASTNode>> expr,const vector<unique_ptr<ASTNode>> elsifblock)
        :expr(expr),elsifblock(elsifblock){};
        vector<unique_ptr<ASTNode>> expr;
        vector<unique_ptr<ASTNode>> elsifblock;
};

class elseStmtNode : public ASTNode{
    public:
        elseStmtNode(const vector<unique_ptr<ASTNode>> elseblock)
        :elseblock(elseblock){};
        vector<unique_ptr<ASTNode>> elseblock;
};

class ConditionNode : public ASTNode{
    public:
        ConditionNode(const unique_ptr<ASTNode> ifBlock,const vector<unique_ptr<ASTNode>> elsIfBlockList,const unique_ptr<ASTNode> elseBlock)
        :ifBlock(ifBlock),elsIfBlockList(elsIfBlockList),elseBlock(elseBlock){};
        unique_ptr<ASTNode> ifBlock;
        vector<unique_ptr<ASTNode>> elsIfBlockList;
        unique_ptr<ASTNode> elseBlock;
};

class ExprListNode : public ASTNode{
    public:
        ExprListNode(const vector<unique_ptr<ASTNode>> exprList)
        :exprList(exprList){};
        vector<unique_ptr<ASTNode>> exprList;
};

class ExprNode : public ASTNode{
    public:
        ExprNode(const string type,const unique_ptr<ASTNode> left, const unique_ptr<ASTNode> right)
        :type(type),left(left),right(right){};
        string type;
        unique_ptr<ASTNode> left;
        unique_ptr<ASTNode> right;
};

class Literal : public ASTNode{
    public:
        Literal(const string type,const auto value)
        :type(type),value(value){};
        string type;
        auto value;
};

#endif