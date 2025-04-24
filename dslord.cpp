/**
 * DSLord - Professional Data Structure Generator
 * 
 * The ultimate developer tool for generating production-ready
 * data structure implementations with a single command.
 * 
 * Version: 2.1.0
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>
#include <set>
#include <sstream>
#include <ctime>

using namespace std;

// ANSI color codes for terminal output
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"
#define COLOR_BOLD    "\033[1m"

// Structure to hold data structure information
struct DataStructureInfo {
    string name;
    string displayName;
    string description;
    string flag;
    string category;
};

// Function declarations
void printHeader();
void printHelp();
void printAvailableDataStructures(const vector<DataStructureInfo>& dataStructures);
bool readDataStructureContent(const string& ds_name, vector<string>& content);
void generateFile(const string& output_file, const vector<DataStructureInfo>& dataStructures, 
                 const vector<string>& selectedDS);
void generateExampleCode(ofstream& out_file, const vector<string>& selectedDS, 
                        const vector<DataStructureInfo>& dataStructures);
string getFormattedDateTime();
string getProgramName(char* programPath);
void printSuccess(const string& output_file, int count);
void printFooter();

int main(int argc, char* argv[]) {
    // Set up data structure information with categories
    vector<DataStructureInfo> dataStructures = {
        // Linear Data Structures
        {"stack", "Stack", "Last-In-First-Out (LIFO) data structure", "-stack", "Linear"},
        {"queue", "Queue", "First-In-First-Out (FIFO) data structure", "-queue", "Linear"},
        {"deque", "Deque", "Double-ended Queue implementation", "-deque", "Linear"},
        {"array", "Dynamic Array", "Dynamic Array implementation (similar to C++ vector)", "-array", "Linear"},
        
        // Linked Data Structures
        {"linkedlist", "Linked List", "Singly Linked List implementation", "-linkedlist", "Linked"},
        {"doublylinkedlist", "Doubly Linked List", "Bi-directional linked nodes", "-doublylinkedlist", "Linked"},
        {"circularlist", "Circular Linked List", "Circular chain of linked nodes", "-circularlist", "Linked"},
        
        // Tree Data Structures
        {"bst", "Binary Search Tree", "Ordered binary tree implementation", "-bst", "Tree"},
        {"heap", "Min Heap", "Complete binary tree with heap property", "-heap", "Tree"},
        
        // Hash-based Data Structures
        {"hashtable", "Hash Table", "Key-value pairs with O(1) access time", "-hashtable", "Hash-based"}
    };
    
    // Get program name for help display
    string programName = getProgramName(argv[0]);
    
    // Display header
    printHeader();
    
    // Check for help flag
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-h" || arg == "--help" || arg == "-help") {
            printHelp();
            printAvailableDataStructures(dataStructures);
            printFooter();
            return 0;
        }
    }
    
    // Check command-line arguments
    if (argc < 2) {
        cout << COLOR_RED << "ERROR: " << COLOR_RESET << "Not enough arguments.\n";
        cout << "Use " << COLOR_BOLD << programName << " --help" << COLOR_RESET << " for usage information.\n";
        printFooter();
        return 1;
    }
    
    string output_file = argv[1];
    
    // Process command line flags
    vector<string> selectedDS;
    
    // Map to track invalid flags
    map<string, bool> validFlags;
    for (const auto& ds : dataStructures) {
        validFlags[ds.flag] = true;
    }
    
    for (int i = 2; i < argc; i++) {
        string arg = argv[i];
        
        // Handle "all" flag specially
        if (arg == "-all") {
            for (const auto& ds : dataStructures) {
                selectedDS.push_back(ds.name);
            }
            break;
        }
        
        // Skip if it's not a flag
        if (arg.empty() || arg[0] != '-') {
            continue;
        }
        
        bool found = false;
        for (const auto& ds : dataStructures) {
            if (arg == ds.flag) {
                selectedDS.push_back(ds.name);
                found = true;
                break;
            }
        }
        
        if (!found && !validFlags[arg]) {
            cout << COLOR_YELLOW << "WARNING: " << COLOR_RESET << "Unknown flag: " << arg << endl;
        }
    }
    
    // Generate the file if at least one data structure was selected
    if (!selectedDS.empty()) {
        generateFile(output_file, dataStructures, selectedDS);
        printSuccess(output_file, selectedDS.size());
    } else {
        cout << COLOR_RED << "ERROR: " << COLOR_RESET << "No data structures were selected. Use flags like -stack, -queue, etc.\n";
        cout << "Use " << COLOR_BOLD << programName << " --help" << COLOR_RESET << " to see available options.\n";
        printFooter();
        return 1;
    }
    
    printFooter();
    return 0;
}

/**
 * Display application header
 */
