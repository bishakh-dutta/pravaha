#include<iostream>
#include<fstream>
#include "lexer_logic.h"
using namespace std;
string readSourceCode(const string& path);

// just for test section start
string getTokenTypeName(TokenType type) {
    switch (type) {
        case KEYWORD: return "KEYWORD";
        case IDENTIFIER: return "IDENTIFIER";
        case OPERATOR: return "OPERATOR";
        case EQUALS: return "EQUALS";
        case LITERAL: return "LITERAL";
        case INT: return "INT";
        case FLOAT: return "FLOAT";
        case BOOL: return "BOOL";
        case STRING: return "STRING";
        case INDENT: return "INDENT";
        case DEDENT: return "DEDENT";
        case NUL: return "NUL";
        default: return "UNKNOWN";
    }
}
// just for test section end
int main(){
    string sourceCode;
    try{
        string filePath = "../../examples/hello.prv";
        sourceCode = readSourceCode(filePath);
    }
    catch(const exception& e){
            cerr<<"Error: "<<e.what()<<'\n';
    }
    
    Lexer lexer(sourceCode);
    vector tokens = lexer.getTokens();
    for(const Token i : tokens){
        cout<<"[  "+getTokenTypeName(i.type)+" : "+i.lexeme+"  ]"<<endl;
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