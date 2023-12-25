#ifndef __HEAP_H
#define __HEAP_H
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <stack>

class Operation
{
   public:
    Operation(char op, int prio, bool is_unary = false) :
        _op(op),
        _prio(prio),
        _is_unary(is_unary){

        };
    virtual ~Operation(){};
    virtual int Eval (int a, int b) {
        return a + b;
    };

    virtual int Eval (int a) {
        return a;
    };

    char GetOp (void) {
        return _op;
    }

    int GetPrio (void) {
        return _prio;
    }

    bool IsUnary (void) {
        return _is_unary;
    }

   private:
    char _op;
    int _prio;
    bool _is_unary;
};

class Add : public Operation
{
   public:
    Add(char op, int prio, bool is_unary = false) : Operation(op, prio, is_unary){};
    int Eval (int a, int b) {
        return (a + b);
    }
};

class Sub : public Operation
{
   public:
    Sub(char op, int prio, bool is_unary = false) : Operation(op, prio, is_unary){};
    int Eval (int a, int b) {
        return (a - b);
    }
};

class SubUn : public Operation
{
   public:
    SubUn(char op, int prio, bool is_unary = true) : Operation(op, prio, is_unary){};

    int Eval (int a) {
        return -a;
    }
};

class Mul : public Operation
{
   public:
    Mul(char op, int prio, bool is_unary = false) : Operation(op, prio, is_unary){};
    int Eval (int a, int b) {
        return (a * b);
    }
};

class Div : public Operation
{
   public:
    Div(char op, int prio, bool is_unary = false) : Operation(op, prio, is_unary){};
    int Eval (int a, int b) {
        return (a / b);
    }
};

class Calculator
{
   public:
    using ElemType = std::shared_ptr<Operation>;
    Calculator() = default;

    void AddOperation (ElemType op) {
        _operations[op->GetOp()] = std::move(op);
    }
    void AddUnaryOperation (ElemType op) {
        _unary_operations[op->GetOp()] = std::move(op);
    }

    int Eval (std::string &s) {
        std::stack<ElemType> op;
        std::stack<int> num;
        bool is_unary = true;

        for(int i = 0; i < s.size(); ++i) {
            if(IsValid(s[i])) {
                if(s[i] == '(') {
                    op.push(CharToOperation(s[i], false));
                    is_unary = true;
                } else if(s[i] == ')') {
                    while(op.top()->GetOp() != '(') {
                        Process(num, op.top());
                        op.pop();
                    }
                    op.pop();
                    is_unary = false;
                } else if(IsOperation(s[i])) {
                    auto tmp = CharToOperation(s[i], is_unary);
                    while(!op.empty() && tmp->GetPrio() <= op.top()->GetPrio()) {
                        Process(num, op.top());
                        op.pop();
                    }
                    op.push(tmp);
                    is_unary = true;
                } else {
                    std::string tmp = "";
                    while(i < s.size() && s[i] >= '0' && s[i] <= '9') {
                        tmp.push_back(s[i]);
                        ++i;
                    }
                    --i;
                    num.push(atoi(tmp.c_str()));
                    is_unary = false;
                }
            }
        }
        while(!op.empty()) {
            Process(num, op.top());
            op.pop();
        }
        return num.top();
    }
    ElemType CharToOperation (char s, bool is_unary) {
        ElemType ret;
        if(is_unary) {
            auto elem = _unary_operations.find(s);
            if(elem != _unary_operations.end()) {
                ret = elem->second;
            }
        } else {
            auto elem = _operations.find(s);
            if(elem != _operations.end()) {
                ret = elem->second;
            }
        }
        return ret;
    }

   private:
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

    void Process (std::stack<int> &num, ElemType op) {
        if(op->IsUnary()) {
            int right = num.top();
            num.pop();
            num.push(op->Eval(right));
        } else {
            int right = num.top();
            num.pop();
            int left = num.top();
            num.pop();
            num.push(op->Eval(left, right));
        }
    }
    std::unordered_map<char, ElemType> _operations;
    std::unordered_map<char, ElemType> _unary_operations;
};

#endif /* __HEAP_H */