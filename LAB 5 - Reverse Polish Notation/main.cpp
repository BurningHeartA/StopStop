#include <iostream>
#include <stack>
#include <list>
using namespace std;
// program works only with integer input numbers,
// has only 4 standart arifmetic operations.
// result can be float in division.
// you can change input string down there at the end of main()

class operation{
public:
    operation(char sign, int priority){
        this->sign = sign;
        this->priority = priority;
    }
    char sign;
    int priority;
    operation(){
        this->priority = -1;
    }
};

inline bool operator<(const operation& lhs, const operation& rhs)
{
  return lhs.sign < rhs.sign;
}

class ContainerOperation{
public:
list<operation> Operations;

void Add(operation OP){
        Operations.insert(Operations.end(),OP);
}

operation Find(char s){
        list<operation>::iterator it;
        bool found = false;
        for (it = Operations.begin(); (it != Operations.end()) and !found; ++it){
            if (it->sign==s){
                found = true;
                return *it;
            }
        }
        return operation();
    }
};

bool isDigit(char a){
    if ((a>='0') && (a<='9')){
        return true;
    }
    return false;
}

string PolishReverseNotation(string s, ContainerOperation Ops){
    stack<operation> OpStack;
    string out="";
    string word="";
    bool error = false;
    for (int i=0; (i< s.size()) && !error;i++){
        if (isDigit(s[i])){
            word+=s[i];
            continue;
        } else {
            if (word!=""){
                out+=word+" ";
                word = "";
            }
            if(s[i]!=' '){
                operation cur_op = Ops.Find(s[i]);
                if (cur_op.priority>-1){
                    if (cur_op.sign == '('){
                        OpStack.push(cur_op);
                    } else {
                        if (cur_op.sign == ')'){
                            bool left_bracket_found = false;
                            if (!OpStack.empty()){
                                while (!OpStack.empty() && !left_bracket_found){
                                    if (OpStack.top().sign!='(') {
                                            if (OpStack.top().priority != 1) {
                                                out += OpStack.top().sign;
                                                out += " ";
                                            }
                                            OpStack.pop();
                                    } else {
                                        left_bracket_found = true;
                                        OpStack.pop();
                                    }
                                }
                            }
                        } else {
                            if (OpStack.empty()) {
                                OpStack.push(cur_op);
                                continue;
                            } else {
                                if (cur_op.priority > OpStack.top().priority) {
                                    OpStack.push(cur_op);
                                    continue;
                                } else {
                                    bool found = false;
                                    while (!OpStack.empty() && !found) {
                                        if (cur_op.priority < OpStack.top().priority) {
                                            if (OpStack.top().priority != 1) {
                                                out += OpStack.top().sign;
                                                out += " ";
                                            }
                                            OpStack.pop();
                                        } else {
                                            found = true;
                                        }
                                    }
                                    OpStack.push(cur_op);
                                }
                            }
                        }
                    }
                } else{
                    error = true;
                }
            }
        }
    }
    if (word!=""){
        out+=word+" ";
    }
    if (error){
        cout<<"Wrong expression!\n";
        out = "";
    } else {
        if (!OpStack.empty()){
            while (!OpStack.empty()){
                //cout<<OpStack.top().sign<<endl;
                if (OpStack.top().priority != 1) {
                    out += OpStack.top().sign;
                    out +=" ";
                }
                OpStack.pop();
            }
        }
    }

    return out;
}

float Calculate(string s) {
    stack<float> numbers;                //стек
    float num1, num2, res;
    string word = "";
    for (int i = 0; i < s.length(); ++i) {
        if (isDigit(s[i])) {
            word += s[i];
        } else {
            if (word != "") {
                numbers.push((float)stof(word));
            }
            word = "";
            if (s[i] != ' ') {
                num1 = numbers.top();
                numbers.pop();
                num2 = numbers.top();
                numbers.pop();
                switch (s[i]) {
                    case '+':
                        res = num2 + num1;
                        break;
                    case '-':
                        res = num2 - num1;
                        break;
                    case '*':
                        res = num2 * num1;
                        break;
                    case '/':
                        if (num1!=0){
                            res = ((float) num2) / ((float)num1);
                        }
                        else{
                            cout << "Деление на 0\n";
                        }
                        break;
                    default:
                        cout << "Ошибка !\n";
                }
                numbers.push(res);
            }
        }
    }
    return numbers.top();
}

int main() {
    ContainerOperation Ops;
    operation plus('+',2);
    operation minus('-',2);
    operation mul('*',3);
    operation div('/',3);
    operation Lb('(',1);
    operation Rb(')',1);
   Ops.Add(plus);
   Ops.Add(minus);
    Ops.Add(mul);
    Ops.Add(div);
    Ops.Add(Lb);
    Ops.Add(Rb);
    // enter your string s here
    string s = "     300/600    +    (((( 2 *   5/4))-1)*12)   +       2   ";// = 0.5+ (2.5-1)*12 +2 = 0.5 +18 +2 = 20.5
    cout<< "Your string: "<< s<< endl;
    cout<<"Polish Reverse Notation of your string:"<<endl;
    string res = PolishReverseNotation(s,Ops);
    cout << res << endl;
    cout <<"Calculating..."<<endl;
    cout <<"Result: "<<Calculate(res)<<endl;
    return 0;
}
