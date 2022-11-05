#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

/* Expected output:

hello5.3
helloworld
Unknown operator
6.5

 */

// header start

class Variable_Base
{
public:
    virtual void print(std::ostream& os) const {};
    virtual Variable_Base* add(Variable_Base* rhs) const{
        throw std::invalid_argument("Unknown operator");
    };

};

class Number : public Variable_Base
{
public:
    Number(double val) : value{val} {}
    void print(std::ostream& os) const override;
    Variable_Base* add(Variable_Base* rhs) const override;
private:
    double value;
};

class String : public Variable_Base
{
public:
    String(std::string val) : value{val} {}
    void print(std::ostream& os) const override;
    Variable_Base* add(Variable_Base* rhs) const override;
private:
    std::string value;
};

class Variable{
public:
    Variable(double value) : data{new Number{value}} {}
    Variable(std::string value) : data{new String{value}} {}
    Variable(Variable_Base* vb) : data{vb} {}
    Variable operator+(Variable const& other) const;
    void operator=(double const& other);
    void operator=(std::string const& other);
    friend std::ostream& operator<<(std::ostream& os, Variable const& rhs);
private:
    Variable_Base* data;
};

// header end
// class implementation start

void Number::print(std::ostream& os) const{
    os << value;
}

Variable_Base* Number::add(Variable_Base* rhs) const{
    if (auto p = dynamic_cast<Number*>(rhs)){
        // rhs is number
        // Number n{p->value + value};
        return new Number{p->value + value};
    } else {
        // throw exception
        return Variable_Base::add(rhs);
    }
}

void String::print(std::ostream& os) const{
    os << value;
}

Variable_Base* String::add(Variable_Base* rhs) const{
    if (dynamic_cast<Number*>(rhs)){
        std::ostringstream oss;
        print(oss); // put string in oss
        rhs->print(oss);
        return new String{oss.str()};
    }
    else if (auto p = dynamic_cast<String*>(rhs)){
        return new String{value + p->value};
    }
    else {
        return Variable_Base::add(rhs);
    }
}

Variable Variable::operator+(Variable const& other) const{
    return Variable{data->add(other.data)};
}

void Variable::operator=(double const& other){
    data = new Number{other};
}

void Variable::operator=(std::string const& other) {
    data = new String{other};
}

std::ostream& operator<<(std::ostream& os, Variable const& rhs){
    rhs.data->print(os);
    return os;
}

int main()
{
    Variable var1 { "hello" };
    Variable var2 { 5.3 };
    Variable var3 { "world" };
    Variable var4 { 1.2 };
    
    std::cout << var1 + var2 << std::endl;
    std::cout << var1 + var3 << std::endl;

    try
    {
	std::cout << var2 + var3 << std::endl;
    } catch (std::exception& e)
    {
	std::cerr << e.what() << std::endl;
    }
    
    std::cout << var2 + var4 << std::endl;
    
}