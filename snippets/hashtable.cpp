/**
 * HashTable - A Hash Table implementation using separate chaining
 * Operations:
 * - insert: Insert a key-value pair
 * - remove: Remove a key
 * - get: Get a value by key
 * - containsKey: Check if a key exists
 * - size: Get the number of key-value pairs
 * - isEmpty: Check if the hash table is empty
 */
class HashTable {
private:
    // Node structure for each key-value pair
    struct Node {
        int key;
        int value;
        Node* next;
        
        // Constructor
        Node(int k, int v) : key(k), value(v), next(nullptr) {}
    };
    
    static const int INITIAL_CAPACITY = 16;
    static const int MAX_LOAD_FACTOR = 75; // 75% load factor threshold
    
    Node** buckets;
    int numBuckets;
    int count;
    
    // Hash function
    int hash(int key) const {
        return abs(key) % numBuckets;
    }
    
    // Resize the hash table
    void resize(int newCapacity) {
        // Create new bucket array
        Node** newBuckets = new Node*[newCapacity];
        
        // Initialize new buckets
        for (int i = 0; i < newCapacity; i++) {
            newBuckets[i] = nullptr;
        }
        
        // Rehash existing key-value pairs
        for (int i = 0; i < numBuckets; i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                Node* next = current->next;
                
                // Compute new bucket index
                int newIndex = abs(current->key) % newCapacity;
                
                // Insert at beginning of new chain
                current->next = newBuckets[newIndex];
                newBuckets[newIndex] = current;
                
                current = next;
            }
        }
        
        // Update hash table
        delete[] buckets;
        buckets = newBuckets;
        numBuckets = newCapacity;
    }

public:
    // Constructor
    HashTable() : numBuckets(INITIAL_CAPACITY), count(0) {
        buckets = new Node*[numBuckets];
        for (int i = 0; i < numBuckets; i++) {
            buckets[i] = nullptr;
        }
    }
    
    // Destructor
    ~HashTable() {
        // Free all nodes
        for (int i = 0; i < numBuckets; i++) {
            Node* current = buckets[i];
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
        
        // Free bucket array
        delete[] buckets;
    }
    
    // Insert a key-value pair
    void insert(int key, int value) {
        // Check if resize is needed
        if (count >= numBuckets * MAX_LOAD_FACTOR / 100) {
            resize(numBuckets * 2);
        }
        
        int index = hash(key);
        
        // Check if key already exists
        Node* current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value; // Update value
                return;
            }
            current = current->next;
        }
        
        // Insert new node at beginning of chain
        Node* newNode = new Node(key, value);
        newNode->next = buckets[index];
        buckets[index] = newNode;
        count++;
    }
    
    // Remove a key
    bool remove(int key) {
        int index = hash(key);
        
        // Check if bucket is empty
        if (buckets[index] == nullptr) {
            return false;
        }
        
        // If key is in first node
        if (buckets[index]->key == key) {
            Node* temp = buckets[index];
            buckets[index] = buckets[index]->next;
            delete temp;
            count--;
            return true;
        }
        
        // Search for key in chain
        Node* current = buckets[index];
        while (current->next != nullptr && current->next->key != key) {
            current = current->next;
        }
        
        // If key found, remove it
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            count--;
            return true;
        }
        
        return false; // Key not found
    }
    
    // Get a value by key
    bool get(int key, int& value) const {
        int index = hash(key);
        
        // Search for key in chain
        Node* current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        
        return false; // Key not found
    }
    
    // Check if a key exists
    bool containsKey(int key) const {
        int index = hash(key);
        
        // Search for key in chain
        Node* current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        
        return false; // Key not found
    }
    
    // Get the number of key-value pairs
    int size() const {
        return count;
    }
    
    // Check if the hash table is empty
    bool isEmpty() const {
        return count == 0;
    }
    
    // Display the hash table (for debugging)
    void display() const {
        if (isEmpty()) {
            cout << "Hash table is empty" << endl;
            return;
        }
        
        cout << "Hash Table Contents:" << endl;
        for (int i = 0; i < numBuckets; i++) {
            cout << "Bucket " << i << ": ";
            
            Node* current = buckets[i];
            if (current == nullptr) {
                cout << "Empty";
            }
            
            while (current != nullptr) {
                cout << "[" << current->key << ":" << current->value << "]";
                current = current->next;
                if (current != nullptr) {
                    cout << " -> ";
                }
            }
            
            cout << endl;
        }
    }
}; 