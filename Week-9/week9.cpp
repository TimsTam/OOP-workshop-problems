#include <iostream>
#include <memory>
#include <cstring> //memset
#include <cstdlib> //rand
#include <climits>

using namespace std;

template <typename T>
class Node {
private:
    T key;

public:
    // Array to hold pointers to node of different level
    Node **forward;
    Node(T, int);
    T getKey() const { return key; }
    ~Node()
    {
        std::cout << "key " << key << " destroyed.\n";
    }
};

template <typename T>
Node<T>::Node(T key, int level) {
    this->key = key;
    // Allocate memory to forward
    forward = new Node *[level + 1];
    // Fill forward array with 0(NULL)
    memset(forward, 0, sizeof(Node *) * (level + 1));
};

template <typename T>
class SkipList {
    // Maximum level for this skip list
    int MAXLVL;
    float P = 0.5;
    // current level of skip list
    int level;
    // pointer to header node
    Node<T> *header;

public:
    SkipList(int, float);
    bool searchElement(T);
    void insertElement(T, int=-1);
    void deleteElement(T);
    void displayList();
    int randomLevel();

    ~SkipList()
    {
        std::cout << "skip list destroyed.\n";
    }
};

template <typename T>
SkipList<T>::SkipList(int MAXLVL, float P) {
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;
    // create header node and initialize key to -1
    header = new Node<T>(INT_MIN, MAXLVL);
};

// create random level for node
template <typename T>
int SkipList<T>::randomLevel() {
    float r = (float)rand() / RAND_MAX;
    int lvl = 0;
    while (r < P && lvl < MAXLVL)
    {
        lvl++;
        r = (float)rand() / RAND_MAX;
    }
    return lvl;
};

template <typename T>
bool SkipList<T>::searchElement(T key) {
    auto *current = header;
    std::cout<<"Search Path:"<<std::endl;
    for (int i = MAXLVL-1; i >= 0; i--)
    {
        cout << "(Level:" << i << ",node:" << current->getKey() << ")" << endl;
        while (current->forward[i] && current->forward[i]->getKey() < key)
        {
            cout << "(Level:" << i << ",node:" << current->forward[i]->getKey() << ")" << endl;
            current = current->forward[i];
        }
    }
    current = current->forward[0];
    cout << "(Level:0" << ",node:" << current->getKey() << ")" << endl;
    
    if (current && current->getKey() == key)
    {
        return true;
    }
    else
    {
        return false;
    }
};

template <typename T>
void SkipList<T>::insertElement(T key, int level) {
    auto *current = header; // Set the current node to the header node

    // create update array and initialize it
    Node<T> *update[MAXLVL + 1]; // Array to store nodes to update
    std::memset(update, 0, sizeof(Node<T> *) * (MAXLVL + 1)); // Initialize update array with nullptr

    // Traverse through the levels from top to bottom
    for (int i = level; i >= 0; i--) {
        // Move forward while the next node in the current level is not nullptr and its key is less than the given key
        while (current->forward[i] != nullptr && current->forward[i]->getKey() < key) {
            current = current->forward[i]; // Move to the next node
        }
        update[i] = current; // Store the last node visited at level i
    }

    current = current->forward[0]; // Move to the next node in the bottom level

    // If the current node is nullptr or its key is not equal to the given key
    
    if (current == nullptr || current->getKey() != key) {
        auto *n = new Node<T>(key, level); // Create a new node with the given key and level

        // Update pointers to insert the new node into the skip list
        for (int i = 0; i <= level-1; i++) {
            n->forward[i] = update[i]->forward[i]; // Update forward pointers of the new node
            update[i]->forward[i] = n; // Update forward pointers of the previous nodes to point to the new node
        }

        std::cout << "Successfully Inserted key " << key << "\n"; 
    }
    
}

template <typename T>
void SkipList<T>::deleteElement(T key) {
    auto *current = header;
    // create update array and initialize it
    Node<T> *update[MAXLVL + 1];
    memset(update, 0, sizeof(Node<T> *) * (MAXLVL + 1));
    for (int i = MAXLVL-1; i >= 0; i--)
    {
        while (current->forward[i] != NULL &&
               current->forward[i]->getKey() < key)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];
    if (current != NULL and current->getKey() == key)
    {
        for (int i = 0; i <= MAXLVL-1; i++)
        {
            if (update[i]->forward[i] != current)
            {
                break;
            }
            update[i]->forward[i] = current->forward[i];
        }
        // Remove levels having no elements
        while (level > 0 && header->forward[level] == 0)
        {
            level--;
        }
        cout << "Successfully deleted key " << key << "\n";
    }
}

// Display skip list level wise
template <typename T>
void SkipList<T>::displayList() {
    cout << "\n*****Skip List*****"
         << "\n";
    for (int i = 0; i <= MAXLVL-1; i++)
    {
        Node<T> *node = header->forward[i];
        cout << "Level " << i << ": ";
        while (node != NULL)
        {
            cout << node->getKey() << " ";
            node = node->forward[i];
        }
        cout << "\n";
    }

};


// MUST NOT CHANGE THE MAIN FUNCTION

int main() {
    srand(static_cast<unsigned>(time(nullptr))); // Seed random number generator

    SkipList<int> lst(3, 0.5);

    std::cout << "======== Insertion ========\n";
    lst.insertElement(5, 1);
    lst.insertElement(25, 2);
    lst.insertElement(30, 1);
    lst.insertElement(31, 3);
    lst.insertElement(42, 1);
    lst.insertElement(58, 2);
    lst.insertElement(62, 1);
    lst.insertElement(69, 3);
    lst.displayList();

    std::cout << "\n======== Search ========\n";
    int key = 31;
    if (lst.searchElement(key)) {
        std::cout << "Found " << key << std::endl;
    }
    else {
        std::cout << "Key " << key << " not found.\n";
    }

    std::cout << "\n======== Deletion ========\n";
    lst.deleteElement(key);
    lst.displayList();
    
    std::cout << "\n======== Automatic Memory Management ========\n";
}

