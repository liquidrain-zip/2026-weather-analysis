#ifndef WEATHERENTRY_H_INCLUDED
#define WEATHERENTRY_H_INCLUDED

#include "Date.h"
#include "Time.h"

/**
 * @class WeatherEntry
 * @brief Encapsulates weather data for a specific date and time.
 *
 * @author 34528531
 * @version 01
 * @date 28/06/2026 34528531, Initial.
 */
class WeatherEntry
{
public:
    WeatherEntry();
    WeatherEntry(const Date& date, const Time& time, float speed, float temp, float solarRad);

    Date GetDate() const;
    Time GetTime() const;
    float GetWindSpeed() const;
    float GetTemperature() const;
    float GetSolarRadiation() const;

    void SetDate(const Date& date);
    void SetTime(const Time& time);
    void SetWindSpeed(float speed);
    void SetTemperature(float temp);
    void SetSolarRadiation(float solarRad);

    bool operator==(const WeatherEntry& other) const;

private:
    Date m_date;
    Time m_time;
    float m_windSpeed;
    float m_temperature;
    float m_solarRadiation;
};

#endif // WEATHERENTRY_H_INCLUDED
