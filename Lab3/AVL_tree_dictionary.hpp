#ifndef AVL_TREE_DICTIONARY_HPP
#define AVL_TREE_DICTIONARY_HPP

#include <iostream>
#include <string>

using std::string;

template <typename Key, typename Info>
class Dictionary
{
private:
    // nodes of AVL
    struct Node
    {
        Key key;
        Info info;
        Node *left;
        Node *right;
    } * root;

    // private methods to be used only by public methods

    Node *l_rotation(Node *parent) // left rotation
    {
        Node *tmp = parent->right;
        if (tmp->right != nullptr)
            parent->right = tmp->left;
        else
            parent->right = nullptr;
        tmp->left = parent;
        return tmp;
    }

    Node *r_rotation(Node *parent) // right rotation
    {
        Node *tmp = parent->left;
        if (tmp->right != nullptr)
            parent->left = tmp->right;
        else parent->left = nullptr;
        tmp->right = parent;
        return tmp;
    }

    Node *lr_rotation(Node *parent)
    {
        Node *tmp = parent->left;
        parent->left = l_rotation(tmp); // makes the left rotation for the parent->left and then makes the parent->left point at the new, rotated value
        return r_rotation(parent);      // makes the right rotation for the parent and returns it
    }

    Node *rl_rotation(Node *parent)
    {
        Node *tmp = parent->right;
        parent->right = r_rotation(tmp); // makes the right rotation for the parent->right and then makes the parent->right point at the new, rotated value
        return l_rotation(tmp);          // makes the left rotation for the parent and returns it
    }

    int height(Node *node)
    {
        int h = 0;
        if (node != nullptr)
        {
            int l_height = height(node->left);
            int r_height = height(node->right);
            int max_height;
            if (l_height >= r_height)
                max_height = l_height;
            else if (l_height < r_height)
                max_height = r_height;
            h = max_height + 1;
        }
        return h;
    }

    int balance_factor(Node *node) // positive when left has more nodes, negative when right has more nodes
    {
        int l_height = height(node->left);
        int r_height = height(node->right);
        int bal_factor = l_height - r_height;
        return bal_factor;
    }

    void add_node(string key, Info info) // simply adds a node in the correct place without balancing tree
    {
        if (root == nullptr)
        {
            root = new Node;
            root->key = key;
            root->info = info;
            root->left = nullptr;
            root->right = nullptr;
            return;
        }
        Node *prev;
        Node *iterator = root;
        while (true)
        {
            if (key.compare(iterator->key) > 0)
            {
                prev = iterator;
                iterator = iterator->right;
            }
            else if (key.compare(iterator->key) < 0)
            {
                prev = iterator;
                iterator = iterator->left;
            }
            else if(key.compare(iterator->key) == 0)
            {
                iterator->info = info;
                return;
            }
            if (iterator == nullptr)
            {
                iterator = new Node;
                iterator->key = key;
                iterator->info = info;
                iterator->left = nullptr;
                iterator->right = nullptr;
                if (prev->key.compare(key) > 0)
                {
                    prev->left = iterator;
                }
                else if(prev->key.compare(key) < 0)
                {
                    prev->right = iterator;
                }
                else
                {
                    std::cerr << "Unexpected error in add_node\n";
                }
                return;
            }
        }
    }

    Node *balance(Node *node)
    {
        int bal_factor = balance_factor(node);
        
        if (bal_factor > 0)
        {
            bal_factor = balance_factor(node->left);
            if (bal_factor > 0)
                node = r_rotation(node);
            else if (bal_factor < 0)
                node = lr_rotation(node);
        }
        else if (bal_factor < 0)
        {
            bal_factor = balance_factor(node->right);
            if (bal_factor > 0)
                node = rl_rotation(node);
            else if (bal_factor < 0)
                node = l_rotation(node);
        }
        return node;
    }

    void print_all_as_tree(Node *node, int space)
    {
        // Base case
        if (node == nullptr)
            return;

        // Increase distance between levels
        space += 10;

        // Process right child first
        print_all_as_tree(node->right, space);

        // Print current node after space
        // count
        std::cout << std::endl;
        for (int i = 10; i < space; i++)
            std::cout << " ";
        std::cout << node->key << "\n";

        // Process left child
        print_all_as_tree(node->left, space);
    }

    void inorder(Node *node)
    {
        if (node->left != nullptr)
            inorder(node->left);

        std::cout << node->key << ", ";

        if(node->right != nullptr)
            inorder(node->right);
    }

    void delete_tree(Node *node)
    {
        if (node != nullptr)
        {
            delete_tree(node->left);
            delete_tree(node->right);
            delete node;
        }
    }

    Node *find(Key key)
    {
        Node *iterator = root;
        while (key.compare(iterator->key) != 0)
        {
            if (key.compare(iterator->key) > 0)
                iterator = iterator->right;
            else if (key.compare(iterator->key) < 0)
            {
                iterator = iterator->left;
            }
            if (iterator == nullptr)
            {
                return nullptr;
            }
        }
        return iterator;
    }

    void delete_node(Key key)
    {
        Node *prev = root;
        Node *node = root;
        bool to_left = false;   // check if deleting to left or right from prev
        while (key.compare(node->key) != 0)
        {
            if (key.compare(node->key) > 0)
            {
                prev = node;
                node = node->right;
                to_left = false;
            }
            else if (key.compare(node->key) < 0)
            {
                prev = node;
                node = node->left;
                to_left = true;
            }
            if (node == nullptr)
            {
                std::cout << "No such entry\n";
                return;
            }
        }
        if (node == root)
        {
            // force rebalance
            if (balance_factor(root) > 0)
            {
                root = r_rotation(root);
                to_left = false;
            }
            else
            {
                root = l_rotation(root);
                to_left = true;
            }
            prev = root;
        }
        // no children case
        if (node->left == nullptr && node->right == nullptr)
        {
            if (to_left)
                prev->left = nullptr;
            else
                prev->right = nullptr;
        }
        // one child cases
        else if (node->left == nullptr)
        {
            if (to_left)
                prev->left = node->right;
            else
                prev->right = node->right;
        }
        else if (node->right == nullptr)
        {
            if (to_left)
            {
                prev->left = node->left;
            }
            else
                prev->right = node->left;
        }
        // two children case
        else
        {
            Node *leftmost_prev = node;
            Node *leftmost = node->right;
            // loop down to find the leftmost leaf from the right branch
            while (leftmost->left != nullptr)
            {
                leftmost_prev = leftmost;
                leftmost = leftmost->left;
            }
            // prepare leftmost_prev
            if (leftmost->right != nullptr)
                leftmost_prev->right = leftmost->right;
            else
                leftmost_prev->right = nullptr;
            // prepare leftmost for swap
            leftmost->left = node->left;
            if (leftmost_prev != node)
                leftmost->right = node->right;
            else
                leftmost->right = nullptr;
            // put leftmost in place of node
            if (to_left)
                prev->left = leftmost;
            else
                prev->right = leftmost;

            root = balance(root);
        }
        delete node;
    }

public:
Dictionary();
~Dictionary();

void insert(Key newKey, Info newInfo); // adds a new node with new key and info or replaces an old one with the same key
void remove(Key key);                  // to-do removes a node with a given key
void search(Key key);                  // looks for a node with a given key and displays it
void print_tree();
void inorder_(); // to-do prints the whole tree
};

#endif