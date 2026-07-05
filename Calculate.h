#ifndef CALCULATE_H_INCLUDED
#define CALCULATE_H_INCLUDED

#include "Utils.h"

/**
 * @class Calculate
 * @brief Declaration of the Calculate class.
 *
 * @author 34528531
 * @version 01
 * @date 09/06/2026 34528531, Initial.
 *
 * @author 34528531
 * @version 02
 * @date 18/06/2026 34528531, Added Total and GetValue methods.
 */

class Calculate
{
public:
    static double Average(const WeatherData& weatherData, string column);
    static double StandardDeviation(const WeatherData& weatherData, double averageSpeed, string column);
    static double Total(const WeatherData& weatherData, string column);

private:
    static float GetValue(const WeatherEntry& weatherEntry, string dataType);
};

#endif // CALCULATE_H_INCLUDED
