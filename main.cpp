#include "Menu.h"

int main()
{
    // 0. Data store
    Menu appMenu;
    WeatherData weatherData;
    const string filename = "data/data_source.txt";
    int recordsCount = appMenu.LoadFromSourceFile(weatherData, filename);

    // 1. Input / Load
    if (recordsCount > 0) {
        cout << "Successfully loaded " << weatherData.getCount() << " records!" << endl;
    }
    else
    {
        cout << "Error loading records. Program terminating." << endl;
        return 1;
    }


    // 2. Menu
    int choice;
    do {
        appMenu.DisplayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please choose from the menu.\n";
            cin.clear();
            choice = 0;
            continue;
        }

        appMenu.ProcessMenuChoice(choice, weatherData);

        cout << endl;

    } while (choice != 5);

    return 0;
}
