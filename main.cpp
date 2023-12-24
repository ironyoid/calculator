#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include "calculator.hpp"

int main (int argc, char *argv[]) {
    std::stack<char> op;
    std::stack<int> num;
    Calculator calculator;
    calculator.AddOperation(std::move(std::make_unique<Add>('+', 1)));
    calculator.AddOperation(std::move(std::make_unique<Sub>('-', 1)));
    calculator.AddOperation(std::move(std::make_unique<Mul>('*', 2)));
    calculator.AddOperation(std::move(std::make_unique<Div>('/', 2)));
    std::string s = "(1 + 2) * 4";

    for(int i = 0; i < s.size(); ++i) {
        if(calculator.IsValid(s[i])) {
            if(s[i] == '(') {
                op.push(s[i]);
            } else if(s[i] == ')') {
                while(op.top() != '(') {
                    calculator.Process(num, op.top());
                    op.pop();
                }
                op.pop();
            } else if(calculator.IsOperation(s[i])) {
                while(!op.empty() && calculator.GetPrio(s[i]) <= calculator.GetPrio(op.top())) {
                    calculator.Process(num, op.top());
                    op.pop();
                }
                op.push(s[i]);
            } else {
                std::string tmp = "";
                while(i < s.size() && s[i] >= '0' && s[i] <= '9') {
                    tmp.push_back(s[i]);
                    ++i;
                }
                --i;
                num.push(atoi(tmp.c_str()));
            }
        }
    }
    while(!op.empty()) {
        calculator.Process(num, op.top());
        op.pop();
    }
    std::cout << "ans = " << num.top() << std::endl;
}