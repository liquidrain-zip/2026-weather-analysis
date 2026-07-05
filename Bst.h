#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;
using std::runtime_error;

/**
 * @brief Represents a node in the Binary Search Tree.
 * @tparam T The data type stored in the node.
 *
 * @author 34528531
 * @version 01
 * @date 05/07/2026 34528531, Initial.
 */
template <class T>
struct Node
{
    /// @brief The data value stored in the node.
    T m_info;
    /// @brief Pointer to the left child node.
    Node<T> *m_left;
    /// @brief Pointer to the right child node.
    Node<T> *m_right;
};

template <class T>
class Bst
{
public:
    /**
     * @brief Default constructor.
     * Initializes an empty tree by setting the root pointer to nullptr.
     */
    Bst();

    /**
     * @brief Destructor.
     * Calls DestroyTree() to recursively deallocate all nodes in the tree.
     */
    ~Bst();

    /**
     * @brief Copy constructor for deep copying the BST.
     * @param otherTree The BST object to be copied.
     */
    Bst(const Bst& otherTree); // copy constructor

    /**
     * @brief Copy assignment operator for deep copying the BST.
     * Handles self-assignment and performs a deep copy of the structure.
     * @param other The BST object on the right-hand side of the assignment.
     * @return A constant reference to the current object (*this).
     */
    const Bst& operator=(const Bst&); // copy assignment operator

    /**
     * @brief Checks if the tree is empty.
     * @return true if the root is nullptr, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Deallocates all nodes in the tree.
     * Public wrapper for the private destroy() helper function.
     */
    void DestroyTree();

    /**
     * @brief Performs an InOrder traversal of the tree.
     * Prints the elements in ascending order (Left -> Root -> Right).
     */
    void InOrderTraversal();

    /**
     * @brief Performs a PreOrder traversal of the tree.
     * Prints the elements in Root -> Left -> Right order.
     */
    void PreOrderTraversal();

    /**
     * @brief Performs a PostOrder traversal of the tree.
     * Prints the elements in Left -> Right -> Root order.
     */
    void PostOrderTraversal();

    /**
     * @brief Inserts a new element into the BST while maintaining the search tree property.
     * @param data The element to be inserted.
     */
    void Insert(const T & data);

    /**
     * @brief Searches for a specific element in the tree.
     * @param data The element to search for.
     * @return true if the element is found, false otherwise.
     */
    bool Search(const T& data);

    /**
     * @brief Deletes a node containing the specified target data.
     * Handles nodes with zero, one, or two children.
     * @param deleteTarget The value of the node to be deleted.
     */
    void DeleteNode(const T& deleteTarget);

private:
    /// @brief Pointer to the root node of the BST.
    Node<T> *m_root;

    /// @brief Recursive helper function to perform a deep copy of the tree structure.
    void copyTree(Node<T>* &copiedTreeRoot, Node<T>* otherTreeRoot);

    /// @brief Recursive helper function to deallocate all nodes in the tree (post-order traversal).
    void destroy(Node<T>* &p);

    /// @brief Recursive helper function for InOrder traversal.
    void inorder(Node<T> *p) const;

    /// @brief Recursive helper function for PreOrder traversal.
    void preorder(Node<T> *p) const;

    /// @brief Recursive helper function for PostOrder traversal.
    void postorder(Node<T> *p) const;

    /// @brief Recursive helper function for inserting a node.
    void insert(Node<T>* &p, const T& data);

    /// @brief Recursive helper function for searching for data.
    bool search(Node<T> *p, const T& data) const;

    /// @brief Recursive helper function for deleting a node.
    void deleteNode(Node<T>* &p, const T& deleteTarget);

    /**
     * @brief Finds the minimum value in a given subtree.
     * Used by deleteNode to find the inorder successor (smallest element in the right subtree).
     * @param p The root of the subtree to search.
     * @return The minimum value found.
     * @throw std::runtime_error if called on a nullptr.
     */
    T getMin(Node<T>* p) const;
};



template <class T>
Bst<T>::Bst()
{
    m_root = nullptr;
}

template <class T>
Bst<T>::~Bst()
{
    DestroyTree();
}

// Copy Constructor
template <class T>
Bst<T>::Bst(const Bst& otherTree):m_root(nullptr)
{
    copyTree(m_root, otherTree.m_root);
}

// Copy Assignment Operator
template <class T>
const Bst<T>& Bst<T>::operator=(const Bst<T>& other)
{
    if (this != &other)
    {
        DestroyTree();
        copyTree(m_root, other.m_root);
    }
    return *this;
}

