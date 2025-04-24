/**
 * LinkedList - A Singly Linked List implementation
 * Operations:
 * - insertAtBeginning: Insert a node at the beginning of the list
 * - insertAtEnd: Insert a node at the end of the list
 * - insertAt: Insert a node at a specific position
 * - deleteNode: Delete a node with a specific value
 * - search: Search for a node with a specific value
 * - display: Display all nodes in the list
 */
class LinkedList {
private:
    // Node structure for Linked List
    struct Node {
        int data;
        Node* next;
        
        // Constructor
        Node(int value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    int nodeCount;

public:
    // Constructor
    LinkedList() : head(nullptr), nodeCount(0) {}
    
    // Destructor to free memory
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
    
    // Insert a node at the beginning of the list
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        nodeCount++;
    }
    
    // Insert a node at the end of the list
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        
        // If list is empty, make the new node the head
        if (head == nullptr) {
            head = newNode;
            nodeCount++;
            return;
        }
        
        // Traverse to the end of the list
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        
        // Link the new node
        current->next = newNode;
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
        
        // Create new node
        Node* newNode = new Node(value);
        
        // Traverse to the position
        Node* current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }
        
        // Link the new node
        newNode->next = current->next;
        current->next = newNode;
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
            head = head->next;
            delete temp;
            nodeCount--;
            return true;
        }
        
        // Traverse the list to find the node with the value
        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }
        
        // If node found, delete it
        if (current->next != nullptr) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
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
    
    // Display all nodes in the list
    void display() const {
        if (isEmpty()) {
            cout << "List is empty" << endl;
            return;
        }
        
        cout << "Linked List elements: ";
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;
            current = current->next;
            if (current != nullptr) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}; 