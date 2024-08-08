#ifndef AST_H
#define AST_H
#include <string>
#include <vector>
#include <memory>
#include<iostream>
using namespace std;

class ASTNode{
    public:
        virtual ~ASTNode() = default;
        virtual void print() const = 0;
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
        void print() const override{
            for (const auto& stmt : statements) {
                cout<<endl;
                if (stmt) stmt->print();
            }
        };
};

class ExprNode : public ASTNode{
    public:
        ExprNode(const string type,unique_ptr<ASTNode> left,unique_ptr<ASTNode> right)
        :type(type),left(std::move(left)),right(std::move(right)){};
        // string getType(){
        //     return type;
        // };
        // unique_ptr<ASTNode> getLeft(){
        //     return std::move(left);
        // };
        // unique_ptr<ASTNode> getRight(){
        //     return std::move(right);
        // };
        void print() const override {
            std::cout << "ExprNode {\n";
            std::cout << "op: '" << type << "',\n";
            std::cout << "left: ";
            if (left) left->print();
            std::cout << "right: ";
            if (right) right->print();
            std::cout << "}\n";
        }
    private:
        string type;
        unique_ptr<ASTNode> left;
        unique_ptr<ASTNode> right;
};

class VariableDeclNode : public ASTNode{
    public:
        VariableDeclNode(const string type,const string identifier,unique_ptr<ASTNode> expr)
        :type(type),identifier(identifier),expr(std::move(expr)){};
        VariableDeclNode(const string type,const string identifier)
        :type(type),identifier(identifier){};
        // string getType(){
        //     return this->type;
        // };
        // string getIdentifier(){
        //     return this->indentifier;
        // };
        // unique_ptr<ASTNode> getExpr(){
        //     return std::move(expr);
        // };
        void print() const override {
            std::cout << "VariableDeclNode {\n";
            std::cout << "type: \"" << type << "\",\n";
            std::cout << "identifier: \"" << identifier << "\",\n";
            std::cout << "expr: ";
            if (expr) expr->print();
            std::cout << "}\n";
        }
    private:
        string type,identifier;
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
        IfStmtNode(unique_ptr<ASTNode> expr,vector<unique_ptr<ASTNode>> ifblock)
        :expr(std::move(expr)),ifblock(std::move(ifblock)){};
    private:
        unique_ptr<ASTNode> expr;
        vector<unique_ptr<ASTNode>> ifblock;
};

class ElsIfStmtNode : public ASTNode{
    public:
        ElsIfStmtNode(unique_ptr<ASTNode> expr,vector<unique_ptr<ASTNode>> elsifblock)
        :expr(std::move(expr)),elsifblock(std::move(elsifblock)){};
    private:
        unique_ptr<ASTNode> expr;
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

// class ExprListNode : public ASTNode{
//     public:
//         ExprListNode(vector<unique_ptr<ASTNode>> exprList)
//         :exprList(std::move(exprList)){};
//         vector<unique_ptr<ASTNode>> exprList;
// };



class Literal : public ASTNode{
    public:
        Literal(TokenType type,string value)
        :type(type),value(value){};
        // string print(){
        //      return value;
        // }
        void print() const override {
            std::cout << "Literal {\n";
            std::cout << "value: \"" << value << "\"\n";
            std::cout << "}\n";
        }
    private:
        TokenType type;
        string value;
};

#endif