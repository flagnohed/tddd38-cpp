#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
/* implement your classes here */
// TIME TAKEN: 1.5H
using namespace std;
class Operation {
public:
    Operation() = default;
    ~Operation() = default;
    Operation(Operation& op) = delete;
    virtual std::string apply(std::string str) = 0;
    virtual bool redundant_after(Operation const& op) const = 0;
};

class Replace : public Operation {
public:
    Replace(char t, char r) 
        : target{t}, replacement{r} { }
    std::string apply(std::string str) override {
        std::string new_str{};
        for (auto it{str.begin()}; it != str.end(); it++) {
            if (*it == target) {
                new_str += replacement;
            } else {
                new_str += *it;
            }
        }
        return new_str;
    }
    bool redundant_after(Operation const& op) const override {
      
        if (auto p = dynamic_cast<Replace const*>(&op)) {
            return target == p->target;
        }
        return false;
    }
private:
    char target;
    char replacement;
};

class Lowercase : public Operation {
public:
    std::string apply(std::string str) override {
        string res{};
        for (int i{0}; i < str.size(); ++i) {
            res += tolower(str[i]);
        }
        return res;
    }
    bool redundant_after(Operation const& op) const override {
        return typeid(op) == typeid(Lowercase);
        
    }
};

class Capitalize : public Lowercase {
public:
    std::string apply(std::string str) override {
        string res{Lowercase::apply(str)};
        res = (char) toupper(res.front()) + res.substr(1, str.size() - 1);
        return res;
    }
    bool redundant_after(Operation const& op) const override {
        return typeid(op) == typeid(Capitalize);
    }
};


bool has_redundancy(vector<Operation*> const& operations)
{
    for (int i{1}; i < operations.size(); ++i)
    { 
        if (operations[i]->redundant_after(*operations[i-1]))
            return true;
    }
    return false;
}

void apply(vector<Operation*> const& operations, vector<string>& text)
{
    for (auto&& op : operations)
    {
        for (auto&& str : text)
        {
            str = op->apply(str);
        }
    }
}

int main()
{
    vector<string> test {"TDDD38", "Advanced", "programming", "in", "C++" };
    
    {
        vector<string> current {test};
        vector<Operation*> operations {
            new Capitalize{}, new Lowercase{}, new Lowercase{}
        };

        // Should have redundancy since we have two Lowecase in a row
        assert(has_redundancy(operations));
        apply(operations, current);
        
        assert((current == vector<string>{"tddd38", "advanced", "programming", "in", "c++"}));
    }
    
    {
        vector<string> current {test};
        vector<Operation*> operations {
            new Capitalize{}, new Capitalize{}
        };

        // Should have redundancy since we have two Capitalize in a row
        assert(has_redundancy(operations));
        apply(operations, current);
        assert((current == vector<string>{"Tddd38", "Advanced", "Programming", "In", "C++"}));
    }
    {
        vector<string> current {test};
        vector<Operation*> operations {
            new Lowercase{}, new Replace{'t', 'T'}, new Replace{'d', 'D'}
        };

        assert(!has_redundancy(operations));
        apply(operations, current);
        assert((current == vector<string>{"TDDD38", "aDvanceD", "programming", "in", "c++"}));
    }
    
    {
        vector<string> current {test};
        vector<Operation*> operations {
            new Lowercase{}, new Replace{'t', 'T'}, new Replace{'t', 'V'}
        };

        // Should have redundancy since we have two replacers in a row
        // that replace the same character
        assert(has_redundancy(operations));
        apply(operations, current);
        assert((current == vector<string>{"Tddd38", "advanced", "programming", "in", "c++"}));
    }
}