void printHeader() {
    cout << COLOR_BOLD << COLOR_CYAN;
    cout << "+--------------------------------------------------------------+" << endl;
    cout << "|                          DSLORD                              |" << endl;
    cout << "|  Generate professional data structures with a single command |" << endl;
    cout << "+--------------------------------------------------------------+" << endl;
    cout << COLOR_RESET << endl;
}

/**
 * Display application footer
 */
void printFooter() {
    cout << endl << COLOR_CYAN;
    cout << "================================================================" << endl;
    cout << "               Thank you for using DSLord!                      " << endl;
    cout << "================================================================" << endl;
    cout << COLOR_RESET << endl;
}

/**
 * Display help information
 */
void printHelp() {
    cout << COLOR_BOLD << "USAGE:" << COLOR_RESET << endl;
    cout << "  dslord <output_file> [-datastructure1] [-datastructure2] ... [-all]" << endl << endl;
    
    cout << COLOR_BOLD << "EXAMPLES:" << COLOR_RESET << endl;
    cout << "  dslord mycode.cpp -stack -linkedlist" << endl;
    cout << "  dslord datastructures.cpp -queue -bst -heap" << endl;
    cout << "  dslord complete.cpp -all              " << COLOR_CYAN << "# Generate all data structures" << COLOR_RESET << endl << endl;
    
    cout << COLOR_BOLD << "FLAGS:" << COLOR_RESET << endl;
    cout << "  -h, --help   : Display this help information" << endl;
    cout << "  -all         : Include all available data structures" << endl << endl;
}

/**
 * Display available data structures
 */
void printAvailableDataStructures(const vector<DataStructureInfo>& dataStructures) {
    cout << COLOR_BOLD << "AVAILABLE DATA STRUCTURES:" << COLOR_RESET << endl;
    
    // Group by category
    map<string, vector<DataStructureInfo>> categorized;
    for (const auto& ds : dataStructures) {
        categorized[ds.category].push_back(ds);
    }
    
    // Print each category
    for (const auto& category : categorized) {
        cout << endl << COLOR_BOLD << COLOR_MAGENTA << "  " << category.first << " Data Structures:" << COLOR_RESET << endl;
        cout << "  " << setw(20) << left << "FLAG" << setw(25) << "NAME" << "DESCRIPTION" << endl;
        cout << "  " << string(75, '-') << endl;
        
        for (const auto& ds : category.second) {
            cout << "  " << COLOR_CYAN << setw(20) << left << ds.flag << COLOR_RESET;
            cout << setw(25) << ds.displayName;
            cout << ds.description << endl;
        }
    }
    cout << endl;
}

/**
 * Read data structure content from file
 */
bool readDataStructureContent(const string& ds_name, vector<string>& content) {
    string path = "snippets/" + ds_name + ".cpp";
    ifstream file(path);

    if (!file) {
        cout << COLOR_RED << "ERROR: " << COLOR_RESET << "Code for " << ds_name << " not found at " << path << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        // Skip include and namespace lines - we'll add them at the top once
        if (line.find("#include") != string::npos || 
            line.find("using namespace") != string::npos || 
            line.empty()) {
            continue;
        }
        content.push_back(line);
    }

    file.close();
    return true;
}

