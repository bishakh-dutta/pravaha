#include<iostream>
#include<fstream>
#include "lexer/lexer.hpp"
using namespace std;
string readSourceCode(const string& path);
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