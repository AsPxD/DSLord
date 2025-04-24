/**
 * BinarySearchTree - A Binary Search Tree implementation
 * Operations:
 * - insert: Insert a value
 * - remove: Remove a value
 * - search: Search for a value
 * - inorderTraversal: Traverse the tree in-order
 * - preorderTraversal: Traverse the tree pre-order
 * - postorderTraversal: Traverse the tree post-order
 * - getMin: Get the minimum value
 * - getMax: Get the maximum value
 * - getHeight: Get the height of the tree
 * - getSize: Get the number of nodes in the tree
 */
class BinarySearchTree {
private:
    // Node structure for BST
    struct Node {
        int data;
        Node* left;
        Node* right;
        
        // Constructor
        Node(int value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    int nodeCount;
    
    // Helper function to insert a value recursively
    Node* insertRecursive(Node* node, int value) {
        // Base case: empty tree or reached leaf node
        if (node == nullptr) {
            nodeCount++;
            return new Node(value);
        }
        
        // Recursive case: traverse the tree
        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }
        // If value already exists, don't insert
        
        return node;
    }
    
    // Helper function to find the minimum value node
    Node* findMin(Node* node) const {
        // The leftmost node has the minimum value
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    // Helper function to remove a value recursively
    Node* removeRecursive(Node* node, int value) {
        // Base case: empty tree
        if (node == nullptr) {
            return nullptr;
        }
        
        // Recursive case: traverse the tree
        if (value < node->data) {
            node->left = removeRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = removeRecursive(node->right, value);
        } else {
            // Found the node to remove
            
            // Case 1: Node has no children (leaf node)
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                nodeCount--;
                return nullptr;
            }
            // Case 2: Node has only one child
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                nodeCount--;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                nodeCount--;
                return temp;
            }
            // Case 3: Node has two children
            else {
                // Find the inorder successor (minimum in right subtree)
                Node* successor = findMin(node->right);
                
                // Copy the successor's data to this node
                node->data = successor->data;
                
                // Delete the successor
                node->right = removeRecursive(node->right, successor->data);
            }
        }
        
        return node;
    }
    
    // Helper function to search for a value recursively
    bool searchRecursive(Node* node, int value) const {
        // Base case: empty tree or found the value
        if (node == nullptr) {
            return false;
        }
        
        if (node->data == value) {
            return true;
        }
        
        // Recursive case: traverse the tree
        if (value < node->data) {
            return searchRecursive(node->left, value);
        } else {
            return searchRecursive(node->right, value);
        }
    }
    
    // Helper function for in-order traversal
    void inorderRecursive(Node* node) const {
        if (node != nullptr) {
            inorderRecursive(node->left);
            cout << node->data << " ";
            inorderRecursive(node->right);
        }
    }
    
    // Helper function for pre-order traversal
    void preorderRecursive(Node* node) const {
        if (node != nullptr) {
            cout << node->data << " ";
            preorderRecursive(node->left);
            preorderRecursive(node->right);
        }
    }
    
    // Helper function for post-order traversal
    void postorderRecursive(Node* node) const {
        if (node != nullptr) {
            postorderRecursive(node->left);
            postorderRecursive(node->right);
            cout << node->data << " ";
        }
    }
    
    // Helper function to get the height of the tree
    int getHeightRecursive(Node* node) const {
        if (node == nullptr) {
            return -1; // Height of empty tree is -1
        }
        
        int leftHeight = getHeightRecursive(node->left);
        int rightHeight = getHeightRecursive(node->right);
        
        return 1 + max(leftHeight, rightHeight);
    }
    
    // Helper function to free all nodes
    void destroyRecursive(Node* node) {
        if (node != nullptr) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }

public:
    // Constructor
    BinarySearchTree() : root(nullptr), nodeCount(0) {}
    
    // Destructor
    ~BinarySearchTree() {
        destroyRecursive(root);
        root = nullptr;
    }
    
    // Insert a value
    void insert(int value) {
        root = insertRecursive(root, value);
    }
    
    // Remove a value
    bool remove(int value) {
        int prevCount = nodeCount;
        root = removeRecursive(root, value);
        return prevCount > nodeCount;
    }
    
    // Search for a value
    bool search(int value) const {
        return searchRecursive(root, value);
    }
    
    // In-order traversal
    void inorderTraversal() const {
        if (isEmpty()) {
            cout << "Tree is empty" << endl;
            return;
        }
        
        cout << "In-order traversal: ";
        inorderRecursive(root);
        cout << endl;
    }
    
    // Pre-order traversal
    void preorderTraversal() const {
        if (isEmpty()) {
            cout << "Tree is empty" << endl;
            return;
        }
        
        cout << "Pre-order traversal: ";
        preorderRecursive(root);
        cout << endl;
    }
    
    // Post-order traversal
    void postorderTraversal() const {
        if (isEmpty()) {
            cout << "Tree is empty" << endl;
            return;
        }
        
        cout << "Post-order traversal: ";
        postorderRecursive(root);
        cout << endl;
    }
    
    // Get the minimum value
    bool getMin(int& value) const {
        if (isEmpty()) {
            return false;
        }
        
        Node* minNode = findMin(root);
        value = minNode->data;
        return true;
    }
    
    // Get the maximum value
    bool getMax(int& value) const {
        if (isEmpty()) {
            return false;
        }
        
        // The rightmost node has the maximum value
        Node* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        
        value = current->data;
        return true;
    }
    
    // Get the height of the tree
    int getHeight() const {
        return getHeightRecursive(root);
    }
    
    // Get the number of nodes in the tree
    int getSize() const {
        return nodeCount;
    }
    
    // Check if the tree is empty
    bool isEmpty() const {
        return root == nullptr;
    }
    
    // Display the tree (in-order traversal)
    void display() const {
        inorderTraversal();
    }
}; 