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

struct MonthData
{
    MonthData() : month(0), dayData() {}

    int month = 0;
    DayMap dayData;

    bool operator<(const MonthData& other) const { return month < other.month; }
    bool operator>(const MonthData& other) const { return month > other.month; }
    bool operator==(const MonthData& other) const { return month == other.month; }
};

struct YearData
{
    YearData() : year(0), monthTree() {}

    int year = 0;
    Bst<MonthData> monthTree;

    bool operator<(const YearData& other) const { return year < other.year; }
    bool operator>(const YearData& other) const { return year > other.year; }
    bool operator==(const YearData& other) const { return year == other.year; }
};

template <typename T>
using visit_t = void (*)(T&, void*);

#endif // UTILS_H_INCLUDED
