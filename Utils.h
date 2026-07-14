#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "Date.h"
#include "Time.h"
#include "Vector.h"
#include "WeatherEntry.h"
#include "Bst.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <map>

/**
 * @class Utils
 * @brief Global utility definitions, common namespace, and file configurations.
 *
 * @author 34528531
 * @version 01
 * @date 30/05/2026 34528531, Initial creation and definition of standard delimiters.
 *
 * @author 34528531
 * @version 02
 * @date 09/06/2026 34528531, Added WindRecType and WindlogType.
 *
 * @author 34528531
 * @version 03
 * @date 18/06/2026 34528531, Replaced with new struct.
 */

// Stream using declarations
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::cin;

// String and utility using declarations
using std::string;
using std::stringstream;
using std::getline;
using std::stoi;
using std::stol;
using std::stof;
using std::invalid_argument;
using std::out_of_range;
using std::abs;

/**
 * @brief Character constant used to split fields within CSV input data streams.
 */
const char CSV_DELIMITER = ',';

/**
 * @brief Character constant used to split fields within date string input data streams.
 */
const char DATE_DELIMITER = '/';

/**
 * @brief Character constant used to split fields within time string input data streams.
 */
const char TIME_DELIMITER = ':';

/**
 * @brief List of months
 */
const string MonthNames[] =
{
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

/**
 * @brief Data structure for holding weather entries in a Vector
 */
typedef Vector<WeatherEntry> WeatherData;

/**
 * @struct DayMap
 * @brief Stores the data for the day.
 */
using DayMap = map<int, WeatherData>;

/**
 * @struct MonthData
 * @brief Stores all data for a single month, held within a YearData's BST.
 */
struct MonthData
{
    MonthData() : month(0), dayData() {}

    int month = 0;
    DayMap dayData;

    bool operator<(const MonthData& other) const
    {
        return month < other.month;
    }
    bool operator>(const MonthData& other) const
    {
        return month > other.month;
    }
    bool operator==(const MonthData& other) const
    {
        return month == other.month;
    }
};

/**
 * @struct YearData
 */
struct YearData
{
    YearData() : year(0), monthTree() {}

    int year = 0;
    Bst<MonthData> monthTree;

    bool operator<(const YearData& other) const
    {
        return year < other.year;
    }
    bool operator>(const YearData& other) const
    {
        return year > other.year;
    }
    bool operator==(const YearData& other) const
    {
        return year == other.year;
    }
};
#endif // UTILS_H_INCLUDED
