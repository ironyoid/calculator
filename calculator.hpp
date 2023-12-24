#ifndef __HEAP_H
#define __HEAP_H
#include <iostream>
#include <vector>
#include <functional>
#include <stack>

class Operation
{
   public:
    Operation(char op, int prio) :
        _op(op),
        _prio(prio){

        };
    virtual ~Operation(){};
    virtual int Eval (int a, int b) = 0;

    char GetOp (void) {
        return _op;
    }

    int GetPrio (void) {
        return _prio;
    }

   private:
    char _op;
    int _prio;
};

class Add : public Operation
{
   public:
    Add(char op, int prio) : Operation(op, prio){};
    int Eval (int a, int b) {
        return (a + b);
    }
};

class Sub : public Operation
{
   public:
    Sub(char op, int prio) : Operation(op, prio){};
    int Eval (int a, int b) {
        return (a - b);
    }
};

class Mul : public Operation
{
   public:
    Mul(char op, int prio) : Operation(op, prio){};
    int Eval (int a, int b) {
        return (a * b);
    }
};

class Div : public Operation
{
   public:
    Div(char op, int prio) : Operation(op, prio){};
    int Eval (int a, int b) {
        return (a / b);
    }
};

class Calculator
{
   public:
    using ElemType = std::unique_ptr<Operation>;
    Calculator() = default;

    void AddOperation (ElemType op) {
        _operations[op->GetOp()] = std::move(op);
    }

    bool IsValid (char s) {
        return s != ' ';
    }

    bool IsOperation (char s) {
        auto elem = _operations.find(s);
        return elem != _operations.end();
    }

    int GetPrio (char s) {
        int ret = -1;
        auto elem = _operations.find(s);
        if(elem != _operations.end()) {
            ret = elem->second->GetPrio();
        }
        return ret;
    }

    void Process (std::stack<int> &num, char op) {
        int right = num.top();
        num.pop();
        int left = num.top();
        num.pop();
        num.push(_operations[op]->Eval(left, right));
    }

   private:
    std::unordered_map<char, ElemType> _operations;
};

#endif /* __HEAP_H */