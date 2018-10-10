#include <iostream>
#include <vector>

template <typename T> struct BinaryTree;
//   A
//  / \
// B   C
template <typename T>
struct Node {
    T value = T();
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    Node<T>* parent = nullptr;
    BinaryTree<T>* tree = nullptr;

    Node(const T& value) : value(value) {}
    virtual ~Node() {
        if(left) {
            delete left;
        }
        if(right) {
            delete right;
        }
    }

    Node(const T& value, Node<T>* left, Node<T>* right)
    : value(value), left(left), right(right) {
        this->left->tree = this->right->tree = tree;
        this->left->parent = this->right->parent = this;
    }

    void set_tree(BinaryTree<T>* tree) {
        this->tree = tree;
        if(left) {
            left->set_tree(tree);
        }
        if(right) {
            right->set_tree(tree);
        }
    }
};
template <typename T>
struct BinaryTree {
    Node<T>* root = nullptr;

    BinaryTree(Node<T>* root) : root(root) {
        root->set_tree(*this);
    }
    virtual ~BinaryTree() {
        if(root) {
            delete root;
        }
    }

    template <typename U>
    struct PreOrderIterator {
        Node<U>* current;

        PreOrderIterator(Node<U>* current) : current(current) {}

        bool operator!=(const PreOrderIterator<U>& other) {
            
        }
    };
};

void stl_iterator_basics() {
    // Iterator syntax.
    std::vector<std::string> names {"john", "jane", "jill", "jack"};
    std::vector<std::string>::iterator it = names.begin(); // can use global function begin(names).
    std::cout << "First name in vector: " << *it << std::endl; // Uses pointer syntax.
    ++it;
    it->append(" goodall"); // Call string::append method.
    std::cout << "Second name in vector: " << *it << std::endl;
    while(++it != names.end()) { // end is 1 passed the last element, i.e. john... jack, x.
        std::cout << "Next name in vector: " << *it << std::endl;
    }

    // Reverse iterators.
    // ++ is seen as 'advance', so this advances in the reverse direction.
    std::cout << "Items in reverse order: ";
    for(auto rev_it = names.rbegin(); rev_it != names.rend(); ++rev_it) { // or rbegin(names), rend(names).
        std::cout << *rev_it;
        if(rev_it+1 != names.rend()) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    // Constant iterators.
    std::vector<std::string>::const_reverse_iterator jack = names.crbegin();
    // *jack += std:string(" reacher"); // Error: can't modify constant.

    // Range-based for loop. Can only go forward.
    // The object must implement begin() and end() functions.
    // name is *it.
    std::cout << "Items using range-based for loop: ";
    for(auto&& name : names) {
        std::cout << name << ". ";
    }
    std::cout << std::endl;
}
void binary_tree_iterator() {

}

int main() {
    stl_iterator_basics();
    binary_tree_iterator();

    return 0;
}