/**
 * Generate the output file with the selected data structures
 */
void generateFile(const string& output_file, const vector<DataStructureInfo>& dataStructures, 
                const vector<string>& selectedDS) {
    // Attempt to open the output file
    ofstream out(output_file);
    if (!out) {
        cout << COLOR_RED << "ERROR: " << COLOR_RESET << "Failed to open output file: " << output_file << endl;
        return;
    }
    
    // Content for each data structure
    map<string, vector<string>> dsContent;
    
    // Collect content for all selected data structures
    cout << COLOR_CYAN << "\nReading data structure implementations..." << COLOR_RESET << endl;
    for (const auto& ds : selectedDS) {
        vector<string> content;
        if (readDataStructureContent(ds, content)) {
            dsContent[ds] = content;
            cout << "  " << COLOR_GREEN << "✓" << COLOR_RESET << " " << ds << endl;
        }
    }
    
    // Generate the file header
    out << "/**\n";
    out << " * Data Structures Implementation\n";
    out << " * Generated with DSLord\n";
    out << " * Date: " << getFormattedDateTime() << "\n";
    out << " *\n";
    out << " * Contains:\n";
    
    for (const auto& ds : selectedDS) {
        // Find the display name for this data structure
        string displayName = ds; // default
        for (const auto& info : dataStructures) {
            if (info.name == ds) {
                displayName = info.displayName;
                break;
            }
        }
        out << " * - " << displayName << "\n";
    }
    out << " */\n\n";
    
    // Add standard includes
    out << "#include <iostream>\n";
    out << "#include <string>\n";
    out << "#include <stdexcept>\n";
    out << "#include <algorithm>\n";
    
    // Add using namespace statement
    out << "using namespace std;\n\n";
    
    // Add all data structure implementations
    cout << COLOR_CYAN << "\nWriting data structures to file..." << COLOR_RESET << endl;
    for (const auto& ds : selectedDS) {
        if (dsContent.find(ds) != dsContent.end()) {
            // Find the display name for this data structure
            string displayName = ds; // default
            for (const auto& info : dataStructures) {
                if (info.name == ds) {
                    displayName = info.displayName;
                    cout << "  " << COLOR_GREEN << "✓" << COLOR_RESET << " Adding " << displayName << endl;
                    break;
                }
            }
            
            // Add the content
            for (const auto& line : dsContent[ds]) {
                out << line << endl;
            }
            out << endl; // Add a blank line between implementations
        }
    }
    
    // Add example usage code
    generateExampleCode(out, selectedDS, dataStructures);
    
    out.close();
    cout << COLOR_GREEN << "\nAll data structures successfully written to " << output_file << COLOR_RESET << endl;
}

/**
 * Generate example usage code
 */
