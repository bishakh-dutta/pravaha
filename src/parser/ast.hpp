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

class TestNode : public ASTNode{
    public:
        TestNode(){};
};

class ProgramNode : public ASTNode{
    public:
        ProgramNode(unique_ptr<ASTNode> stmtList)
        :stmtList(std::move(stmtList)){};
    private:
        unique_ptr<ASTNode> stmtList;
};

class StmtList : public ASTNode{
    public:
        StmtList(vector<unique_ptr<ASTNode>> statements)
        :statements(std::move(statements)){};
        vector<unique_ptr<ASTNode>> statements;
};

class VariableDeclNode : public ASTNode{
    public:
        VariableDeclNode(const string type,const string indentifier,unique_ptr<ASTNode> expr)
        :type(type),indentifier(indentifier),expr(std::move(expr)){};
        VariableDeclNode(const string type,const string indentifier)
        :type(type),indentifier(indentifier){};
        string getIdentifier(){
            return this->indentifier;
        };
    private:
        string type,indentifier;
        unique_ptr<ASTNode> expr;
};

class ConstDeclNode : public ASTNode{
    public:
        ConstDeclNode(unique_ptr<ASTNode> declNode)
        :declNode(std::move(declNode)){};
    private:
        string type = "const";
        unique_ptr<ASTNode> declNode;
};

class FunctionDeclNode : public ASTNode{
    public:
        FunctionDeclNode(const string type,const string identifier,vector<unique_ptr<ASTNode>> paramList,vector<unique_ptr<ASTNode>>functionBody)
        :type(type),identifier(identifier),paramList(std::move(paramList)),functionBody(std::move(functionBody)){};
    private:
        string type;
        string identifier;
        vector<unique_ptr<ASTNode>> paramList;
        vector<unique_ptr<ASTNode>> functionBody;
};

class FunctionCallNode : public ASTNode{
    public:
        FunctionCallNode(const string identifier,vector<unique_ptr<ASTNode>> argList)
        :identifier(identifier),argList(std::move(argList)){};
    private:
        string identifier;
        vector<unique_ptr<ASTNode>> argList;
};

class IfStmtNode : public ASTNode{
    public:
        IfStmtNode(vector<unique_ptr<ASTNode>> expr,vector<unique_ptr<ASTNode>> ifblock)
        :expr(std::move(expr)),ifblock(std::move(ifblock)){};
    private:
        vector<unique_ptr<ASTNode>> expr;
        vector<unique_ptr<ASTNode>> ifblock;
};

class ElsIfStmtNode : public ASTNode{
    public:
        ElsIfStmtNode(vector<unique_ptr<ASTNode>> expr,vector<unique_ptr<ASTNode>> elsifblock)
        :expr(std::move(expr)),elsifblock(std::move(elsifblock)){};
    private:
        vector<unique_ptr<ASTNode>> expr;
        vector<unique_ptr<ASTNode>> elsifblock;
};

class elseStmtNode : public ASTNode{
    public:
        elseStmtNode(vector<unique_ptr<ASTNode>> elseblock)
        :elseblock(std::move(elseblock)){};
    private:
        vector<unique_ptr<ASTNode>> elseblock;
};

class ConditionNode : public ASTNode{
    public:
        ConditionNode(unique_ptr<ASTNode> ifBlock,vector<unique_ptr<ASTNode>> elsIfBlockList,unique_ptr<ASTNode> elseBlock)
        :ifBlock(std::move(ifBlock)),elsIfBlockList(std::move(elsIfBlockList)),elseBlock(std::move(elseBlock)){};
    private:
        unique_ptr<ASTNode> ifBlock;
        vector<unique_ptr<ASTNode>> elsIfBlockList;
        unique_ptr<ASTNode> elseBlock;
};

class ExprListNode : public ASTNode{
    public:
        ExprListNode(vector<unique_ptr<ASTNode>> exprList)
        :exprList(std::move(exprList)){};
        vector<unique_ptr<ASTNode>> exprList;
};

class ExprNode : public ASTNode{
    public:
        ExprNode(const string type,unique_ptr<ASTNode> left,unique_ptr<ASTNode> right)
        :type(type),left(std::move(left)),right(std::move(right)){};
    private:
        string type;
        unique_ptr<ASTNode> left;
        unique_ptr<ASTNode> right;
};

// class Literal : public ASTNode{
//     public:
//         Literal(const string type,const auto value)
//         :type(type),value(value){};
//     private:
//         string type;
//         auto value;
// };

#endif