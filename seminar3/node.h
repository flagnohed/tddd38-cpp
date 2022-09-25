#pragma once
#include <string>
#include <ostream>
using namespace std;
class Node
{
public:
    Node();
    virtual double evaluate() const;
    virtual void print(std::ostream& os) const;
    virtual void print_tree(std::ostream& os, int i);
    virtual Node* clone();
};

class Number : public Node
{
public:
    Number(double value);
    double evaluate() const override;
    void print(std::ostream& os) const override;
protected:
    double value;
};

class Operator : public Node
{
public:
    Operator(Node* left, Node* right);
    double evaluate() const override;
    void print(std::ostream &os) const override;
protected:
    Node* left;
    Node* right;
};

class Addition : public Operator
{
public:
    using Operator::Operator;
    double evaluate() const override;
    void print(std::ostream &os) const override;
};

class Multiplication : public Operator
{
public:
    using Operator::Operator;
    double evaluate() const override;
    void print(std::ostream &os) const override;
};

class Subtraction : public Addition
{
public:
    using Addition::Addition;
    double evaluate() const override;
    void print(std::ostream &os) const override;
};

class Division : public Multiplication
{
public:
    using Multiplication::Multiplication;
    double evaluate() const override;
    void print(std::ostream &os) const override;
};
