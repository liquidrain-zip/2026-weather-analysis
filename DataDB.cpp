#include "DataDB.h"

void DataDB::Insert(const WeatherEntry& record)
{
    const Date& date = record.GetDate();
    int year = date.GetYear();
    int month = date.GetMonth();
    int day = date.GetDay();

    // 1. Find or Create Year
    YearData searchYear;
    searchYear.year = year;
    YearData* yearNode = m_yearTree.Search(searchYear);

    if (yearNode == nullptr)
    {
        m_yearTree.Insert(searchYear);
        yearNode = m_yearTree.Search(searchYear);
    }

    // 2. Find or Create Month
    MonthData searchMonth;
    searchMonth.month = month;
    MonthData* monthNode = yearNode->monthTree.Search(searchMonth);

    if (monthNode == nullptr)
    {
        yearNode->monthTree.Insert(searchMonth);
        monthNode = yearNode->monthTree.Search(searchMonth);
    }

    WeatherData& dayVector = monthNode->dayData[day];
    dayVector.Insert(record, dayVector.getCount());
}

const DayMap* DataDB::GetMonthData(int y, int m) const
{
    // 1. Find Year
    YearData searchYear;
    searchYear.year = y;
    const YearData* yearNode = m_yearTree.Search(searchYear);

    if (yearNode == nullptr)
    {
        return nullptr;
    }

    // 2. Find Month
    MonthData searchMonth;
    searchMonth.month = m;
    const MonthData* monthNode = yearNode->monthTree.Search(searchMonth);

    if (monthNode == nullptr)
    {
        return nullptr;
    }

    return &(monthNode->dayData);
}

void DataDB::TraverseYears(visit_t<YearData> visit_func, void* userData)
{
    m_yearTree.InOrder(visit_func, userData);
}
