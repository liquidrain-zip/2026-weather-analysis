#include "Date.h"
#include "DateFormatter.h"

Date::Date()
{
    m_day = 0;
    m_month = 0;
    m_year = 0;
}

Date::Date(int day, int month, int year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}

int Date::GetDay() const
{
    return m_day;
}

int Date::GetMonth() const
{
    return m_month;
}

int Date::GetYear() const
{
    return m_year;
}

void Date::SetDay( int day )
{
    if(day >= 1 && day <= 31)
    {
        m_day = day;
    }
}

void Date::SetMonth( int month )
{
    if(month >= 1 && month <= 12)
    {
        m_month = month;
    }
}

void Date::SetYear( int year )
{
    m_year = year;
}

ostream & operator <<( ostream & output, const Date & date )
{
    output << DateFormatter::ToLocale(date);
    return output;
}

istream & operator >>( istream & input, Date & date )
{
    int day = 0, month = 0, year = 0;
    char slash1 = '\0', slash2 = '\0';

    if ( (input >> day) &&
         (input >> slash1) && (slash1 == '/') &&
         (input >> month) &&
         (input >> slash2) && (slash2 == '/') &&
         (input >> year) )
    {
        date.SetDay(day);
        date.SetMonth(month);
        date.SetYear(year);
    }

    return input;
}
