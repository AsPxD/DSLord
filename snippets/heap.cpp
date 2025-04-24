/**
 * MinHeap - A Min Heap implementation
 * Operations:
 * - insert: Insert a value into the heap
 * - extractMin: Extract the minimum value from the heap
 * - getMin: Get the minimum value without removing it
 * - size: Get the number of elements in the heap
 * - isEmpty: Check if the heap is empty
 */
class MinHeap {
private:
    static const int MAX_SIZE = 1000;
    int heap[MAX_SIZE];
    int heapSize;
    
    // Get parent index
    int parent(int i) const {
        return (i - 1) / 2;
    }
    
    // Get left child index
    int leftChild(int i) const {
        return 2 * i + 1;
    }
    
    // Get right child index
    int rightChild(int i) const {
        return 2 * i + 2;
    }
    
    // Heapify up (bubble up)
    void heapifyUp(int i) {
        // While the node is not the root and smaller than its parent
        while (i > 0 && heap[i] < heap[parent(i)]) {
            // Swap with parent
            swap(heap[i], heap[parent(i)]);
            // Move up to parent
            i = parent(i);
        }
    }
    
    // Heapify down (bubble down)
    void heapifyDown(int i) {
        int smallest = i;
        int left = leftChild(i);
        int right = rightChild(i);
        
        // If left child is smaller than current smallest
        if (left < heapSize && heap[left] < heap[smallest]) {
            smallest = left;
        }
        
        // If right child is smaller than current smallest
        if (right < heapSize && heap[right] < heap[smallest]) {
            smallest = right;
        }
        
        // If smallest is not the current node
        if (smallest != i) {
            // Swap with smallest child
            swap(heap[i], heap[smallest]);
            // Recursively heapify down the affected subtree
            heapifyDown(smallest);
        }
    }

public:
    // Constructor
    MinHeap() : heapSize(0) {}
    
    // Insert a value into the heap
    void insert(int value) {
        if (heapSize >= MAX_SIZE) {
            throw overflow_error("Heap Overflow");
        }
        
        // Add the value at the end of the heap
        heap[heapSize] = value;
        
        // Restore the heap property by bubbling up
        heapifyUp(heapSize);
        
        // Increment heap size
        heapSize++;
    }
    
    // Extract the minimum value from the heap
    int extractMin() {
        if (isEmpty()) {
            throw underflow_error("Heap Underflow");
        }
        
        // Store the minimum value
        int minValue = heap[0];
        
        // Replace root with the last element
        heap[0] = heap[heapSize - 1];
        
        // Decrement heap size
        heapSize--;
        
        // Restore the heap property by bubbling down
        heapifyDown(0);
        
        return minValue;
    }
    
    // Get the minimum value without removing it
    int getMin() const {
        if (isEmpty()) {
            throw underflow_error("Heap is empty");
        }
        
        return heap[0];
    }
    
    // Get the number of elements in the heap
    int size() const {
        return heapSize;
    }
    
    // Check if the heap is empty
    bool isEmpty() const {
        return heapSize == 0;
    }
    
    // Display the heap (for debugging)
    void display() const {
        if (isEmpty()) {
            cout << "Heap is empty" << endl;
            return;
        }
        
        cout << "Heap elements: ";
        for (int i = 0; i < heapSize; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
}; 