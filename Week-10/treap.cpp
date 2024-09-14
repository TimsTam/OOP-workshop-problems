#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>

// Template class for TreapNode
template <typename T>
class TreapNode {
private:
    T key; // Node's key
    int priority; // Node's priority (used for heap property)
    std::shared_ptr<TreapNode<T>> left; // Left child
    std::shared_ptr<TreapNode<T>> right; // Right child

    void updateSubtreeProperties() {
        subtree_sum = key;
        subtree_count = 1;
        if (left) {
            subtree_sum += left->subtree_sum;
            subtree_count += left->subtree_count;
        }
        if (right) {
            subtree_sum += right->subtree_sum;
            subtree_count += right->subtree_count;
        }
    }

public:
    int subtree_sum; // Sum of keys in the subtree rooted at this node
    int subtree_count; // Count of nodes in the subtree rooted at this node
    // Constructor with key (priority is randomized)
    TreapNode(T key) : key(key), priority(rand()), left(nullptr), right(nullptr), subtree_sum(key), subtree_count(1) {}

    // Constructor with key and priority
    TreapNode(T key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr), subtree_sum(key), subtree_count(1) {}

    // Destructor
    ~TreapNode() {
        std::cout << "Key " << key << " destroyed." << std::endl;
    }

    // Function for right rotation
    void right_rotation(std::shared_ptr<TreapNode<T>>& x) {
        std::shared_ptr<TreapNode<T>> y = x->left;
        x->left = y->right;
        y->right = x;
        x = y;
        y->right->updateSubtreeProperties();
        y->updateSubtreeProperties();
    }

    // Function for left rotation
    void left_rotation(std::shared_ptr<TreapNode<T>>& y) {
        std::shared_ptr<TreapNode<T>> x = y->right;
        y->right = x->left;
        x->left = y;
        y = x;
        x->left->updateSubtreeProperties();
        x->updateSubtreeProperties();
    }

    // Insert function for the Treap
    void insert(std::shared_ptr<TreapNode<T>>& root, T key) {
        if (!root) {
            root = std::make_shared<TreapNode<T>>(key);
            return;
        }

        // Recur down the tree to find the correct position
        if (key <= root->key) {
            insert(root->left, key);
            // Maintain heap property
            if (root->left && root->left->priority > root->priority)
                right_rotation(root);
        } else {
            insert(root->right, key);
            // Maintain heap property
            if (root->right && root->right->priority > root->priority)
                left_rotation(root);
        }
        root->updateSubtreeProperties();
    }

    // Remove function for the Treap
    bool remove(std::shared_ptr<TreapNode<T>>& root, T key) {
        if (!root)
            return false;

        if (key < root->key)
            return remove(root->left, key);
        if (key > root->key)
            return remove(root->right, key);

        // Node to be deleted found
        if (!root->left && !root->right) {
            root.reset();
        } else if (!root->left || !root->right) {
            std::shared_ptr<TreapNode<T>> child = (root->left) ? root->left : root->right;
            root = child;
        } else {
            // Both children exist, perform rotations to maintain heap property
            if (root->left->priority < root->right->priority) {
                left_rotation(root);
                remove(root->left, key);
            } else {
                right_rotation(root);
                remove(root->right, key);
            }
        }

        if (root) root->updateSubtreeProperties();
        return true;
    }

    // Search function for the Treap
    std::shared_ptr<TreapNode<T>> search(std::shared_ptr<TreapNode<T>>& root, T key) {
        if (!root || root->key == key)
            return root;
        if (root->key < key)
            return search(root->right, key);
        return search(root->left, key);
    }

    // Print function to visualize the Treap
    void printBT(const std::string &prefix, std::shared_ptr<TreapNode<T>> node, bool isLeft)
    {
        if (node != nullptr)
        {
            std::cout << prefix;
            std::cout << (isLeft ? "|--" : "L--");
            // print the value of the node
            std::cout << node->key << "|" << node->priority << " (Sum: " << node->subtree_sum << ", Count: " << node->subtree_count << ")" << std::endl;
            // enter the next tree level - left and right branch
            printBT(prefix + (isLeft ? "|   " : "    "), node->right, true);
            printBT(prefix + (isLeft ? "|   " : "    "), node->left, false);
        }
    }

    int countLeafNodes() {
        if (!left && !right) return 1;
        int leftCount = left ? left->countLeafNodes() : 0;
        int rightCount = right ? right->countLeafNodes() : 0;
        return leftCount + rightCount;
    }

    int countSingleChildNodes() {
        int count = 0;
        if ((left && !right) || (!left && right)) {
            count = 1;
        }
        int leftCount = left ? left->countSingleChildNodes() : 0;
        int rightCount = right ? right->countSingleChildNodes() : 0;
        return count + leftCount + rightCount;
    }

    int countTwoChildrenNodes() {
        int count = 0;
        if (left && right) {
            count = 1;
        }
        int leftCount = left ? left->countTwoChildrenNodes() : 0;
        int rightCount = right ? right->countTwoChildrenNodes() : 0;
        return count + leftCount + rightCount;
    }
};

int main() {
    srand(time(NULL)); // Initialize random seed

    std::shared_ptr<TreapNode<int>> t = nullptr; // Initialize the Treap

    std::vector<int> keys{3, 1, 4, 2, 9, 5, 7, 8, 6}; // Keys to be inserted

    // Insert keys into the Treap
    for (auto key : keys)
        t->insert(t, key);

    // Print the Treap
    std::cout << "Treap structure:" << std::endl;
    t->printBT("", t, false);

    // Test 1: Leaf nodes count
    int leafNodeCount = t->countLeafNodes();
    std::cout << "\nLeaf nodes count: " << leafNodeCount << std::endl;

    // Test 2: Single child nodes count
    int singleChildNodeCount = t->countSingleChildNodes();
    std::cout << "Single child nodes count: " << singleChildNodeCount << std::endl;

    // Test 3: Two children nodes count
    int twoChildrenNodeCount = t->countTwoChildrenNodes();
    std::cout << "Two children nodes count: " << twoChildrenNodeCount << std::endl;

    // Search test
    int searchKey = 5;
    std::cout << "Search for Key in Treap: " << std::endl;
    auto foundNode = t->search(t, searchKey);
    if (foundNode) {
        std::cout << "Found node with key " << searchKey << " (Sum: " << foundNode->subtree_sum << ", Count: " << foundNode->subtree_count << ")" << std::endl;
    } else {
        std::cout << "Node with key " << searchKey << " not found." << std::endl;
    }

    // Removal test
    int removeKey = 9;
    std::cout << "Remove Key from Treap: " << std::endl;
    bool removed = t->remove(t, removeKey);
    std::cout << "Node with key " << removeKey << (removed ? " removed." : " not found.") << std::endl;
    std::cout << "Treap structure after removal:" << std::endl;
    t->printBT("", t, false);

    // Recheck counts after removal
    leafNodeCount = t->countLeafNodes();
    std::cout << "\nLeaf nodes count after removal: " << leafNodeCount << std::endl;

    singleChildNodeCount = t->countSingleChildNodes();
    std::cout << "Single child nodes count after removal: " << singleChildNodeCount << std::endl;

    twoChildrenNodeCount = t->countTwoChildrenNodes();
    std::cout << "Two children nodes count after removal: " << twoChildrenNodeCount << std::endl;

    return 0;
}
