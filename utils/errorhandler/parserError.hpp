#include<string>
#include <iostream>
#include <cstdlib>
using namespace std;
enum ErrorType{
    UNEXP_TOK,
    MISS_TOK,
    // will add more later
};
string ClassifyError(ErrorType err,string tok,string exp){
    string msg="";
    switch(err){
        case UNEXP_TOK:
            if(exp!=""){
                msg = "Unexpected token \""+tok+"\", expected \""+exp+"\"";
            }else{
                msg = "Unexpected token \""+tok+"\"";
            }
            break;
        case MISS_TOK:
            if(exp!=""){
                msg = "Missing token \""+tok+"\", expected \""+exp+"\"";
            }else{
                msg = "Missing token \""+tok+"\"";
            }
            break;
        default:
            break;
    }
    return msg;
}
class NewError{
    public:
        NewError(ErrorType err,string tok,string exp,int l,int c):line(l),col(c){
            ErrMsg(err,tok,exp);
            cerr<<this->msg;
            exit(EXIT_FAILURE);
        };
        void ErrMsg(ErrorType err,string tok,string exp){
            string pos = " at line: "+to_string(line)+", column: "+to_string(col)+"\n";
            this->msg = ClassifyError(err,tok,exp)+pos;
        };
    private:
        string msg;
        int line,col;
};