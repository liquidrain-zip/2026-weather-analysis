#include "WeatherEntry.h"

WeatherEntry::WeatherEntry()
{
    m_windSpeed = 0.0f;
    m_temperature = 0.0f;
    m_solarRadiation = 0.0f;
}

WeatherEntry::WeatherEntry(const Date& date, const Time& time, float speed, float temp, float solarRad)
{
    m_date = date;
    m_time = time;
    m_windSpeed = speed;
    m_temperature = temp;
    m_solarRadiation = solarRad;
}

Date WeatherEntry::GetDate() const
{
    return m_date;
}

Time WeatherEntry::GetTime() const
{
    return m_time;
}

float WeatherEntry::GetWindSpeed() const
{
    return m_windSpeed;
}

float WeatherEntry::GetTemperature() const
{
    return m_temperature;
}

float WeatherEntry::GetSolarRadiation() const
{
    return m_solarRadiation;
}

// --- Setters ---

void WeatherEntry::SetDate(const Date& date)
{
    m_date = date;
}

void WeatherEntry::SetTime(const Time& time)
{
    m_time = time;
}

void WeatherEntry::SetWindSpeed(float speed)
{
    m_windSpeed = speed;
}

void WeatherEntry::SetTemperature(float temp)
{
    m_temperature = temp;
}

void WeatherEntry::SetSolarRadiation(float solarRad)
{
    m_solarRadiation = solarRad;
}

bool WeatherEntry::operator==(const WeatherEntry& other) const
{
    return (m_date.GetDay() == other.m_date.GetDay() &&
            m_date.GetMonth() == other.m_date.GetMonth() &&
            m_date.GetYear() == other.m_date.GetYear() &&
            m_time.GetHour() == other.m_time.GetHour() &&
            m_time.GetMinute() == other.m_time.GetMinute() &&
            m_time.GetSecond() == other.m_time.GetSecond());
}
