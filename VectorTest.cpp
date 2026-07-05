#include "Vector.h"
#include <iostream>
#include <stdexcept>
#include <string>

using std::cout;
using std::endl;
using std::out_of_range;

int main()
{
    cout << "--- Test 1: Default Constructor ---" << endl;
    Vector<int> intVec;
    cout << "Expected Count: 0" << endl;
    cout << "Actual Count  : " << intVec.getCount() << endl << endl;

    cout << "--- Test 2: Parameterized Constructor ---" << endl;
    Vector<double> doubleVec(50);
    cout << "Expected Count: 0" << endl;
    cout << "Actual Count  : " << doubleVec.getCount() << endl << endl;

    cout << "--- Test 3: Insert and Element Retrieval (Valid Access) ---" << endl;
    Vector<int> regularVec;
    regularVec.Insert(100, 0);
    regularVec.Insert(200, 1);
    cout << "Expected: Count 2, Elements [100, 200]" << endl;
    cout << "Actual  : Count " << regularVec.getCount()
         << ", Elements [" << regularVec[0] << ", " << regularVec[1] << "]" << endl;
    cout << "Array Pointer Location: " << &regularVec[0] << endl << endl;

    cout << "--- Test 4: Boundary Validation (Invalid Lower Index Insertion) ---" << endl;
    Vector<int> boundaryVec;
    bool lowerInsertSuccess = boundaryVec.Insert(50, -1);
    cout << "Expected Success Status: 0 (False)" << endl;
    cout << "Actual Success Status  : " << lowerInsertSuccess << endl << endl;

    cout << "--- Test 5: Boundary Validation (Invalid Upper Index Insertion) ---" << endl;
    bool upperInsertSuccess = boundaryVec.Insert(50, 2); // Cannot insert at index 2 when count is 0
    cout << "Expected Success Status: 0 (False)" << endl;
    cout << "Actual Success Status  : " << upperInsertSuccess << endl << endl;

    cout << "--- Test 6: Deep Copy Constructor Verification ---" << endl;
    Vector<int> originalVec;
    originalVec.Insert(67, 0);

    Vector<int> copiedVec(originalVec); // Triggers deep copy allocation
    cout << "Expected Copied Element: 67" << endl;
    cout << "Actual Copied Element  : " << copiedVec[0] << endl;
    cout << "Original Vector Array Pointer Location: " << &originalVec[0] << endl;
    cout << "Copied Vector Array Pointer Location  : " << &copiedVec[0] << endl;
    cout << "Status: " << (&originalVec[0] != &copiedVec[0] ? "SUCCESS (Deep Copy Verified)" : "FAIL (Shallow Copy Bug)") << endl << endl;

    cout << "--- Test 7: Deep Assignment Operator Verification ---" << endl;
    Vector<int> assignTarget;
    assignTarget = originalVec; // Triggers operator=
    cout << "Expected Assigned Element: 67" << endl;
    cout << "Actual Assigned Element  : " << assignTarget[0] << endl;
    cout << "Original Vector Array Pointer Location: " << &originalVec[0] << endl;
    cout << "Assigned Vector Array Pointer Location: " << &assignTarget[0] << endl;
    cout << "Status: " << (&originalVec[0] != &assignTarget[0] ? "SUCCESS (Deep Assignment Verified)" : "FAIL (Shallow Assignment Bug)") << endl << endl;

    cout << "--- Test 8: Exception Handling (Subscript Out of Range) ---" << endl;
    cout << "Expected: Catch out_of_range exception gracefully" << endl;
    try
    {
        // Forcing a bad read index lookup
        int invalidData = originalVec[5];
        cout << "Actual  : Value read successfully? " << invalidData << " (Failed test requirement)" << endl;
    }
    catch (const out_of_range & e)
    {
        cout << "Actual  : Exception caught! Message -> " << e.what() << endl;
    }
    cout << endl;

    cout << "--- Test 9: Element Modification (Update via non-const []) ---" << endl;
    Vector<int> updateVec;
    updateVec.Insert(123, 0);
    updateVec[0] = 999; // Uses the non-const T& operator[] to update the value
    cout << "Expected Element: 999" << endl;
    cout << "Actual Element  : " << updateVec[0] << endl << endl;

    cout << "--- Test 10: Element Deletion (Valid Index) ---" << endl;
    Vector<int> deleteVec;
    deleteVec.Insert(10, 0);
    deleteVec.Insert(20, 1);
    deleteVec.Insert(30, 2);
    bool deleteSuccess = deleteVec.Delete(1); // Delete the middle element (20)
    cout << "Expected: Success 1 (True), Count 2, Elements [10, 30]" << endl;
    cout << "Actual  : Success " << deleteSuccess
         << ", Count " << deleteVec.getCount()
         << ", Elements [" << deleteVec[0] << ", " << deleteVec[1] << "]" << endl << endl;

    cout << "--- Test 11: Element Deletion (Invalid Index / Bounds Check) ---" << endl;
    bool invalidDelete = deleteVec.Delete(50); // Index 50 does not exist
    cout << "Expected Success Status: 0 (False)" << endl;
    cout << "Actual Success Status  : " << invalidDelete << endl << endl;

    return 0;
}
