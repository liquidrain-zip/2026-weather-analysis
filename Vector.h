#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdexcept>
#include <string>

using std::out_of_range;
using std::to_string;

/**
 * @brief Default initial size constant applied when allocation limits are missing or invalid.
 */
const int INITIAL_CAPACITY = 20;

/**
 * @class Vector
 * @brief A dynamic, self-resizing template array collection class.
 *
 * @author 34528531
 * @version 01
 * @date 09/06/2026 34528531, Initial.
 */
template <class T>
class Vector
{
public:
    /**
     * @brief Parameterized constructor.
     * @param initialCapacity Starting size allocation limit for the heap storage array.
     */
    Vector(int initialCapacity);

    /**
     * @brief Default constructor. Initializes empty vector mapped to INITIAL_CAPACITY.
     */
    Vector();

    /**
     * @brief Destructor. Cleans up dynamically allocated heap memory blocks safely.
     */
    ~Vector();

    /**
     * @brief Copy constructor. Allocates a unique heap space and creates a deep copy.
     * @param myVector Constant reference to the source vector being duplicated.
     */
    Vector(const Vector& myVector);

    /**
     * @brief Overloaded assignment operator. Safely replaces data contents using deep copying.
     * @param myVector Constant reference to the source vector.
     * @return Reference to this assigned vector instance block.
     */
    Vector& operator=(const Vector& myVector);

    /**
     * @brief Constant subscript array accessor. Includes safe std::out_of_range boundaries verification.
     * @param index Target position integer element lookup constraint.
     * @return Constant reference to the target element mapped within the vector array.
     */
    const T& operator[](int index) const; // Read

    /**
     * @brief Access operator for Vector (non-const version - modify element).
     *
     * @param index The index of the element to access.
     * @return T& A non-const reference to the element at the specified index.
     * @throws std::out_of_range if index is out of bounds.
     */
    T& operator[](int index); // Update

    /**
     * @brief Inserts an element item target into a specific array position.
     * @param data Constant reference to the data payload being inserted.
     * @param index position inside the array.
     * @return true if assignment succeeded, false if validation conditions fail.
     */
    bool Insert(const T& data, int index); // Create

    /**
     * @brief Deletes the element at the specified index.
     *
     * @param index The index of the element to delete (0 to getCount() - 1).
     * @return true if deletion was successful, false otherwise (e.g., invalid index or empty).
     */
    bool Delete(int index); // Delete

    /**
     * @brief Gets the count value tracking utilized index data records.
     * @return Integer total of items currently stored.
     */
    int getCount() const;

private:
    T* m_vector;
    int m_capacity;
    int m_count;

    /**
     * @brief Retrieves current size limits for tracking array storage.
     * @return Integer value of capacity
     */
    int getCapacity() const;

    /**
     * @brief Doubles capacity
     */
    void Resize();
};

template <class T>
Vector<T>::Vector()
{
    m_count = 0;
    m_capacity = INITIAL_CAPACITY;
    m_vector = new T[m_capacity];
    if (m_vector == nullptr)
    {
        m_capacity = 0;
    }
}

template <class T>
Vector<T>::Vector(int initialCapacity)
{
    if (initialCapacity > 0)
    {
        m_capacity = initialCapacity;
    }
    else
    {
        m_capacity = INITIAL_CAPACITY;
    }
    m_vector = new T[m_capacity]; // attempt to get heap memory

    if (m_vector == nullptr)
    {
        m_capacity = 0;
    }
    m_count = 0;
}

template <class T>
Vector<T>::~Vector()
{
    if (m_vector != nullptr)
    {
        delete[] m_vector;
        m_vector = nullptr;
    }
}

template <class T>
Vector<T>::Vector(const Vector& myVector)
{
    m_capacity = myVector.m_capacity;
    m_count = myVector.m_count;
    m_vector = nullptr;
    m_vector = new T[m_capacity];
    for (int i = 0; i < m_count; ++i)
    {
        m_vector[i] = myVector.m_vector[i];
    }
}

template <class T>
Vector<T>& Vector<T>::operator = (const Vector& myVector)
{
    if (this == &myVector)
    {
        return *this;
    }

    if (m_capacity != myVector.m_capacity || (m_capacity == 0 && myVector.m_capacity > 0) )
    {
        delete[] m_vector;
        m_capacity = myVector.m_capacity;
        m_vector = new T[m_capacity];
    }
    m_count = myVector.m_count;
    for (int i = 0; i < m_count; ++i)
    {
        m_vector[i] = myVector.m_vector[i];
    }
    return *this;
}

template <class T>
const T& Vector<T>::operator[](int index) const
{
    if (index < 0 || index >= m_count)
    {
        throw out_of_range("Vector index out of bounds: " + to_string(index));
    }
    return m_vector[index];
}

template <class T>
T& Vector<T>::operator[](int index)
{
    if (index < 0 || index >= m_count) {
        throw out_of_range("Vector index out of bounds: " + to_string(index));
    }
    return m_vector[index];
}

template <class T>
bool Vector<T>::Insert(const T& data, int index)
{
    if (index < 0 || index > m_count)
    {
        return false;
    }

    if (m_count >= m_capacity/2)
    {
        Resize();
    }

    if (m_count < m_capacity)
    {
        for (int i = m_count; i > index; --i)
        {
            m_vector[i] = m_vector[i - 1];
        }

        m_vector[index] = data;
        m_count++;

        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
bool Vector<T>::Delete(int index)
{
    if (index < 0 || index >= m_count)
    {
        return false;
    }

    if (m_count == 0)
    {
        return false;
    }

    for (int i = index; i < m_count - 1; ++i)
    {
        m_vector[i] = m_vector[i + 1];
    }

    m_count--;
    return true;
}

template <class T>
int Vector<T>::getCount() const
{
    return m_count;
}

template <class T>
int Vector<T>::getCapacity() const
{
    return m_capacity;
}

template <class T>
void Vector<T>::Resize()
{
    int newCapacity = m_capacity * 2;
    if (newCapacity < 1)
    {
        newCapacity = INITIAL_CAPACITY;
    }

    T* newVector = new T[newCapacity];

    for (int i = 0; i < m_count; ++i)
    {
        newVector[i] = m_vector[i];
    }

    delete[] m_vector;
    m_vector = newVector;
    m_capacity = newCapacity;
}

#endif // VECTOR_H_INCLUDED
