#include <iostream>

template <typename Key, typename Info>
class Sequence
{
private:
    struct node
    {
        Key key;
        Info info;
        node *next;
    };
    node *head;

public:
    Sequence();
    Sequence(Key, Info);
    ~Sequence();
    Sequence(const Sequence<Key, Info> &); // deep copy constructor (creates independent sequence that is a copy)
    Sequence& operator= (const Sequence &Seq);


    Sequence<Key, Info> produce(
        const Sequence<Key, Info> &seq1, int start1, int dl1,
        const Sequence<Key, Info> &seq2, int start2, int dl2,
        int limit = 1);

    void insertAtEnd(const Key &, const Info &);
    Key getKey(unsigned int);
    Info getInfo(unsigned int);
    void print();
    void reset();   // resets a sequence to the initial state
};

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence() : head(nullptr)
{
}

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(Key nKey, Info nInfo)
{
    head = new node;
    head->key = nKey;
    head->info = nInfo;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::reset()
{
    node *curr = *head;
    node *next;
    while (curr != nullptr)
    {
        next = curr->next; // store the next node
        free(curr);        // free mem for current node
        curr = next;       // move to the next node
    }

    *head = nullptr;
}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence()
{
    reset();
    free(head);
}

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info> &srcSeq)
{ // deep copy
    if (srcSeq->head == nullptr)
        return;

    node *srcTemp = srcSeq->head;
    // create the head (allocate memory, assign data)
    head = new node;
    head->key = srcTemp->key;
    head->info = srcTemp->info;
    head->next = nullptr;

    node *current = head; // iterator

    srcTemp = srcTemp->next; // move to the next of src after we copied head

    while (srcTemp != nullptr)
    {
        // allocate memory for the next node:
        current->next = new node;
        // move to the node we just allocated:
        current = current->next;
        // assign the data to the new node:
        current->key = srcTemp->key;
        current->info = srcTemp->info;
        current->next = nullptr;
        // move to the next node:
        srcTemp = srcTemp->next;
    }
}

template <typename Key, typename Info>
Sequence<Key, Info> &Sequence<Key, Info>::operator=(const Sequence<Key, Info> &Seq)
{
    if (this == &Seq)   // check if self-assignment
        return *this;
    
    this->reset();
    head = Seq->head;
    
    return *this;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::insertAtEnd(const Key &key, const Info &inf)
{
    // Create the new node and assign data
    node *newObj = new node;
    newObj->key = key;
    newObj->info = inf;
    newObj->next = nullptr;
    // if the list is empty, insert it at beginning
    if (head == nullptr)
        head = newObj;
    else
    {
        node *current = head; // Create a node to traverse until the end
        while (current->next != nullptr)
        {
            current = current->next;
        }
        // Insert the new node at the end (as the next of the last node)
        current->next = newObj;
    }
}

template <typename Key, typename Info>
Key Sequence<Key, Info>::getKey(unsigned int index)
{
    node *iterator = head;
    unsigned int i = 0;
    while (i != index)
    {
        iterator = iterator->next;
        i++;
    }
    return iterator->key;
}

template <typename Key, typename Info>
Info Sequence<Key, Info>::getInfo(unsigned int index)
{
    node *iterator = head;
    unsigned int index_iterator = 0;
    while (index_iterator != index)
    {
        iterator = iterator->next;
        index_iterator++;
    }
    return iterator->info;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::print()
{
    node *iterator = head;
    while (iterator != nullptr)
    {
        printNode(iterator);
        iterator = iterator->next;
    }
}

template <typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::produce(
    const Sequence<Key, Info> &seq1, int start1, int dl1,
    const Sequence<Key, Info> &seq2, int start2, int dl2,
    int limit)
{
    // For the 1st sequence
    node *startSeq1 = seq1->head;
    for (unsigned int pos1 = 0; pos1 != start1; pos1++)
    {
        startSeq1 = startSeq1->next;
    }

    // For the 2nd sequence:
    node *startSeq2 = seq2->head;
    for (unsigned int pos2 = 0; pos2 != start2; pos2++)
    {
        startSeq2 = startSeq2->next;
    }

    Sequence<Key, Info> finalSequence;
    // startSeq1 and start startSeq2 are our seq1 and seq2 iterators
    node *finalIterator = finalSequence->head; // Iterator that is at the start of our new sequence
    // Assign head (done only once)
    finalIterator->key = startSeq1->key;
    finalIterator->info = startSeq1->info;
    for (int i = 0; i < limit; i++)
    {

        for (int j1 = 0; j1 < dl1 || startSeq1->next == nullptr; j1++, finalIterator = finalIterator->next, startSeq1 = startSeq1->next)
        { // first : add dl1 elements from the seq1
            node *obj1 = new node;
            obj1->key = startSeq1->key;
            obj1->info = startSeq1->info;
            finalIterator->next = obj1;
        }

        for (int j2 = 0; j2 < dl2 || startSeq2->next == nullptr; j2++, finalIterator = finalIterator->next, startSeq2 = startSeq2->next)
        { // second : add dl2 elements from the seq2
            node *obj2 = new node;
            obj2->key = startSeq2->key;
            obj2->info = startSeq2->info;
            finalIterator->next = obj2;
        }
        startSeq1 = startSeq1->next;
        startSeq2 = startSeq2->next;
    }
    return finalSequence;
}