#include "Date.h"

int main()
{
    cout << "--- Test 1: Default Constructor ---" << endl;
    Date myDate;
    cout << "Expected: 0 / 0 / 0" << endl;
    cout << "Actual  : " << myDate.GetDay() << " / "
         << myDate.GetMonth() << " / "
         << myDate.GetYear() << endl << endl;

    cout << "--- Test 2: Parameterized Constructor ---" << endl;
    Date myDate1(16, 2, 2000);
    cout << "Expected: 16 / 2 / 2000" << endl;
    cout << "Actual  : " << myDate1.GetDay() << " / "
         << myDate1.GetMonth() << " / "
         << myDate1.GetYear() << endl << endl;

    cout << "--- Test 3: Setters and Getters (Valid Values) ---" << endl;
    Date validDate;
    validDate.SetDay(25);
    validDate.SetMonth(12);
    validDate.SetYear(2026);
    cout << "Expected: 25 / 12 / 2026" << endl;
    cout << "Actual  : " << validDate.GetDay() << " / "
         << validDate.GetMonth() << " / "
         << validDate.GetYear() << endl << endl;

    cout << "--- Test 4: Boundary Validation (Lower Bounds) ---" << endl;
    Date lowerBoundDate(10, 10, 2020);
    lowerBoundDate.SetDay(0);
    lowerBoundDate.SetMonth(0);
    cout << "Expected: 10 / 10 / 2020 (Values 0 should be rejected)" << endl;
    cout << "Actual  : " << lowerBoundDate.GetDay() << " / "
         << lowerBoundDate.GetMonth() << " / "
         << lowerBoundDate.GetYear() << endl << endl;

    cout << "--- Test 5: Boundary Validation (Upper Bounds) ---" << endl;
    Date upperBoundDate(15, 6, 2024);
    upperBoundDate.SetDay(32);
    upperBoundDate.SetMonth(13);
    cout << "Expected: 15 / 6 / 2024 (Values 32 and 13 should be rejected)" << endl;
    cout << "Actual  : " << upperBoundDate.GetDay() << " / "
         << upperBoundDate.GetMonth() << " / "
         << upperBoundDate.GetYear() << endl << endl;

    cout << "--- Test 6: Formatted Stream Insertion Operator (<<) ---" << endl;
    Date formatTest(1, 1, 2005);
    cout << "Expected String: 1 January 2005" << endl;
    cout << "Actual Stream  : " << formatTest << endl << endl;

    return 0;
}