template <class T>
bool Bst<T>::isEmpty() const
{
    return (m_root == nullptr);
}

template <class T>
void Bst<T>::DestroyTree()
{
    destroy(m_root);
}

// Private Recursive Helper to destroy the tree
template <class T>
void Bst<T>::destroy(Node<T>* &p)
{
    if (p != nullptr)
    {
        destroy(p->m_left);
        destroy(p->m_right);
        delete p;
        p = nullptr;
    }
}

// --- Copy Operations (Rule of Three) ---

// Private Recursive Helper to perform deep copy
template <class T>
void Bst<T>::copyTree(Node<T>* &copiedTreeRoot, Node<T>* otherTreeRoot)
{
    if (otherTreeRoot == nullptr)
    {
        copiedTreeRoot = nullptr;
    }
    else
    {
        copiedTreeRoot = new Node<T>;
        copiedTreeRoot->m_info = otherTreeRoot->m_info;

        copyTree(copiedTreeRoot->m_left, otherTreeRoot->m_left);
        copyTree(copiedTreeRoot->m_right, otherTreeRoot->m_right);
    }
}

template <class T>
void Bst<T>::Insert(const T& data)
{
    insert(m_root, data);
}

template <class T>
void Bst<T>::insert(Node<T>* &p, const T& data)
{
    if (p == nullptr)
    {
        p = new Node<T>;
        p->m_info = data;
        p->m_left = nullptr;
        p->m_right = nullptr;
    }
    else if (data < p->m_info)
    {
        insert(p->m_left, data);
    }
    else if (data > p->m_info)
    {
        insert(p->m_right, data);
    }
}

template <class T>
bool Bst<T>::Search(const T& data)
{
    return search(m_root, data);
}

template <class T>
bool Bst<T>::search(Node<T> *p, const T& data) const
{
    if (p == nullptr)
    {
        return false;
    }
    else if (data == p->m_info)
    {
        return true;
    }
    else if (data < p->m_info)
    {
        return search(p->m_left, data);
    }
    else
    {
        return search(p->m_right, data);
    }
}

template <class T>
void Bst<T>::InOrderTraversal()
{
    inorder(m_root);
    cout << endl;
}

template <class T>
void Bst<T>::inorder(Node<T> *p) const
{
    if (p != nullptr)
    {
        inorder(p->m_left);
        cout << p->m_info << " ";
        inorder(p->m_right);
    }
}

template <class T>
void Bst<T>::PreOrderTraversal()
{
    preorder(m_root);
    cout << endl;
}

template <class T>
void Bst<T>::preorder(Node<T> *p) const
{
    if (p != nullptr)
    {
        cout << p->m_info << " ";
        preorder(p->m_left);
        preorder(p->m_right);
    }
}

template <class T>
void Bst<T>::PostOrderTraversal()
{
    postorder(m_root);
    cout << endl;
}

template <class T>
void Bst<T>::postorder(Node<T> *p) const
{
    if (p != nullptr)
    {
        postorder(p->m_left);
        postorder(p->m_right);
        cout << p->m_info << " ";
    }
}

template <class T>
T Bst<T>::getMin(Node<T>* p) const
{
    if (p == nullptr)
    {
        throw runtime_error("Attempted to get minimum of a null node.");
    }
    while (p->m_left != nullptr)
    {
        p = p->m_left;
    }
    return p->m_info;
}

template <class T>
void Bst<T>::DeleteNode(const T& deleteTarget)
{
    deleteNode(m_root, deleteTarget);
}

template <class T>
void Bst<T>::deleteNode(Node<T>* &p, const T& deleteTarget)
{
    if (p == nullptr)
    {
        return;
    }
    else if (deleteTarget < p->m_info)
    {
        deleteNode(p->m_left, deleteTarget);
    }
    else if (deleteTarget > p->m_info)
    {
        deleteNode(p->m_right, deleteTarget);
    }
    else // Found the node to delete
    {
        Node<T> *temp = p;

        if (p->m_left == nullptr)
        {
            p = p->m_right;
            delete temp;
        }
        else if (p->m_right == nullptr)
        {
            p = p->m_left;
            delete temp;
        }
        else // Two children
        {
            p->m_info = getMin(p->m_right);
            deleteNode(p->m_right, p->m_info);
        }
    }
}

#endif // BST_H_INCLUDED
