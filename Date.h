#ifndef DATE_H
#define DATE_H

#include <iostream>
using std::ostream;
using std::istream;

/**
 * @class Date
 * @brief Holds calendar dates consisting of integers for day, month, and year.
 *
 * @author 34528531
 * @version 01
 * @date 30/05/2026 34528531, Initial.
 */
class Date
{
public:
    /**
     * @brief Default constructor. Initializes date to 0/0/0.
     */
    Date();

    /**
     * @brief Parameterized constructor.
     * @param day The day of the month.
     * @param month The month number (1-12).
     * @param year The calendar year.
     */
    Date(int day, int month, int year);

    /**
     * @brief Gets the day integer.
     * @return The day value.
     */
    int GetDay() const;

    /**
     * @brief Gets the month integer.
     * @return The month value.
     */
    int GetMonth() const;

    /**
     * @brief Gets the year integer.
     * @return The year value.
     */
    int GetYear() const;

    /**
     * @brief Sets the day field with basic validation (1-31).
     * @param day The numerical day.
     */
    void SetDay( int day );

    /**
     * @brief Sets the month field with basic validation (1-12).
     * @param month The numerical month.
     */
    void SetMonth( int month );

    /**
     * @brief Sets the year field.
     * @param year The numerical year.
     */
    void SetYear( int year );

private:
    int m_day;
    int m_month;
    int m_year;
};

/**
 * @brief Overloaded global stream insertion operator to output formatted Date data using Utils.
 */
ostream & operator <<( ostream & output, const Date & date );

/**
 * @brief Overloaded global stream extraction operator to parse slashed date strings.
 */
istream & operator >>( istream & input, Date & date );

#endif // DATE_H
