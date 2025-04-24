/**
 * CircularLinkedList - A Circular Linked List implementation
 * Operations:
 * - insertAtBeginning: Insert a node at the beginning of the list
 * - insertAtEnd: Insert a node at the end of the list
 * - deleteNode: Delete a node with a specific value
 * - search: Search for a node with a specific value
 * - display: Display all nodes in the list
 */
class CircularLinkedList {
private:
    // Node structure for Circular Linked List
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
    CircularLinkedList() : head(nullptr), nodeCount(0) {}
    
    // Destructor to free memory
    ~CircularLinkedList() {
        if (head == nullptr) return;
        
        // Start at the head
        Node* current = head;
        Node* nextNode;
        
        // Free all nodes
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
        
        head = nullptr;
    }
    
    // Insert a node at the beginning of the list
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        
        // If list is empty
        if (head == nullptr) {
            head = newNode;
            newNode->next = head; // Point to itself
        } else {
            // Find the last node
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            
            // Update connections
            newNode->next = head;
            last->next = newNode;
            head = newNode;
        }
        
        nodeCount++;
    }
    
    // Insert a node at the end of the list
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        
        // If list is empty
        if (head == nullptr) {
            head = newNode;
            newNode->next = head; // Point to itself
        } else {
            // Find the last node
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            
            // Update connections
            last->next = newNode;
            newNode->next = head;
        }
        
        nodeCount++;
    }
    
    // Delete a node with a specific value
    bool deleteNode(int value) {
        // Check if list is empty
        if (head == nullptr) {
            return false;
        }
        
        // If only one node and it has the value
        if (head->next == head && head->data == value) {
            delete head;
            head = nullptr;
            nodeCount--;
            return true;
        }
        
        // If head node has the value
        if (head->data == value) {
            // Find the last node
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            
            Node* temp = head;
            head = head->next;
            last->next = head;
            delete temp;
            nodeCount--;
            return true;
        }
        
        // Search for the node with the value
        Node* current = head;
        while (current->next != head && current->next->data != value) {
            current = current->next;
        }
        
        // If found, delete it
        if (current->next != head) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            nodeCount--;
            return true;
        }
        
        return false; // Not found
    }
    
    // Search for a node with a specific value
    bool search(int value) const {
        // Check if list is empty
        if (head == nullptr) {
            return false;
        }
        
        // Check head
        if (head->data == value) {
            return true;
        }
        
        // Search other nodes
        Node* current = head->next;
        while (current != head) {
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
        
        cout << "Circular Linked List: ";
        
        Node* current = head;
        do {
            cout << current->data;
            current = current->next;
            if (current != head) {
                cout << " -> ";
            }
        } while (current != head);
        
        cout << " -> (back to first node)" << endl;
    }
}; 