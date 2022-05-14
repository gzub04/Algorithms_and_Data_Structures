#include "lab2_Michal_Lezka.cpp"

int main()
{
    // testing addNode and displayNode
    Ring<int, int> testRing;
    // node 1
    testRing.addNode(1, 123);
    testRing.displayNode(1);
    Ring<int, int>::Iterator iterator(testRing);
    iterator.displayNode();
    testRing.displayNode(1);
    std::cout << std::endl;
    // node 2
    testRing.addNode(2, 234);
    testRing.displayNode(2);
    iterator++;
    iterator.displayNode();
    // node 3
    testRing.addNode(3, 345);
    testRing.displayNode(3);
    iterator++;
    iterator.displayNode();
    // node 4
    testRing.addNode(4, 567);
    testRing.displayNode(4);
    ++iterator;
    iterator.displayNode();
    std::cout << "Going back to iterator's initial node:\n";
    ++iterator;
    iterator.displayNode();
    testRing.displayAll();  // based on that, we can see that our "any" gets lost and I ran out of ideas how to combat this problem
                            // also worth noting that it only gets lost after initialising Iterator, not before

    return 0;
}