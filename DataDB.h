#ifndef DATADB_H_INCLUDED
#define DATADB_H_INCLUDED

#include "Utils.h"

/**
 * @class DataDB
 * @brief Encapsulates the Year->Month->Day nested data structure.
 */
class DataDB
{
public:
    DataDB() : m_yearTree() {}
    ~DataDB() = default;

    /**
     * @brief Inserts a single weather record into the nested data structure.
     * @param record The WeatherRecord to add.
     */
    void Insert(const WeatherEntry& record);

    /**
     * @brief Retrieves the map of day-data for a specific month and year.
     * @param y The year to search for.
     * @param m The month to search for.
     * @return A const pointer to the DayMap, or nullptr if no data exists.
     */
    const DayMap* GetMonthData(int y, int m) const;

    /**
     * @brief Traverses the Year BST, calling the visit function on each YearData.
     * @param visit_func The function pointer to call.
     * @param userData A void pointer to a 'collector' struct.
     */
    void TraverseYears(visit_t<YearData> visit_func, void* userData);

private:
    Bst<YearData> m_yearTree;
};

#endif // DATADB_H_INCLUDED