void generateExampleCode(ofstream& out_file, const vector<string>& selectedDS, 
                        const vector<DataStructureInfo>& dataStructures) {
    out_file << "/**\n";
    out_file << " * Example usage of implemented data structures\n";
    out_file << " */\n";
    out_file << "int main() {\n";
    out_file << "    cout << \"+----------------------------------------------+\" << endl;\n";
    out_file << "    cout << \"|  Data Structures Implementation Example     |\" << endl;\n";
    out_file << "    cout << \"+----------------------------------------------+\" << endl << endl;\n";
    
    // Group data structures by category for better example organization
    map<string, vector<string>> categorizedDS;
    
    for (const auto& ds : selectedDS) {
        // Find the category for this data structure
        for (const auto& info : dataStructures) {
            if (info.name == ds) {
                categorizedDS[info.category].push_back(ds);
                break;
            }
        }
    }
    
    // Generate examples for each category
    for (const auto& category : categorizedDS) {
        out_file << "    // " << category.first << " Data Structures Examples\n";
        out_file << "    cout << \"\\n" << category.first << " Data Structures:\" << endl;\n";
        out_file << "    cout << \"" << string(category.first.length() + 16, '-') << "\" << endl;\n\n";
        
        for (const auto& ds : category.second) {
            string displayName = ds;
            string className = "";
            string varName = ds;
            
            // Find the display name for prettier output
            for (const auto& info : dataStructures) {
                if (info.name == ds) {
                    displayName = info.displayName;
                    break;
                }
            }
            
            // Use the actual class name (which might have spaces in the display name)
            // For actual class name in code, remove spaces
            className = displayName;
            className.erase(remove(className.begin(), className.end(), ' '), className.end());
            
            // Clean up variable name: remove spaces, underscores
            varName.erase(remove(varName.begin(), varName.end(), ' '), varName.end());
            varName.erase(remove(varName.begin(), varName.end(), '_'), varName.end());
            // Convert first letter to lowercase
            if (!varName.empty()) {
                varName[0] = tolower(varName[0]);
            }
            
            // Generate example code based on data structure type
            out_file << "    // " << displayName << " example:\n";
            out_file << "    cout << \"\\n" << displayName << " operations:\" << endl;\n";
            out_file << "    " << className << " " << varName << ";\n";
            
            if (ds == "stack") {
                out_file << "    " << varName << ".push(10);\n";
                out_file << "    " << varName << ".push(20);\n";
                out_file << "    " << varName << ".push(30);\n";
                out_file << "    cout << \"Top element: \" << " << varName << ".top() << endl;\n";
                out_file << "    " << varName << ".display();\n";
                out_file << "    cout << \"Pop: \" << " << varName << ".pop() << endl;\n";
                out_file << "    " << varName << ".display();\n";
            } 
            else if (ds == "queue") {
                out_file << "    " << varName << ".enqueue(10);\n";
                out_file << "    " << varName << ".enqueue(20);\n";
                out_file << "    " << varName << ".enqueue(30);\n";
                out_file << "    cout << \"Front element: \" << " << varName << ".front() << endl;\n";
                out_file << "    " << varName << ".display();\n";
                out_file << "    cout << \"Dequeue: \" << " << varName << ".dequeue() << endl;\n";
                out_file << "    " << varName << ".display();\n";
            }
            else if (ds == "linkedlist" || ds == "doublylinkedlist" || ds == "circularlist") {
                out_file << "    " << varName << ".insertAtBeginning(30);\n";
                out_file << "    " << varName << ".insertAtBeginning(20);\n";
                out_file << "    " << varName << ".insertAtEnd(40);\n";
                out_file << "    " << varName << ".display();\n";
                out_file << "    cout << \"Deleting 20: \" << (" << varName << ".deleteNode(20) ? \"Success\" : \"Not found\") << endl;\n";
                out_file << "    " << varName << ".display();\n";
            }
            else if (ds == "bst") {
                out_file << "    " << varName << ".insert(50);\n";
                out_file << "    " << varName << ".insert(30);\n";
                out_file << "    " << varName << ".insert(70);\n";
                out_file << "    " << varName << ".insert(20);\n";
                out_file << "    " << varName << ".insert(40);\n";
                out_file << "    cout << \"Inorder traversal: \";\n";
                out_file << "    " << varName << ".inorderTraversal();\n";
                out_file << "    cout << \"Removing 30: \" << (" << varName << ".remove(30) ? \"Success\" : \"Not found\") << endl;\n";
                out_file << "    " << varName << ".inorderTraversal();\n";
            }
            else if (ds == "heap") {
                out_file << "    " << varName << ".insert(30);\n";
                out_file << "    " << varName << ".insert(10);\n";
                out_file << "    " << varName << ".insert(20);\n";
                out_file << "    " << varName << ".insert(5);\n";
                out_file << "    " << varName << ".display();\n";
                out_file << "    cout << \"Min element: \" << " << varName << ".getMin() << endl;\n";
                out_file << "    cout << \"Extracting min: \" << " << varName << ".extractMin() << endl;\n";
                out_file << "    " << varName << ".display();\n";
            }
            else if (ds == "hashtable") {
                out_file << "    " << varName << ".insert(1, 100);\n";
                out_file << "    " << varName << ".insert(2, 200);\n";
                out_file << "    " << varName << ".insert(3, 300);\n";
                out_file << "    int value;\n";
                out_file << "    if (" << varName << ".get(2, value)) {\n";
                out_file << "        cout << \"Value for key 2: \" << value << endl;\n";
                out_file << "    }\n";
                out_file << "    " << varName << ".display();\n";
                out_file << "    cout << \"Removing key 2: \" << (" << varName << ".remove(2) ? \"Success\" : \"Not found\") << endl;\n";
                out_file << "    " << varName << ".display();\n";
            }
            else if (ds == "deque") {
                out_file << "    " << varName << ".insertRear(10);\n";
                out_file << "    " << varName << ".insertFront(5);\n";
                out_file << "    " << varName << ".insertRear(20);\n";
                out_file << "    " << varName << ".display();\n";
                out_file << "    cout << \"Front: \" << " << varName << ".getFront() << \", Rear: \" << " << varName << ".getRear() << endl;\n";
                out_file << "    cout << \"Deleting from front: \" << " << varName << ".deleteFront() << endl;\n";
                out_file << "    " << varName << ".display();\n";
            }
            else if (ds == "array") {
                out_file << "    " << varName << ".pushBack(10);\n";
                out_file << "    " << varName << ".pushBack(20);\n";
                out_file << "    " << varName << ".pushBack(30);\n";
                out_file << "    " << varName << ".insert(1, 15);\n";
                out_file << "    " << varName << ".display();\n";
                out_file << "    cout << \"Element at position 2: \" << " << varName << ".get(2) << endl;\n";
                out_file << "    " << varName << ".removeAt(1);\n";
                out_file << "    " << varName << ".display();\n";
            }
            else {
                out_file << "    // Add example usage for " << displayName << " here\n";
                out_file << "    " << varName << ".display();\n";
            }
            
            out_file << "\n";
        }
    }
    
    out_file << "    cout << \"\\nAll data structures implemented successfully!\" << endl;\n";
    out_file << "    return 0;\n";
    out_file << "}\n";
}

