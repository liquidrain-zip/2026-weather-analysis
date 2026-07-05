#include "Calculate.h"

double Calculate::Total(const WeatherData& weatherData, string column)
{
    if (weatherData.getCount() == 0) {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 0; i < weatherData.getCount(); ++i) {
        sum += GetValue(weatherData[i], column);
    }
    return sum;
}

double Calculate::Average(const WeatherData& weatherData, string column)
{
    int count = weatherData.getCount();
    if (count == 0) {
        return 0.0;
    }

    double total = Total(weatherData, column);
    return total / count;
}

double Calculate::StandardDeviation(const WeatherData& weatherData, double average, string column)
{
    if (weatherData.getCount() < 2) {
        return 0.0;
    }

    double sumSquaredDifferences = 0.0;
    for (int i = 0; i < weatherData.getCount(); ++i) {
        double value = GetValue(weatherData[i], column);
        sumSquaredDifferences += pow(value - average, 2);
    }

    return sqrt(sumSquaredDifferences / (weatherData.getCount() - 1));
}

float Calculate::GetValue(const WeatherEntry& weatherEntry, string column)
{
    if (column == "S") {
        return weatherEntry.m_windSpeed;
    } else if (column == "T") {
        return weatherEntry.m_temperature;
    } else if (column == "SR") {
        return weatherEntry.m_solarRadiation;
    }
    return 0.0f;
}
