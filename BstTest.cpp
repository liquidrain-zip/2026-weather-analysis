#include <iostream>
#include "Bst.h"

using std::cout;
using std::endl;

// Helper function to format boolean output nicely
void printBool(bool val)
{
    cout << (val ? "True" : "False") << endl;
}

// Callback function matching: void (*process)(T&, void*)
void printNode(int& data, void*)
{
    cout << data << " ";
}

int main()
{
    cout << "===================================" << endl;
    cout << "       Bst<T> Template Testing     " << endl;
    cout << "===================================" << endl;

    // 1. Initialization and isEmpty test
    Bst<int> tree;
    cout << "\n[1] Initializing new tree..." << endl;
    cout << "Is tree empty? Expected: True | Actual: ";
    printBool(tree.isEmpty());

    // 2. Insertion
    cout << "\n[2] Inserting values: 50, 30, 70, 20, 40, 60, 80..." << endl;
    tree.Insert(50);
    tree.Insert(30);
    tree.Insert(70);
    tree.Insert(20);
    tree.Insert(40);
    tree.Insert(60);
    tree.Insert(80);

    cout << "Is tree empty? Expected: False | Actual: ";
    printBool(tree.isEmpty());

    // 3. Traversals (Updated with function pointer & nullptr context)
    cout << "\n[3] Testing Traversals:" << endl;

    cout << "InOrder   (Expected: 20 30 40 50 60 70 80) \nActual:   ";
    tree.InOrderTraversal(printNode, nullptr);
    cout << endl;

    cout << "PreOrder  (Expected: 50 30 20 40 70 60 80) \nActual:   ";
    tree.PreOrderTraversal(printNode, nullptr);
    cout << endl;

    cout << "PostOrder (Expected: 20 40 30 60 80 70 50) \nActual:   ";
    tree.PostOrderTraversal(printNode, nullptr);
    cout << endl;

    // 4. Search
    cout << "\n[4] Testing Search Functionality:" << endl;
    cout << "Search for 40 (Expected: True)  | Actual: ";
    printBool(tree.Search(40));

    cout << "Search for 99 (Expected: False) | Actual: ";
    printBool(tree.Search(99));

    // 5. Deletion Cases
    cout << "\n[5] Testing Deletion Cases:" << endl;

    // Case A: Delete Leaf Node
    cout << "Deleting Leaf Node (80)..." << endl;
    tree.DeleteNode(80);
    cout << "InOrder: ";
    tree.InOrderTraversal(printNode, nullptr); // 80 should be missing
    cout << endl;

    // Case B: Delete Node with One Child
    tree.Insert(25);
    cout << "\nAdded 25. Deleting Node with One Child (20)..." << endl;
    tree.DeleteNode(20);
    cout << "InOrder: ";
    tree.InOrderTraversal(printNode, nullptr); // 20 missing, 25 shifts up
    cout << endl;

    // Case C: Delete Node with Two Children
    cout << "\nDeleting Node with Two Children (Root: 50)..." << endl;
    tree.DeleteNode(50);
    cout << "InOrder: ";
    tree.InOrderTraversal(printNode, nullptr); // 50 missing, replaced by 60 (min of right subtree)
    cout << endl;

    // 6. Deep Copy Testing (Copy Constructor)
    cout << "\n[6] Testing Copy Constructor (Deep Copy):" << endl;
    Bst<int> treeCopy(tree);

    cout << "Original tree InOrder: ";
    tree.InOrderTraversal(printNode, nullptr);
    cout << endl;
    cout << "Copied tree InOrder:   ";
    treeCopy.InOrderTraversal(printNode, nullptr);
    cout << endl;

    cout << "Modifying Original (Inserting 999)..." << endl;
    tree.Insert(999);

    cout << "Original tree InOrder: ";
    tree.InOrderTraversal(printNode, nullptr);       // Should have 999
    cout << endl;
    cout << "Copied tree InOrder:   ";
    treeCopy.InOrderTraversal(printNode, nullptr);   // Should NOT have 999
    cout << endl;

    // 7. Assignment Operator Testing
    cout << "\n[7] Testing Assignment Operator:" << endl;
    Bst<int> treeAssigned;
    treeAssigned = treeCopy; // Assign from the copy (no 999)

    cout << "Assigned tree InOrder: ";
    treeAssigned.InOrderTraversal(printNode, nullptr);
    cout << endl;

    cout << "Modifying Copied tree (Deleting 70)..." << endl;
    treeCopy.DeleteNode(70);

    cout << "Copied tree InOrder:   ";
    treeCopy.InOrderTraversal(printNode, nullptr);       // Should not have 70
    cout << endl;
    cout << "Assigned tree InOrder: ";
    treeAssigned.InOrderTraversal(printNode, nullptr);   // Should still have 70
    cout << endl;

    // 8. Destroy Tree
    cout << "\n[8] Testing DestroyTree:" << endl;
    tree.DestroyTree();
    cout << "Destroyed original tree. Is empty? Expected: True | Actual: ";
    printBool(tree.isEmpty());

    cout << "\nAll tests completed successfully!" << endl;

    return 0;
}
