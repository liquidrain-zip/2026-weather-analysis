#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <vector>
#include <stdexcept>
#include <string>

using std::out_of_range;
using std::to_string;
using std::vector;

/**
 * @brief Default initial size constant applied when allocation limits are missing or invalid.
 */
const int INITIAL_CAPACITY = 20;

/**
 * @class Vector
 * @brief A dynamic template array collection class encapsulating std::vector.
 *
 * @author 34528531
 * @version 01
 * @date 09/06/2026 34528531, Initial.
 *
 * @author 34528531
 * @version 02
 * @date 05/07/2026 34528531, Refactored to encapsulate std::vector.
 */
template <class T>
class Vector
{
public:
    /**
     * @brief Parameterized constructor.
     * @param initialCapacity Starting size allocation limit for the vector.
     */
    Vector(int initialCapacity);

    /**
     * @brief Default constructor. Initializes empty vector reserved to INITIAL_CAPACITY.
     */
    Vector();

    /**
     * @brief Copy constructor. Creates a deep copy.
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
    vector<T> m_vector;

    /**
     * @brief Retrieves current size limits for tracking array storage.
     * @return Integer value of capacity
     */
    int getCapacity() const;
};


template <class T>
Vector<T>::Vector()
{
    m_vector.reserve(INITIAL_CAPACITY);
}

template <class T>
Vector<T>::Vector(int initialCapacity)
{
    if (initialCapacity > 0)
    {
        m_vector.reserve(initialCapacity);
    }
    else
    {
        m_vector.reserve(INITIAL_CAPACITY);
    }
}

template <class T>
Vector<T>::Vector(const Vector& myVector)
{
    m_vector = myVector.m_vector;
}

template <class T>
Vector<T>& Vector<T>::operator = (const Vector& myVector)
{
    if (this != &myVector)
    {
        m_vector = myVector.m_vector;
    }
    return *this;
}

template <class T>
const T& Vector<T>::operator[](int index) const
{
    if (index < 0 || index >= static_cast<int>(m_vector.size()))
    {
        throw out_of_range("Vector index out of bounds: " + to_string(index));
    }
    return m_vector[index];
}

template <class T>
T& Vector<T>::operator[](int index)
{
    if (index < 0 || index >= static_cast<int>(m_vector.size())) {
        throw out_of_range("Vector index out of bounds: " + to_string(index));
    }
    return m_vector[index];
}

template <class T>
bool Vector<T>::Insert(const T& data, int index)
{
    if (index < 0 || index > static_cast<int>(m_vector.size()))
    {
        return false;
    }

    m_vector.insert(m_vector.begin() + index, data);

    return true;
}

template <class T>
bool Vector<T>::Delete(int index)
{
    if (index < 0 || index >= static_cast<int>(m_vector.size()))
    {
        return false;
    }

    if (m_vector.empty())
    {
        return false;
    }

    m_vector.erase(m_vector.begin() + index);

    return true;
}

template <class T>
int Vector<T>::getCount() const
{
    return static_cast<int>(m_vector.size());
}

template <class T>
int Vector<T>::getCapacity() const
{
    return static_cast<int>(m_vector.capacity());
}

#endif // VECTOR_H_INCLUDED