/**
 * Extract program name from path
 */
string getProgramName(char* programPath) {
    string path(programPath);
    size_t lastSlash = path.find_last_of("/\\");
    if (lastSlash != string::npos) {
        return path.substr(lastSlash + 1);
    }
    return path;
}

/**
 * Get current date and time as formatted string
 */
string getFormattedDateTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    ostringstream oss;
    oss << 1900 + ltm->tm_year << "-" 
        << setw(2) << setfill('0') << 1 + ltm->tm_mon << "-"
        << setw(2) << setfill('0') << ltm->tm_mday << " "
        << setw(2) << setfill('0') << ltm->tm_hour << ":"
        << setw(2) << setfill('0') << ltm->tm_min;
    
    return oss.str();
}

/**
 * Print success message with statistics
 */
void printSuccess(const string& output_file, int count) {
    cout << endl << COLOR_GREEN << COLOR_BOLD << "SUCCESS!" << COLOR_RESET << COLOR_GREEN << endl;
    cout << "+-----------------------------------------------------+" << endl;
    cout << "| " << setw(51) << left << "Output file generated:" << "|" << endl;
    cout << "| " << setw(51) << output_file << "|" << endl;
    cout << "+-----------------------------------------------------+" << endl;
    cout << "| " << setw(51) << left << "Data structures included: " + to_string(count) << "|" << endl;
    cout << "+-----------------------------------------------------+" << COLOR_RESET << endl;
}