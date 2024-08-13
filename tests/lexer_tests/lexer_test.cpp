#include<iostream>
#include<fstream>
#include "src/lexer/lexer.hpp"
using namespace std;
string readSourceCode(const string& path);
string getTokenTypeName(TokenType type);
void printCode(vector<Token> tokens);
int main(){
    //string filePath = "./tests/lexer_tests/lexer_test.prv";
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
    
    printCode(tokens);
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

void printCode(vector<Token> tokens){
    int indent = 0,level=0,flag=0;
    for(int i=0;i<tokens.size();i++){
        Token t = tokens[i];
        if(t.lexeme=="INDENT"){
            indent++;
            flag=1;
        }else if(t.lexeme=="DEDENT"){
            indent--;
            flag=1;
        }else{
            flag=0;
        }
        if(flag==1){
            continue;
        }
        while(level<indent){
            cout<<"\t";
            level++;
        }
        cout<<t.lexeme<<" ";
        if(tokens[i+1].line!=tokens[i].line){
            level=0;
            cout<<endl;
        }
    }
}