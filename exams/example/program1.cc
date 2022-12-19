#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include <type_traits>

using namespace std;

class Printable {
public:
    virtual void print(ostream& os) const = 0;
};

class Serializable {
public:
    virtual string serialize() const = 0;
    virtual bool deserialize(string str) = 0;
};

class Message : public Printable {
public:
    Message(string msg) : msg{msg} {}
    void print(ostream& os) const override{
        os << msg << '\n';
    }
private:
    string msg;
};

class Integer : public Printable, public Serializable {
public:
    Integer(int data) : data{data} {}
    void print(ostream& os) const override {os << data << '\n';}
    string serialize() const override {
        return to_string(data);
    }
    bool deserialize(string str) override {
        return (data = stoi(str)); 
    }

private:
    int data;
};

vector<string> serialize(vector<Printable*> const& v)
{
  vector<string> result{};
  for (Printable* obj : v)
  {
    
    if (auto i = dynamic_cast<Serializable*>(obj))
    {
      result.push_back(i->serialize());
    }
  }
  return result;
}




void print(ostream& os, vector<Printable*> const& v)
{
  for (Printable* obj : v)
  {
    obj->print(os);
  }
}

int main()
{
  vector<Printable*> v = {
    new Message{"Hello there"},
    new Integer{0},
    new Message{"This is a message"},
    new Integer{100053},
    new Integer{-5}
  };

  {
    auto result {serialize(v)};
    assert((result == vector<string>{"0", "100053", "-5"}));
  }
  
  {
    ostringstream oss{};
    print(oss, v);
    assert(oss.str() == "Hello there\n0\nThis is a message\n100053\n-5\n");
  }

  {
    Integer i{0};
    assert(i.deserialize("15"));
    assert(i.serialize() == "15");
  }
  
}