#include "Controller.h"

int main()
{
    // 0. Data store
    Controller myController;
    WeatherData weatherData;
    const string filename = "data/data_source.txt";
    int recordsCount = myController.LoadFromSourceFile(weatherData, filename);

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
        myController.DisplayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Invalid input. Please choose from the menu.\n";
            cin.clear();
            choice = 0;
            continue;
        }

        myController.ProcessMenuChoice(choice, weatherData);

        cout << endl;

    } while (choice != 5);

    return 0;
}
