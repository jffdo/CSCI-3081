#ifndef STACK
#define STACK

#include <iostream>
#include <functional>

class Stack {
  private:
    int* arr = nullptr; // array for storing elements
    int capacity; // maximum size of the stack
    int count; // number of elements in the stack
  public:
    // default constructor, creates an empty stack with capacity of 1000
    Stack();

    // initializes an empty stack with capacity cap
    Stack(int cap);

    // initializes a stack with the elements listed in l
    // the first element listed will be at the top of the stack (first to get popped off)
    // the second element will be the second thing to get popped off and so on
    Stack(std::initializer_list<int> l);

    // copy construcotr
    Stack(const Stack& s);

    // destructor, deallocates arr
    ~Stack();

    // equal assignment operator overload
    // returns a reference to the currect stack
    Stack& operator=(const Stack& s);

    // == operator overload
    // returns true if both stacks contain all of the same elements in the same order
    // capacity does not matter
    bool operator==(const Stack& s);

    // index operator overload
    // The 0th element is the first to be popped off
    // throws std::out_of_range exception if index is out of range
    int& operator[](int i);

    // pops off the first element in the stack
    // exits with exit code EXIT_FAILURE and prints an error message to cout if stack is empty
    int pop();

    // pushes x onto the top of the stack
    // exits with exit code EXIT_FAILURE and prints an error message to cout if stack is full
    // returns a reference to the currect stack
    Stack& push(int x);

    // returns the item at the top of the stack
    // exits with exit code EXIT_FAILURE and prints an error message to cout if stack is empty
    int peek();

    // returns the index of a specified element in the stack
    // returns -1 if e is not in the stack
    int indexOf(int e);

    // returns the number of elements in the stack
    int size();

    // returns whether or not the stack is empty
    bool isEmpty();

    // returns whether or not the stack is full
    bool isFull();

    // returns the current capacity of the stack
    int getCapacity();

    // updates the capacity of the stack
    // returns a reference to the currect stack
    Stack& updateCapacity(int c);

    // clears all the items in the stack
    // returns a reference to the currect stack
    Stack& clear();

    // sorts the elements in the stack in increase order
    // the smallest item will be at the top
    // returns a reference to the currect stack
    Stack& sort();

    // reverses the elemnts in the stack
    // returns a reference to the currect stack
    Stack& reverse();

    // maps the function f over all the elemnts
    // each element, x, in the stack now becomes f(x)
    // returns a reference to the currect stack
    Stack& map(std::function<int(int)> f);

    // filters out any elements, x, where f(x) if false
    // returns a reference to the currect stack
    Stack& filter(std::function<bool(int)> f);

    // reduces the elements in the stack
    // returned item for some stack s will be f(f(f(init, s[0]), s[1])...)
    int reduce(std::function<int(int, int)> f, int init);

    // output stream << operator overload
    // allows you to print stack with std::cout << stack;
    friend std::ostream& operator<<(std::ostream& strm, const Stack& s);
};

#endif
