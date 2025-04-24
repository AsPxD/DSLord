/**
 * DoublyLinkedList - A Doubly Linked List implementation
 * Operations:
 * - insertAtBeginning: Insert a node at the beginning of the list
 * - insertAtEnd: Insert a node at the end of the list
 * - insertAt: Insert a node at a specific position
 * - deleteNode: Delete a node with a specific value
 * - search: Search for a node with a specific value
 * - display: Display all nodes in the list (forward and backward)
 */
class DoublyLinkedList {
private:
    // Node structure for Doubly Linked List
    struct Node {
        int data;
        Node* next;
        Node* prev;
        
        // Constructor
        Node(int value) : data(value), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int nodeCount;

public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr), nodeCount(0) {}
    
    // Destructor to free memory
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }
    
    // Insert a node at the beginning of the list
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        
        // If list is empty
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        
        nodeCount++;
    }
    
    // Insert a node at the end of the list
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        
        // If list is empty
        if (tail == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        
        nodeCount++;
    }
    
    // Insert a node at a specific position (0-based indexing)
    void insertAt(int position, int value) {
        // Check if position is valid
        if (position < 0 || position > nodeCount) {
            throw out_of_range("Invalid position");
        }
        
        // Insert at beginning if position is 0
        if (position == 0) {
            insertAtBeginning(value);
            return;
        }
        
        // Insert at end if position is equal to nodeCount
        if (position == nodeCount) {
            insertAtEnd(value);
            return;
        }
        
        // Create new node
        Node* newNode = new Node(value);
        
        // Traverse to the position
        Node* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        
        // Link the new node
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        
        nodeCount++;
    }
    
    // Delete a node with a specific value
    bool deleteNode(int value) {
        // Check if list is empty
        if (head == nullptr) {
            return false;
        }
        
        // If head node has the value
        if (head->data == value) {
            Node* temp = head;
            
            // If only one node in the list
            if (head == tail) {
                head = nullptr;
                tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }
            
            delete temp;
            nodeCount--;
            return true;
        }
        
        // If tail node has the value
        if (tail->data == value) {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
            nodeCount--;
            return true;
        }
        
        // Traverse the list to find the node with the value
        Node* current = head->next;
        while (current != nullptr && current->data != value) {
            current = current->next;
        }
        
        // If node found, delete it
        if (current != nullptr) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            nodeCount--;
            return true;
        }
        
        return false; // Node not found
    }
    
    // Search for a node with a specific value
    bool search(int value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    
    // Get the number of nodes in the list
    int size() const {
        return nodeCount;
    }
    
    // Check if the list is empty
    bool isEmpty() const {
        return head == nullptr;
    }
    
    // Display all nodes in the list (forward)
    void displayForward() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        cout << "Doubly Linked List (forward): ";
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;
            current = current->next;
            if (current != nullptr) {
                cout << " <-> ";
            }
        }
        cout << endl;
    }
    
    // Display all nodes in the list (backward)
    void displayBackward() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        cout << "Doubly Linked List (backward): ";
        Node* current = tail;
        while (current != nullptr) {
            cout << current->data;
            current = current->prev;
            if (current != nullptr) {
                cout << " <-> ";
            }
        }
        cout << endl;
    }
    
    // Display all nodes in the list (both ways)
    void display() const {
        displayForward();
    }
}; 