#include"BTree.h"
#include"BTree.cpp"

// Verification Entrypoint
int main() {
    BTree<int> t(3); // B-Tree with a minimum degree of 3 (Max keys = 5)

    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    std::cout << "Traversal of the constructed B-tree is:";
    t.inOrder();

    int k = 6;
    (t.search(k) != nullptr) ? std::cout << "\nKey " << k << " is found"
        : std::cout << "\nKey " << k << " is not found";

    k = 15;
    (t.search(k) != nullptr) ? std::cout << "\nKey " << k << " is found\n"
        : std::cout << "\nKey " << k << " is not found\n";

    return 0;
}