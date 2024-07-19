#include<iostream>
#include<fstream>
#include "lexer/lexer.hpp"
using namespace std;
string readSourceCode(const string& path);
string getTokenTypeName(TokenType type);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << argv[0] << "Enter file path" << endl;
        return 1;
    }
    string sourceCode;
    try {
        string filePath = argv[1];
        sourceCode = readSourceCode(filePath);
    }
    catch(const exception& e){
            cerr<<"Error: "<<e.what()<<'\n';
    }
    
    Lexer lexer(sourceCode);
    vector tokens = lexer.getTokens();
    for(const Token i : tokens){
        cout << "[  " + getTokenTypeName(i.type) + " : " + i.lexeme + "       (Line: " + to_string(i.line) + " Col: " + to_string(i.column) + ") ]" << endl;
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