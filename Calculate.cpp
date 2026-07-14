#include "Calculate.h"

double Calculate::Total(const WeatherData& weatherData, string column)
{
    if (weatherData.getCount() == 0)
    {
        return 0.0;
    }

    double sum = 0.0;
    for (int i = 0; i < weatherData.getCount(); ++i)
    {
        sum += GetValue(weatherData[i], column);
    }
    return sum;
}

double Calculate::Average(const WeatherData& weatherData, string column)
{
    int count = weatherData.getCount();
    if (count == 0)
    {
        return 0.0;
    }

    double total = Total(weatherData, column);
    return total / count;
}

double Calculate::StandardDeviation(const WeatherData& weatherData, double average, string column)
{
    if (weatherData.getCount() < 2)
    {
        return 0.0;
    }

    double sumSquaredDifferences = 0.0;
    for (int i = 0; i < weatherData.getCount(); ++i)
    {
        double value = GetValue(weatherData[i], column);
        sumSquaredDifferences += pow(value - average, 2);
    }

    return sqrt(sumSquaredDifferences / (weatherData.getCount() - 1));
}

float Calculate::GetValue(const WeatherEntry& weatherEntry, string column)
{
    if (column == "S")
    {
        return weatherEntry.GetWindSpeed();
    }
    else if (column == "T")
    {
        return weatherEntry.GetTemperature();
    }
    else if (column == "SR")
    {
        return weatherEntry.GetSolarRadiation();
    }
    return 0.0f;
}

double Calculate::Spcc(const Vector<float>& dataX, const Vector<float>& dataY)
{
    int n = dataX.getCount();
    if (n == 0 || n != dataY.getCount())
    {
        return 0.0;
    }

    // Calculate means
    double sumX = 0.0, sumY = 0.0;
    for (int i = 0; i < n; ++i)
    {
        sumX += dataX[i];
        sumY += dataY[i];
    }
    double meanX = sumX / n;
    double meanY = sumY / n;

    // Calculate numerator and denominator parts
    double numerator = 0.0;
    double denomX = 0.0;
    double denomY = 0.0;

    for (int i = 0; i < n; ++i)
    {
        double diffX = dataX[i] - meanX;
        double diffY = dataY[i] - meanY;

        numerator += diffX * diffY;
        denomX += diffX * diffX;
        denomY += diffY * diffY;
    }

    // Calculate sPCC
    double denominator = sqrt(denomX * denomY);

    if (abs(denominator) < 1e-9)
    {
        return 0.0;
    }

    return numerator / denominator;
}

double Calculate::Mad(const WeatherData& weatherData, double averageValue, string dataType)
{
    int count = weatherData.getCount();
    if (count == 0)
    {
        return 0.0;
    }

    double sumAbsoluteDifferences = 0.0;
    for (int i = 0; i < count; ++i)
    {
        double value = GetValue(weatherData[i], dataType);
        sumAbsoluteDifferences += abs(value - averageValue);
    }

    // MAD is the average of the absolute differences
    return sumAbsoluteDifferences / count;
}
