#include <cassert>
#include <iostream>

template<typename T>
class New_Allocator
{
public:
    template<typename... Ts>
    static T* create(Ts&&... ts){
        return new T{std::forward<Ts>(ts)...};
    }

    static void destroy(T* t){
        delete t;
    }
};

template<typename T>
class Tracker_Allocator
{
public:
    template<typename... Ts>
    static T* create(Ts&&... ts){
        T* t = New_Allocator<T>::create(std::forward<Ts>(ts)...);
        std::cout << "New object created at: " << t << std::endl;
        return t;
    }

    static void destroy(T* t){
        std::cout << "Removing object at: " << t << std::endl;
        New_Allocator<T>::destroy(t);
    }
};

template<typename T, template<typename> typename Allocator = New_Allocator>
class Stack
{

  struct Node;
  
public:

  Stack()
    : head{nullptr} { }

  Stack(Stack const&) = delete;
  Stack(Stack&&) = delete;

  Stack& operator=(Stack const&) = delete;
  Stack& operator=(Stack&&) = delete;
  
  ~Stack()
  {
    while (!empty())
    {
      pop();
    }
  }
  
  void push(int const& value)
  {
    head = Allocator<Node>::create(value, head);
  }

  int pop()
  {
    int result{top()};
    Node* old {head};
    head = head->next;
    Allocator<Node>::destroy(old);
    return result;
  }

  int& top()
  {
    return head->value;
  }

  int const& top() const
  {
    return head->value;
  }

  bool empty() const
  {
    return head == nullptr;
  }
  
private:
  
  struct Node
  {
    int value;
    Node* next;
  };

  Node* head;
  
};




int main()
{
  // Stack st {};
  Stack<std::string, Tracker_Allocator> st{};
  assert(st.empty());
  
  st.push(1);
  assert(!st.empty());
  assert(st.top() == 1);
  
  st.push(2);
  assert(st.top() == 2);
  assert(st.pop() == 2);
  
  assert(st.pop() == 1);

  assert(st.empty());

  st.push(3);
  assert(st.pop() == 3);
  
  st.push(4);
  
  st.push(5);
  assert(st.pop() == 5);
 
}
