/**
 * DynamicArray - A Dynamic Array implementation (similar to C++ vector)
 * Operations:
 * - pushBack: Add an element to the end of the array
 * - popBack: Remove the last element
 * - insert: Insert an element at a specific position
 * - removeAt: Remove an element at a specific position
 * - get: Get the element at a specific position
 * - set: Set the element at a specific position
 * - size: Get the number of elements in the array
 * - capacity: Get the current capacity of the array
 * - isEmpty: Check if the array is empty
 * - clear: Remove all elements
 */
class DynamicArray {
private:
    int* data;
    int arraySize;
    int arrayCapacity;
    
    // Resize the array when needed
    void resize(int newCapacity) {
        // Allocate new larger array
        int* newData = new int[newCapacity];
        
        // Copy elements from old array to new array
        for (int i = 0; i < arraySize; i++) {
            newData[i] = data[i];
        }
        
        // Free old array
        delete[] data;
        
        // Update array data and capacity
        data = newData;
        arrayCapacity = newCapacity;
    }

public:
    // Constructor
    DynamicArray(int initialCapacity = 10) : arraySize(0), arrayCapacity(initialCapacity) {
        if (initialCapacity <= 0) {
            initialCapacity = 10;
        }
        
        data = new int[initialCapacity];
    }
    
    // Destructor
    ~DynamicArray() {
        delete[] data;
    }
    
    // Copy constructor
    DynamicArray(const DynamicArray& other) : arraySize(other.arraySize), arrayCapacity(other.arrayCapacity) {
        data = new int[arrayCapacity];
        
        for (int i = 0; i < arraySize; i++) {
            data[i] = other.data[i];
        }
    }
    
    // Assignment operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            // Free existing resources
            delete[] data;
            
            // Copy from other
            arraySize = other.arraySize;
            arrayCapacity = other.arrayCapacity;
            data = new int[arrayCapacity];
            
            for (int i = 0; i < arraySize; i++) {
                data[i] = other.data[i];
            }
        }
        
        return *this;
    }
    
    // Add an element to the end of the array
    void pushBack(int value) {
        // Check if resize is needed
        if (arraySize >= arrayCapacity) {
            resize(arrayCapacity * 2);
        }
        
        // Add the element
        data[arraySize++] = value;
    }
    
    // Remove the last element
    void popBack() {
        if (isEmpty()) {
            throw underflow_error("Array is empty");
        }
        
        arraySize--;
        
        // Optionally shrink the array if it gets too empty
        if (arraySize > 0 && arraySize <= arrayCapacity / 4) {
            resize(arrayCapacity / 2);
        }
    }
    
    // Insert an element at a specific position
    void insert(int position, int value) {
        // Check if position is valid
        if (position < 0 || position > arraySize) {
            throw out_of_range("Invalid position");
        }
        
        // Check if resize is needed
        if (arraySize >= arrayCapacity) {
            resize(arrayCapacity * 2);
        }
        
        // Shift elements to the right
        for (int i = arraySize; i > position; i--) {
            data[i] = data[i - 1];
        }
        
        // Insert the element
        data[position] = value;
        arraySize++;
    }
    
    // Remove an element at a specific position
    void removeAt(int position) {
        // Check if position is valid
        if (position < 0 || position >= arraySize) {
            throw out_of_range("Invalid position");
        }
        
        // Shift elements to the left
        for (int i = position; i < arraySize - 1; i++) {
            data[i] = data[i + 1];
        }
        
        arraySize--;
        
        // Optionally shrink the array if it gets too empty
        if (arraySize > 0 && arraySize <= arrayCapacity / 4) {
            resize(arrayCapacity / 2);
        }
    }
    
    // Get the element at a specific position
    int get(int position) const {
        // Check if position is valid
        if (position < 0 || position >= arraySize) {
            throw out_of_range("Invalid position");
        }
        
        return data[position];
    }
    
    // Set the element at a specific position
    void set(int position, int value) {
        // Check if position is valid
        if (position < 0 || position >= arraySize) {
            throw out_of_range("Invalid position");
        }
        
        data[position] = value;
    }
    
    // Get the number of elements in the array
    int size() const {
        return arraySize;
    }
    
    // Get the current capacity of the array
    int capacity() const {
        return arrayCapacity;
    }
    
    // Check if the array is empty
    bool isEmpty() const {
        return arraySize == 0;
    }
    
    // Remove all elements
    void clear() {
        arraySize = 0;
        
        // Optionally shrink the array
        if (arrayCapacity > 10) {
            resize(10);
        }
    }
    
    // Display the array (for debugging)
    void display() const {
        if (isEmpty()) {
            cout << "Array is empty" << endl;
            return;
        }
        
        cout << "Array elements: ";
        for (int i = 0; i < arraySize; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
}; 