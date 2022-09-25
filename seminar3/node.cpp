#include "node.h"

Node::Node()
{}

// Number
Number::Number(double value) : value{value}
{}

double Number::evaluate() const{
    return value;
}

void Number::print(ostream& os) const{
    os << value;
}


// Operator
Operator::Operator(Node* left, Node* right) :
    left{left}, right{right}
{}

double Addition::evaluate() const{
    return left->evaluate() + right->evaluate();
}

void Addition::print(std::ostream& os) const{
    os << left->evaluate() << "+" << right->evaluate();
}

double Subtraction::evaluate() const {
    return left->evaluate() - right->evaluate();
}

void Subtraction::print(std::ostream& os) const{
    os << left->evaluate() << "-" << right->evaluate();
}

double Multiplication::evaluate() const {
    return left->evaluate() * right->evaluate();
}

void Multiplication::print(std::ostream& os) const{
    os << left->evaluate() << "*" << right->evaluate();
}

double Division::evaluate() const {
    return left->evaluate() / right->evaluate();
}

void Division::print(std::ostream& os) const{
    os << left->evaluate() << "+" << right->evaluate();
}


