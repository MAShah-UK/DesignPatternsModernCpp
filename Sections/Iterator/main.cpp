#include <iostream>
#include <vector>
#include <experimental/coroutine>
#include <experimenta/generator>

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
        root->set_tree(this);
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
            return current != other.current;
        }

        PreOrderIterator<U>& operator++() {
            if(current->right) {
                current = current->right;
                while(current->left) {
                    current = current->left;
                }
            } else {
                Node<T>* p = current->parent;
                while(p && current == p->right) {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }

        Node<U>& operator*() {
            return *current;
        }
    };

    using iterator = PreOrderIterator<T>;

    iterator begin() { // Start from the left-most node on the tree.
        Node<T>* current = this->root;
        while(current->left) {
            current = current->left;
        }
        return iterator(current);
    }

    iterator end() {
        return iterator(nullptr);
    }

    experimental::generator<Node<T>*> post_order() { // Sets initial node to root for recursive call.
        return post_order(root);
    }
private:
    experimental::generator<Node<T>*> post_order(Node<T>* node) {
        if(node) {
            for(auto x : post_order(node->left)) {
                co_yield x;
            }
            for(auto y : post_order(node->right)) {
                co_yield y;
            }
            co_yield node;
        }
    }
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
    //        Me
    //     /     \
    //    F       M
    //   / \     / \
    //  FF FM   MF  MM
    BinaryTree<std::string> family(
        new Node<std::string>("Me",
                new Node<std::string>("Father",
                        new Node<std::string>("Father's Father"),
                        new Node<std::string>("Father's Mother")),
                new Node<std::string>("Mother",
                        new Node<std::string>("Mother's Father"),
                        new Node<std::string>("Mother's Mother"))
        )
    );

    std::cout << "Tree contains: ";
    for(auto it = family.begin(); it != family.end(); ++it) {
        std::cout << (*it).value << ". ";
    }
    std::cout << std::endl;

    // Use coroutines/recursion to iterate.
    for(auto it : family.post_order()) {
        std::cout << it->value << std::endl;
    }
}

int main() {
    stl_iterator_basics();
    binary_tree_iterator();

    return 0;
}

/*
Challenge: Use pre-order iteration for binary tree.
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct Node {
    T value;
    Node<T> *left{nullptr}, *right{nullptr}, *parent{nullptr};

    Node(T value) : value(value) {}

    Node(T value, Node<T> *left, Node<T> *right) : value(value), left(left), right(right) {
      left->parent = right->parent = this;
    }

    // traverse the node and its children preorder
    // and put all the results into `result`
    void preorder_traversal(vector<Node<T>*>& result) {
        // Set initial node to left-most node.
        Node<T>* current = this;
        while(current->parent) {
            current = current->parent;
        }
        while(current->left) {
            current = current->left;
        }
        result.push_back(current);
        // Iteratively add all nodes to result vector.
        bool traversed_to_root = false;
        while(true) {
             if(current->right) {
                current = current->right;
                while(current->left) {
                    current = current->left;
                }
            } else if(current->parent && current != current->parent->right) {
                current = current->parent;
                result.push_back(current);
                if(current->right) {
                    current = current->right;
                    while(current->left) {
                        current = current->left;
                    }
                }
            } else {
                if(traversed_to_root) {
                    break;
                }
                while(current->parent) {
                    current = current->parent;
                }
                traversed_to_root = true;
            }
            result.push_back(current);
        }
    }
};
 */