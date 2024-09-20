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
        ExprNode(const string type,unique_ptr<ASTNode> left)
        :type(type),left(std::move(left)){};
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

class ParamNode : public ASTNode{
    public:
        ParamNode(const string type,const string identifier)
        :type(type),identifier(identifier){};
        void print() const override{
            cout<<"Params: {\n";
            cout<<"type: "<<type<<"\n";
            cout<<"identifier: "<<identifier<<"\n";
            cout<<"}\n";
        };
    private:
        string type;
        string identifier;
};

class ArgNode : public ASTNode{
    public:
        ArgNode(const string identifier)
        :identifier(identifier){};
        void print() const override{
            cout<<"Arg: {\n";
            cout<<"identifier: "<<identifier<<"\n";
            cout<<"}\n";
        };
    private:
        string identifier;
};

class FunctionDeclNode : public ASTNode{
    public:
        FunctionDeclNode(const string type,const string identifier,vector<unique_ptr<ASTNode>> paramList,vector<unique_ptr<ASTNode>>functionBody)
        :type(type),identifier(identifier),paramList(std::move(paramList)),functionBody(std::move(functionBody)){};
        FunctionDeclNode(const string type,const string identifier,vector<unique_ptr<ASTNode>>functionBody)
        :type(type),identifier(identifier),functionBody(std::move(functionBody)){};
        void print() const override{
            cout << "FunctionDeclNode {\n";
            cout << "type: \"" << type << "\",\n";
            cout << "identifier: \"" << identifier << "\",\n";
            if(paramList.size()!=0){
                cout<<"ParamList: {\n";
                for(const auto& param:paramList){
                    param->print();
                }
                cout<<"}\n";
            }
            cout << "FunctionBody: {";
            if(functionBody.size()!=0){
                for(const auto& stmt : functionBody){
                    stmt->print();
                }
            }
            cout<<"}\n";
            cout << "}\n";
        };
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
        FunctionCallNode(const string identifier)
        :identifier(identifier){};

        void print() const override{
            cout << "FunctionCallNode {\n";
            cout << "identifier: \"" << identifier << "\",\n";
            if(argList.size()!=0){
                cout<<"ParamList: {\n";
                for(const auto& arg:argList){
                    arg->print();
                }
                cout<<"}\n";
            }
            cout << "}\n";
        };
    private:
        string identifier;
        vector<unique_ptr<ASTNode>> argList;
};

class IfStmtNode : public ASTNode{
    public:
        IfStmtNode(unique_ptr<ASTNode> expr,vector<unique_ptr<ASTNode>> ifblock)
        :expr(std::move(expr)),ifblock(std::move(ifblock)){};

        void print() const override{
            cout << "IfStmtNode {\n";
            cout<<"CndList: {\n";
            expr->print();
            cout<<"}\n";
            cout << "IfBody: {";
            if(ifblock.size()!=0){
                for(const auto& stmt : ifblock){
                    stmt->print();
                }
            }
            cout<<"}\n";
            cout << "}\n";
        };
    private:
        unique_ptr<ASTNode> expr;
        vector<unique_ptr<ASTNode>> ifblock;
};

class ElsIfStmtNode : public ASTNode{
    public:
        ElsIfStmtNode(unique_ptr<ASTNode> expr,vector<unique_ptr<ASTNode>> elsifblock)
        :expr(std::move(expr)),elsifblock(std::move(elsifblock)){};

        void print() const override{
            cout << "ElsIfStmtNode {\n";
            cout<<"CndList: {\n";
            expr->print();
            cout<<"}\n";
            cout << "ElsIfBody: {";
            if(elsifblock.size()!=0){
                for(const auto& stmt : elsifblock){
                    stmt->print();
                }
            }
            cout<<"}\n";
            cout << "}\n";
        };
    private:
        unique_ptr<ASTNode> expr;
        vector<unique_ptr<ASTNode>> elsifblock;
};

class ElseStmtNode : public ASTNode{
    public:
        ElseStmtNode(vector<unique_ptr<ASTNode>> elseblock)
        :elseblock(std::move(elseblock)){};

        void print() const override{
            cout << "ElsStmtNode {\n";
            cout << "ElsBody: {";
            if(elseblock.size()!=0){
                for(const auto& stmt : elseblock){
                    stmt->print();
                }
            }
            cout<<"}\n";
            cout << "}\n";
        };
    private:
        vector<unique_ptr<ASTNode>> elseblock;
};

class ConditionNode : public ASTNode{
    public:
        ConditionNode(unique_ptr<ASTNode> ifBlock,vector<unique_ptr<ASTNode>> elsIfBlockList,unique_ptr<ASTNode> elseBlock)
        :ifBlock(std::move(ifBlock)),elsIfBlockList(std::move(elsIfBlockList)),elseBlock(std::move(elseBlock)){};
        ConditionNode(unique_ptr<ASTNode> ifBlock,unique_ptr<ASTNode> elseBlock)
        :ifBlock(std::move(ifBlock)),elseBlock(std::move(elseBlock)){};
        ConditionNode(unique_ptr<ASTNode> ifBlock,vector<unique_ptr<ASTNode>> elsIfBlockList)
        :ifBlock(std::move(ifBlock)),elsIfBlockList(std::move(elsIfBlockList)){};
        ConditionNode(unique_ptr<ASTNode> ifBlock)
        :ifBlock(std::move(ifBlock)){};

        void print() const override{
            cout << "ConditionNode {\n";
            ifBlock->print();
            if(elsIfBlockList.size()!=0){
                for(const auto& elsIf:elsIfBlockList){
                    elsIf->print();
                }
            }
            if(elseBlock) elseBlock->print();
            cout << "}\n";
        };
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



class Literal : public ASTNode{
    public:
        Literal(TokenType type,string value)
        :type(type),value(value){};
        // string print(){
        //      return value;
        // }
        void print() const override {
            cout << "Literal {\n";
            // cout << "Type: \""<< type <<"\"\n";
            cout << "value: \"" << value << "\"\n";
            cout << "}\n";
        }
    private:
        TokenType type;
        string value;
};

#endif