#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include "Utils.h"
#include "Calculate.h"

/**
 * @class Controller
 * @brief Declaration of the Controller class.
 *
 * @author 34528531
 * @version 01
 * @date 09/06/2026 34528531, Initial.
 *
 * @author 34528531
 * @version 02
 * @date 18/06/2026 34528531, Replaced menu methods and load source from filename.
 */

class Controller
{
public:
    void DisplayMenu();
    int LoadRecords(WeatherData & weatherData, const string & filename);
    int LoadFromSourceFile(WeatherData& weatherData, const string& filename);
    void ProcessMenuChoice(int choice, const WeatherData& weatherData);

private:
    WeatherData getRecordsForMonthAndYear(int month, int year, const WeatherData& weatherData) const;
    void averageWindSpeedAndStdev(int month, int year, const WeatherData& weatherData) const;
    void monthlyTemperatureAveragesAndStdev(int year, const WeatherData& weatherData) const;
    void monthlyTotalSolarRadiation(int year, const WeatherData& weatherData) const;
    void outputSummary(int year, const WeatherData& weatherData) const;
};

#endif // CONTROLLER_H_INCLUDED
