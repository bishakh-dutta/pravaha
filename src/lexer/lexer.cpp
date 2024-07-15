#include<iostream>
#include<fstream>
#include "lexer_logic.h"
using namespace std;
string readSourceCode(const string& path);
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
        cout<<i.type<<" "<<i.lexeme<<endl;
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