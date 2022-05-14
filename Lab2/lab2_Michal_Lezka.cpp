#include <iostream>

template <typename Key, typename Info>
class Ring
{
private:
    struct Node
    {
        Key key;
        Info info;
        Node *next;
        Node *prev;
    };
    Node *any;

public:
    class Iterator
    {
    private:
        Node *ptr;

    public:
        Iterator(Ring);
        ~Iterator();
        Key &getKey() const;
        Info &getInfo() const;
        Iterator &operator++();     // ++Ring
        Iterator operator++(int);   // Ring ++
        Iterator &operator--();
        Iterator operator--(int);

        void displayNode() const;
    };
    Ring();
    ~Ring();

    void addNode(Key key, Info info);
    int size();
    // for testing
    void displayNode(int nodeNumber);
    void displayAll();
};

template <typename Key, typename Info>
Ring<Key, Info>::Ring()
{
    any = nullptr;
}

template <typename Key, typename Info>
Ring<Key, Info>::~Ring()
{
    Node *tmp = any;
    int Size = size();
    for (int i = 0; i < Size; i++)
    {
        any = any->next;
        delete tmp;
        tmp = any;
    }
}

template <typename Key, typename Info>
int Ring<Key, Info>::size()
{
    // check for edge cases when there's only any
    if (any == nullptr)
        return 0;
    if (any->next == nullptr && any->prev == nullptr)
        return 1;

    // calculates for all other cases
    Node *tmp = any->next;
    int size = 1;
    while (tmp != any)
    {
        size++;
        tmp = tmp->next;
    }
    return size;
}

template <typename Key, typename Info>
void Ring<Key, Info>::addNode(Key key, Info info)
{
    // edge cases
    if (any == nullptr)
    {
        any = new Node;
        any->key = key;
        any->info = info;
        any->next = nullptr;
        any->prev = nullptr;
        return;
    }
    // if any is the only node
    Node *newNode = new Node;
    if (any->next == nullptr && any->prev == nullptr)
    {
        // setting up new node
        newNode->key = key;
        newNode->info = info;
        newNode->next = any;
        newNode->prev = any;
        // connecting it to the ring
        any->next = newNode;
        any->prev = newNode;
        return;
    }
    // for all non-edge cases

    // setting up new node
    Node *refPrev = any->prev;
    newNode->key = key;
    newNode->info = info;
    newNode->next = any;
    newNode->prev = refPrev;
    // connecting it to the ring
    refPrev->next = newNode;
    any->prev = newNode;
}

template <typename Key, typename Info>
void Ring<Key, Info>::displayNode(int nodeNumber)
{
    Node *tmp = any;
    for (int i = 1; i < nodeNumber; i++)
    {
        tmp = tmp->next;
    }
    std::cout << "-- Node " << nodeNumber << " --\n";
    std::cout << "Key: " << tmp->key << "\nInfo: " << tmp->info << std::endl;
}

template <typename Key, typename Info>
void Ring<Key, Info>::displayAll()
{
    std::cout << "--- Displaying all ---\n";
    int Size = size();
    Node *tmp = any;
    for (int i = 1; i <= Size; i++)
    {
        std::cout << "-- Node " << i << " --\n";
        std::cout << "Key: " << tmp->key << "\nInfo: " << tmp->info << std::endl;
        tmp = tmp->next;
    }
}

// ITERATOR methods

template <typename Key, typename Info>
Ring<Key, Info>::Iterator::Iterator(Ring ring) : ptr(ring.any) {}

template <typename Key, typename Info>
Ring<Key, Info>::Iterator::~Iterator() {}

template <typename Key, typename Info>
Key &Ring<Key, Info>::Iterator::getKey() const
{
    return ptr->key;
}

template <typename Key, typename Info>
Info &Ring<Key, Info>::Iterator::getInfo() const
{
    return ptr->info;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator &Ring<Key, Info>::Iterator::operator++()
{
    if (ptr == nullptr || ptr->next == nullptr)
        return *this;
    ptr = ptr->next;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator Ring<Key, Info>::Iterator::operator++(int)
{
    ++(*this);
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator &Ring<Key, Info>::Iterator::operator--()
{
    if (ptr == nullptr || ptr->next == nullptr)
        return *this;
    ptr = ptr->prev;
    return *this;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::Iterator Ring<Key, Info>::Iterator::operator--(int)
{
    --(*this);
    return *this;
}

template <typename Key, typename Info>
void Ring<Key, Info>::Iterator::displayNode() const
{
    std::cout << "-- Node from iterator --\n";
    std::cout << "Key: " << getKey() << "\nInfo: " << getInfo() << std::endl
              << std::endl;
}