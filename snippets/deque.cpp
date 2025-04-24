/**
 * Deque - A Double-ended Queue implementation
 * Operations:
 * - insertFront: Insert an element at the front
 * - insertRear: Insert an element at the rear
 * - deleteFront: Delete the front element
 * - deleteRear: Delete the rear element
 * - getFront: Get the front element
 * - getRear: Get the rear element
 * - isEmpty: Check if the deque is empty
 * - isFull: Check if the deque is full
 * - size: Get the number of elements in the deque
 */
class Deque {
private:
    static const int MAX_SIZE = 1000;
    int data[MAX_SIZE];
    int front;
    int rear;
    int count;

public:
    // Constructor
    Deque() {
        front = -1;
        rear = 0;
        count = 0;
    }
    
    // Check if the deque is full
    bool isFull() const {
        return count == MAX_SIZE;
    }
    
    // Check if the deque is empty
    bool isEmpty() const {
        return count == 0;
    }
    
    // Insert an element at the front
    void insertFront(int value) {
        if (isFull()) {
            throw overflow_error("Deque Overflow");
        }
        
        // If deque is empty
        if (isEmpty()) {
            front = rear = 0;
        } else {
            // Update front
            front = (front - 1 + MAX_SIZE) % MAX_SIZE;
        }
        
        data[front] = value;
        count++;
    }
    
    // Insert an element at the rear
    void insertRear(int value) {
        if (isFull()) {
            throw overflow_error("Deque Overflow");
        }
        
        // If deque is empty
        if (isEmpty()) {
            front = rear = 0;
        } else {
            // Update rear
            rear = (rear + 1) % MAX_SIZE;
        }
        
        data[rear] = value;
        count++;
    }
    
    // Delete the front element
    int deleteFront() {
        if (isEmpty()) {
            throw underflow_error("Deque Underflow");
        }
        
        int value = data[front];
        
        // If deque has only one element
        if (front == rear) {
            front = -1;
            rear = 0;
        } else {
            // Update front
            front = (front + 1) % MAX_SIZE;
        }
        
        count--;
        return value;
    }
    
    // Delete the rear element
    int deleteRear() {
        if (isEmpty()) {
            throw underflow_error("Deque Underflow");
        }
        
        int value = data[rear];
        
        // If deque has only one element
        if (front == rear) {
            front = -1;
            rear = 0;
        } else {
            // Update rear
            rear = (rear - 1 + MAX_SIZE) % MAX_SIZE;
        }
        
        count--;
        return value;
    }
    
    // Get the front element
    int getFront() const {
        if (isEmpty()) {
            throw underflow_error("Deque is empty");
        }
        
        return data[front];
    }
    
    // Get the rear element
    int getRear() const {
        if (isEmpty()) {
            throw underflow_error("Deque is empty");
        }
        
        return data[rear];
    }
    
    // Get the number of elements in the deque
    int size() const {
        return count;
    }
    
    // Display all elements in the deque
    void display() const {
        if (isEmpty()) {
            cout << "Deque is empty" << endl;
            return;
        }
        
        cout << "Deque elements: ";
        int i = front;
        
        // Special handling for a single element
        if (count == 1) {
            cout << data[front] << endl;
            return;
        }
        
        // Traverse from front to rear
        while (i != rear) {
            cout << data[i] << " ";
            i = (i + 1) % MAX_SIZE;
        }
        
        // Print the last element
        cout << data[rear] << endl;
    }
}; 