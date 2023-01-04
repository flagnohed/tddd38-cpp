#include <iostream>
#include <vector>

/* Expected output:

!true = false
!(true && false) = true
(true || false) && false && (false || !false) = false

 */

//classes




class Expression {
public:
    virtual ~Expression() = default;
    virtual bool evaluate() = 0;
    virtual void print(std::ostream& os) = 0;
};

void pretty_print(std::ostream& os, Expression* e);

class Literal : public Expression {
public:
    Literal(bool value) : value{value} {}
    bool evaluate() override {
        return value;
    }
    void print(std::ostream& os) override {
        if (value) {
            os << "true";
        } else {
            os << "false";
        }
    }
private:
    bool value;
};

class Negation : public Expression {
public:
    Negation(Expression* expression) : expression{expression} {}
    ~Negation() {
        delete expression;
    }
    bool evaluate() override {
        bool res = expression->evaluate();
        return !res;
    }
    void print(std::ostream& os) override {
        os << '!';
        pretty_print(os, expression);
    }
private:
    Expression* expression;
};

class Compound : public Expression {
public:
    Compound(std::initializer_list<Expression*> const& expressions) : 
    expressions{expressions.begin(), expressions.end()} {}
    ~Compound() {
        for (Expression* e: expressions) {
            delete e;
        }
    }

    virtual std::string glyph() = 0;
    void print(std::ostream& os) override {
        for (auto it{expressions.begin()}; it != expressions.end() - 1; it++) {
            pretty_print(os, *it);
            os << glyph();
        }
        pretty_print(os, expressions.back());
    }
    std::vector<Expression*> expressions{};

//private: // private inheritance or public? will it reach expressions with public?
    
};

class And : public Compound {
public:
    using Compound::Compound;
    std::string glyph() override {
        return "&&";
    }
    bool evaluate() override {
        for (Expression* e: expressions) {
            if (!e->evaluate()) {
                return false;
            }
        }
        return true;
    }
private:
    Compound* comp;
};

class Or : public Compound {
public:
    using Compound::Compound;
    std::string glyph() override {
        return "||";
    }
    bool evaluate() override {
        for (Expression* e: expressions) {
            if (e) {
                return true;
            }
        }
        return false;
    }
private:
    Compound* comp;
};


void pretty_print(std::ostream& os, Expression* e) {

    if (dynamic_cast<Compound*>(e) != nullptr) {
        // has compound as base
        os << '(';
        e->print(os);
        os << ')';
    } else {
        e->print(os);
    }
    
}


int main()
{

    // Think carefully about the types here. You might have to modify
    // the testcases slightly to make it work.
    
    Expression* expr1 { new Negation { new Literal { true } } };

    expr1->print(std::cout);
    std::cout << " = " << expr1->evaluate() << std::endl;
    
    Expression* expr2 {
	new Negation {
	    new And { new Literal { true }, new Literal { false } }
	}
    };

    expr2->print(std::cout);
    std::cout << " = " << expr2->evaluate() << std::endl;
    
    Expression* expr3 {
	new And {
	    new Or { new Literal { true }, new Literal { false } },
	    new Literal { false },
	    new Or { new Literal { false }, new Negation { new Literal{false} } }
	}
    };

    expr3->print(std::cout);
    std::cout << " = " << expr3->evaluate() << std::endl;
    
    
    
    
    
}