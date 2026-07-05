#ifndef DATEFORMATTER_H_INCLUDED
#define DATEFORMATTER_H_INCLUDED

#include "Date.h"
#include "Utils.h"

/**
 * @class DateFormatter
 * @brief Handles all formatting of Date.
 *
 * @author 34528531
 * @version 01
 * @date 30/05/2026 34528531, Initial.
 */
class DateFormatter
{
    public:
    /**
     * @brief Formats a Date object into a readable locale string (e.g., "16 February 2000").
     * @param date Constant reference to the Date object to format.
     * @return A formatted string representation of the date.
     */
    static string ToLocale(const Date & date);
};

string DateFormatter::ToLocale(const Date & date)
{
    int month = date.GetMonth();
    string monthName = "Invalid Month";

    if (month >= 1 && month <= 12)
    {
        monthName = MonthNames[month];
    }
    stringstream ss;
    ss << date.GetDay() << " " << monthName << " " << date.GetYear();

    return ss.str();
}


#endif // DATEFORMATTER_H_INCLUDED
