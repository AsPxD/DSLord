#include <iostream>
using namespace std;

/**
 * Queue - A First-In-First-Out (FIFO) data structure implementation
 * Operations:
 * - enqueue: Add an element to the end of the queue
 * - dequeue: Remove the first element from the queue
 * - front: Get the first element without removing it
 * - isEmpty: Check if the queue is empty
 * - size: Get the number of elements in the queue
 */
class Queue {
private:
    static const int MAX_SIZE = 1000;
    int data[MAX_SIZE];
    int frontIdx;
    int rearIdx;
    int count;

public:
    // Constructor
    Queue() {
        frontIdx = 0;
        rearIdx = -1;
        count = 0;
    }

    // Add an element to the end of the queue
    void enqueue(int value) {
        if (count >= MAX_SIZE) {
            throw overflow_error("Queue Overflow");
        }
        rearIdx = (rearIdx + 1) % MAX_SIZE;
        data[rearIdx] = value;
        count++;
    }

    // Remove and return the first element from the queue
    int dequeue() {
        if (isEmpty()) {
            throw underflow_error("Queue Underflow");
        }
        int value = data[frontIdx];
        frontIdx = (frontIdx + 1) % MAX_SIZE;
        count--;
        return value;
    }

    // Get the first element without removing it
    int front() const {
        if (isEmpty()) {
            throw underflow_error("Queue is empty");
        }
        return data[frontIdx];
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return count == 0;
    }

    // Get the number of elements in the queue
    int size() const {
        return count;
    }

    // Display all elements in the queue (for debugging)
    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        
        cout << "Queue elements: ";
        int index = frontIdx;
        for (int i = 0; i < count; i++) {
            cout << data[index] << " ";
            index = (index + 1) % MAX_SIZE;
        }
        cout << endl;
    }
};