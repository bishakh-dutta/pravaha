#include<iostream>
#include<fstream>
#include "src/lexer/lexer.hpp"
#include "src/parser/parser.hpp"
#include "src/parser/tokenstream/tokenstream.hpp"
#include "src/parser/ast.hpp"
using namespace std;
string readSourceCode(const string& path);
int main(){
    string filePath = "./tests/parser_tests/parser_test.prv";
    string sourceCode;
    try {
        sourceCode = readSourceCode(filePath);
    }
    catch(const exception& e){
            cerr<<"Error: "<<e.what()<<'\n';
    }
    Lexer lexer(sourceCode);
    vector tokens = lexer.getTokens();
    TokenStream tokenStream(tokens);
    Parser Parser(tokenStream);
    unique_ptr<ASTNode> ast = Parser.parseProgram();

    auto stmtListNode = dynamic_cast<StmtList*>(ast.get());
    if (stmtListNode) {
        for (const auto& stmt : stmtListNode->statements) {
            auto varDeclNode = dynamic_cast<VariableDeclNode*>(stmt.get());
            if (varDeclNode) {
                cout << "Identifier: " << varDeclNode->getIdentifier() << endl;
            }
        }
    }
}
string readSourceCode(const string& path){
    ifstream sourceCode(path);
    if(!sourceCode.is_open()){
        throw runtime_error("Unable to open file: "+path+" (Please check if file exits at the specified path)");
    }
    string codeStr;
    string line;
    while(getline(sourceCode,line)){
        codeStr+=line+'\n';
    }
    return codeStr;
}