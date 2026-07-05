#include "Time.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    cout << "--- Test 1: Default Constructor ---" << endl;
    Time myTime;
    cout << "Expected: 00:00:00" << endl;
    cout << "Actual  : " << myTime << endl << endl;

    cout << "--- Test 2: Parameterized Constructor (Valid) ---" << endl;
    Time myTime1(14, 35, 9);
    cout << "Expected: 14:35:09" << endl;
    cout << "Actual  : " << myTime1 << endl << endl;

    cout << "--- Test 3: Setters and Getters (Valid Modifications) ---" << endl;
    Time validTime;
    validTime.SetHour(23);
    validTime.SetMinute(59);
    validTime.SetSecond(58);
    cout << "Expected Elements: Hour 23, Minute 59, Second 58" << endl;
    cout << "Actual Elements  : Hour " << validTime.GetHour()
         << ", Minute " << validTime.GetMinute()
         << ", Second " << validTime.GetSecond() << endl;
    cout << "Stream Output    : " << validTime << endl << endl;

    cout << "--- Test 4: Boundary Validation (Negative/Underflow Values) ---" << endl;
    Time lowerBoundTime(12, 30, 30);
    // Setting invalid low values (should fall back to 0)
    lowerBoundTime.SetHour(-1);
    lowerBoundTime.SetMinute(-5);
    lowerBoundTime.SetSecond(-10);
    cout << "Expected fallback: 00:00:00" << endl;
    cout << "Actual Output    : " << lowerBoundTime << endl << endl;

    cout << "--- Test 5: Boundary Validation (Overflow Values) ---" << endl;
    Time upperBoundTime(10, 10, 10);
    // Setting invalid high values (should fall back to 0)
    upperBoundTime.SetHour(24);
    upperBoundTime.SetMinute(60);
    upperBoundTime.SetSecond(61);
    cout << "Expected fallback: 00:00:00" << endl;
    cout << "Actual Output    : " << upperBoundTime << endl << endl;

    return 0;
}
