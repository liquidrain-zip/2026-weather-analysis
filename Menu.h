#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Utils.h"
#include "Calculate.h"
#include "DataDB.h"

/**
 * @class Menu
 * @brief Declaration of the Menu class.
 *
 * @author 34528531
 * @version 01
 * @date 09/06/2026 34528531, Initial.
 *
 * @author 34528531
 * @version 02
 * @date 18/06/2026 34528531, Replaced menu methods and load source from filename.
 *
 * @author 34528531
 * @version 03
 * @date 05/07/2026 34528531, Rename to Menu class.
 *
 * @author 34528531
 * @version 04
 * @date 12/07/2026 34528531, Option 3 replaced with displaySPCC.
 */

class Menu
{
public:
    void DisplayMenu();
    int LoadRecords(DataDB & weatherData, const string & filename);
    int LoadFromSourceFile(DataDB& weatherData, const string& filename);
    void ProcessMenuChoice(int choice, DataDB& weatherData);

private:
    WeatherData getRecordsForMonthAndYear(int month, int year, const DataDB& weatherData) const;
    void averageWindSpeedAndStdev(int month, int year, const DataDB& weatherData) const;
    void monthlyTemperatureAveragesAndStdev(int year, const DataDB& weatherData) const;
    void displaySPCC(int month, DataDB& weatherData) const;
    void outputSummary(int year, const DataDB& weatherData) const;
};

#endif // MENU_H_INCLUDED
