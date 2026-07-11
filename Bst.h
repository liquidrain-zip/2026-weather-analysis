#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;

/**
 * @brief Represents a node in the Binary Search Tree.
 * @tparam T The data type stored in the node.
 *
 * @author 34528531
 * @version 01
 * @date 05/07/2026 34528531, Initial.
 *
 * @author 34528531
 * @version 02
 * @date 07/07/2026 34528531, Updated traversals to use function pointers.
 *
 * @author 34528531
 * @version 03
 * @date 11/07/2026 34528531, Updated insert methods to return boolean type.
 **/
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
     */
    Bst();

    /**
     * @brief Destructor.
     */
    ~Bst();

    /**
     * @brief Copy constructor for deep copying the BST.
     */
    Bst(const Bst& otherTree);

    /**
     * @brief Copy assignment operator for deep copying the BST.
     */
    const Bst& operator=(const Bst&);

    /**
     * @brief Checks if the tree is empty.
     */
    bool isEmpty() const;

    /**
     * @brief Deallocates all nodes in the tree.
     */
    void DestroyTree();

    /**
     * @brief Performs an InOrder traversal of the tree.
     * @param process A function pointer that dictates what to do with each node's data.
     */
    void InOrderTraversal(void (*process)(const T&)) const;

    /**
     * @brief Performs a PreOrder traversal of the tree.
     * @param process A function pointer that dictates what to do with each node's data.
     */
    void PreOrderTraversal(void (*process)(const T&)) const;

    /**
     * @brief Performs a PostOrder traversal of the tree.
     * @param process A function pointer that dictates what to do with each node's data.
     */
    void PostOrderTraversal(void (*process)(const T&)) const;

    /**
     * @brief Inserts a new element into the BST while maintaining the search tree property.
     * @param data The element to be inserted.
     */
    bool Insert(const T & data);

    /**
     * @brief Searches for a specific element in the tree.
     */
    bool Search(const T& data) const;

    /**
     * @brief Deletes a node containing the specified target data.
     */
    void DeleteNode(const T& deleteTarget);

private:
    Node<T> *m_root;

    void copyTree(Node<T>* &copiedTreeRoot, Node<T>* otherTreeRoot);
    void destroy(Node<T>* &p);

    void inorder(Node<T> *p, void (*process)(const T&)) const;
    void preorder(Node<T> *p, void (*process)(const T&)) const;
    void postorder(Node<T> *p, void (*process)(const T&)) const;

    bool insert(Node<T>* &p, const T& data);
    bool search(Node<T> *p, const T& data) const;
    void deleteNode(Node<T>* &p, const T& deleteTarget);
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

template <class T>
Bst<T>::Bst(const Bst& otherTree):m_root(nullptr)
{
    copyTree(m_root, otherTree.m_root);
}

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
bool Bst<T>::Insert(const T& data)
{
    return insert(m_root, data);
}

template <class T>
bool Bst<T>::insert(Node<T>* &p, const T& data)
{
    if (p == nullptr)
    {
        p = new Node<T>;
        p->m_info = data;
        p->m_left = nullptr;
        p->m_right = nullptr;
        return true;
    }
    else if (data < p->m_info)
    {
        insert(p->m_left, data);
    }
    else if (data > p->m_info)
    {
        insert(p->m_right, data);
    }
    else
    {
        cout << "Duplicate value detected. Insertion failed." << endl;
        return false;
    }
}

template <class T>
bool Bst<T>::Search(const T& data) const
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
void Bst<T>::InOrderTraversal(void (*process)(const T&)) const
{
    inorder(m_root, process);
}

template <class T>
void Bst<T>::inorder(Node<T> *p, void (*process)(const T&)) const
{
    if (p != nullptr)
    {
        inorder(p->m_left, process);
        process(p->m_info);
        inorder(p->m_right, process);
    }
}

template <class T>
void Bst<T>::PreOrderTraversal(void (*process)(const T&)) const
{
    preorder(m_root, process);
}

template <class T>
void Bst<T>::preorder(Node<T> *p, void (*process)(const T&)) const
{
    if (p != nullptr)
    {
        process(p->m_info);
        preorder(p->m_left, process);
        preorder(p->m_right, process);
    }
}

template <class T>
void Bst<T>::PostOrderTraversal(void (*process)(const T&)) const
{
    postorder(m_root, process);
}

template <class T>
void Bst<T>::postorder(Node<T> *p, void (*process)(const T&)) const
{
    if (p != nullptr)
    {
        postorder(p->m_left, process);
        postorder(p->m_right, process);
        process(p->m_info);
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
