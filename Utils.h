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

using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::cin;
using std::string;
using std::stringstream;
using std::getline;
using std::stoi;
using std::stol;
using std::stof;
using std::invalid_argument;
using std::out_of_range;
using std::abs;
using std::map;

const char CSV_DELIMITER = ',';
const char DATE_DELIMITER = '/';
const char TIME_DELIMITER = ':';

const string MonthNames[] =
{
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

typedef Vector<WeatherEntry> WeatherData;

/**
 * @struct DayMap
 * @brief Stores the data for the day.
 */
typedef map<int, WeatherData> DayMap;

/**
 * @struct MonthData
 * @brief Represents a container for weather data organized by month.
 * * Stores the numerical representation of a month alongside a map containing
 * all daily weather records associated with that month. Implements comparison
 * operators to facilitate ordering within a Binary Search Tree.
 */
struct MonthData
{
    MonthData() : month(0), dayData() {}

    int month = 0;
    DayMap dayData;

    bool operator<(const MonthData& other) const { return month < other.month; }
    bool operator>(const MonthData& other) const { return month > other.month; }
    bool operator==(const MonthData& other) const { return month == other.month; }
};

/**
 * @struct YearData
 * @brief Represents a container for weather data organized by year.
 * * Stores a specific calendar year alongside a Binary Search Tree containing
 * MonthData nodes. Implements comparison operators to allow alphabetical or
 * chronological sorting within a hierarchical data structure.
 */
struct YearData
{
    YearData() : year(0), monthTree() {}

    int year = 0;
    Bst<MonthData> monthTree;

    bool operator<(const YearData& other) const { return year < other.year; }
    bool operator>(const YearData& other) const { return year > other.year; }
    bool operator==(const YearData& other) const { return year == other.year; }
};

/**
 * @typedef visit_t
 * @brief Type alias for a traversal callback function pointer.
 * @tparam T The data type of the element stored within the node being visited.
 * @param T& A reference to the data payload inside the currently visited tree node.
 * @param void* A generic void pointer used to pass external context or accumulator state into the callback.
 */
template <typename T>
using visit_t = void (*)(T&, void*);

/**
 * @struct SPCC_Collector
 * @brief A context payload structure used during BST traversals to accumulate weather data for statistical analysis.
 * * This structure is passed via a void pointer into callback functions to gather corresponding
 * measurements across multiple years for a specific month, enabling the calculation of the
 * Sample Pearson Correlation Coefficient (SPCC) between different weather phenomena.
 */
struct SPCC_Collector
{
    int targetMonth;
    Vector<float> all_S;
    Vector<float> all_T;
    Vector<float> all_R;
};
#endif // UTILS_H_INCLUDED
