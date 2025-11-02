#include <iostream>
#include <cctype>
#include <vector>
#include <string>

std::vector <int> math_op(const char*);

//                              Operations that are suported
float sum(float, float);     float dif(float, float);
float mul(float, float);     float div(float, float);
int rem  (int, int);

int main(int argc, char **argv){
    if(argc != 2){
        std::cerr << "Incorrect argument count!"; return 1;
    }   //      If invalid argument count

    if(!isdigit(argv[1][0]) && argv[1][0] != '-'){
        std::cerr << "Expression cannot starts at math operator. Exception is '-'";
        return 2;
    }   //      If Expression begins with illegal characters

//                              Checking where math operators is
    std::vector <int> op_id = math_op(argv[1]);
    std::string expr(argv[1]);
    int op_count = op_id.size();

    for(int i = 0; i < op_count; i++){
        op_id.clear();      op_id = math_op(expr.c_str());      op_id.shrink_to_fit();

//                              Writing numbers to amount vector
        std::vector <float> amount;  int start = 0;
        for(int i = 0; i < op_id.size(); i++){
            amount.push_back(std::stof(expr.substr(start, op_id[i] - start)));
            if(op_id.size() > i + 1) start = op_id[i] + 1;
        }
        amount.push_back(std::stof(expr.substr(op_id[op_id.size() - 1] + 1, expr.size() - op_id[op_id.size() - 1])));

//                                      Math
        if     (expr[op_id[0]] == '+')  expr.replace(0, op_id[1], std::to_string(sum(amount[0], amount[1])));
        else if(expr[op_id[0]] == '-')  expr.replace(0, op_id[1], std::to_string(dif(amount[0], amount[1])));
        else if(expr[op_id[0]] == '*')  expr.replace(0, op_id[1], std::to_string(mul(amount[0], amount[1])));
        else if(expr[op_id[0]] == '/')  expr.replace(0, op_id[1], std::to_string(div(amount[0], amount[1])));
        else if(expr[op_id[0]] == '%')  expr.replace(0, op_id[1], std::to_string(rem((int)amount[0], (int)amount[1])));
    }

//                                 Printing result and cutoff unnecessary '0'
    if(std::stof(expr) == std::stoi(expr))  std::cout << std::stoi(expr);
    else                                    std::cout << std::stof(expr);
    return 0;
}

float sum(float a, float b){return a+b;}
float dif(float a, float b){return a-b;}
float mul(float a, float b){return a*b;}
float div(float a, float b){return a/b;}
int rem  (int a, int b)    {return a%b;}

std::vector <int> math_op(const char *expr){
    std::vector <int> op_id;
    for(int i = 1; i < strlen(expr); i++){
        if(!isdigit(expr[i]) && expr[i] != '.'){
            op_id.push_back(i);
        }
    }
    return op_id;
}
