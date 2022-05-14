#include "AVL_tree_dictionary.hpp"

template <typename Key, typename Info>
Dictionary<Key, Info>::Dictionary() : root(nullptr) {}

template <typename Key, typename Info>
Dictionary<Key, Info>::~Dictionary()
{
    delete_tree(root);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::insert(Key newKey, Info newInfo)
{
    add_node(newKey, newInfo);
    //std::cerr << "add_node worked.\n";
    root = balance(root);
    //std::cerr << "balance worked.\n";
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::search(Key key)
{
    Node *node = find(key);
    if (node == nullptr)
    {
        std::cout << "No matching words for your query.\n";
        return;
    }
    
    std::cout << "Key: " << node->key << std::endl;
    std::cout << "Info: " << node->info << std::endl;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::print_tree()
{
    if (root == nullptr)
    {
        std::cout << "Tree has no entries.\n";
        return;
    }
    
    print_all_as_tree(root, 0);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::inorder_()
{
    inorder(root);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::remove(Key key)
{
    delete_node(key);

}