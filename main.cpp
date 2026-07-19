#include "Menu.h"

int main()
{
    // 0. Data store
    Menu menu;
    DataDB dataDB;
    const string filename = "data/data_source.txt";
    // 1. Input / Load
    int recordsCount = menu.LoadFromSourceFile(dataDB, filename);

    if (recordsCount > 0)
    {
        cout << "Successfully loaded " << recordsCount << " weather records." << endl;
    }
    else
    {
        cerr << "Error loading records. Program terminating." << endl;
        return 1;
    }
    // 2. Menu
    int choice;
    do
    {
        menu.DisplayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a number from the menu.\n";
            cin.clear();
            choice = 0; // returns to menu display
            continue;
        }
        menu.ProcessMenuChoice(choice, dataDB);
        cout << endl;
    }
    while (choice != 5);
    return 0;
}
