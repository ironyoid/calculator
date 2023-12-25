#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include "calculator.hpp"

int main (int argc, char *argv[]) {
    Calculator calculator;
    calculator.AddOperation(std::move(std::make_shared<Add>('(', -1)));
    calculator.AddOperation(std::move(std::make_shared<Sub>(')', -1)));
    calculator.AddOperation(std::move(std::make_shared<Add>('+', 1)));
    calculator.AddOperation(std::move(std::make_shared<Sub>('-', 1)));
    calculator.AddOperation(std::move(std::make_shared<Mul>('*', 2)));
    calculator.AddOperation(std::move(std::make_shared<Div>('/', 2)));
    calculator.AddUnaryOperation(std::move(std::make_shared<SubUn>('-', 4, true)));

    std::string s = "((1 + 2) * 4 + (-5 - 4) * 10) / -2";

    std::cout << "ans = " << calculator.Eval(s) << std::endl;
}