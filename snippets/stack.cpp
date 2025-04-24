#include <iostream>
using namespace std;

/**
 * Stack - A Last-In-First-Out (LIFO) data structure implementation
 * Operations:
 * - push: Add an element to the top of the stack
 * - pop: Remove the top element from the stack
 * - top: Get the top element without removing it
 * - isEmpty: Check if the stack is empty
 * - size: Get the number of elements in the stack
 */
class Stack {
private:
    static const int MAX_SIZE = 1000;
    int data[MAX_SIZE];
    int stackTop;

public:
    // Constructor
    Stack() {
        stackTop = -1;
    }

    // Add an element to the top of the stack
    void push(int value) {
        if (stackTop >= MAX_SIZE - 1) {
            throw overflow_error("Stack Overflow");
        }
        data[++stackTop] = value;
    }

    // Remove and return the top element from the stack
    int pop() {
        if (isEmpty()) {
            throw underflow_error("Stack Underflow");
        }
        return data[stackTop--];
    }

    // Get the top element without removing it
    int top() const {
        if (isEmpty()) {
            throw underflow_error("Stack is empty");
        }
        return data[stackTop];
    }

    // Check if the stack is empty
    bool isEmpty() const {
        return stackTop < 0;
    }

    // Get the number of elements in the stack
    int size() const {
        return stackTop + 1;
    }

    // Display all elements in the stack (for debugging)
    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        
        cout << "Stack elements: ";
        for (int i = stackTop; i >= 0; i--) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};