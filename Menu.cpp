#include "Menu.h"

// Collector and visit callback for option 3 tree traversal
struct SPCC_Collector
{
    int targetMonth;
    Vector<float> all_S;
    Vector<float> all_T;
    Vector<float> all_R;
};

static void sPCC_Visit_Func(YearData& yearData, void* userData)
{
    SPCC_Collector* collector = static_cast<SPCC_Collector*>(userData);
    MonthData searchMonth;
    searchMonth.month = collector->targetMonth;
    MonthData* monthNode = yearData.monthTree.Search(searchMonth);

    if (monthNode != nullptr)
    {
        for (DayMap::const_iterator it = monthNode->dayData.begin(); it != monthNode->dayData.end(); ++it)
        {
            const WeatherData& dayVector = it->second;
            for (int i = 0; i < dayVector.getCount(); ++i)
            {
                const WeatherEntry& rec = dayVector[i];
                collector->all_S.Insert(rec.GetWindSpeed(), collector->all_S.getCount());
                collector->all_T.Insert(rec.GetTemperature(), collector->all_T.getCount());
                collector->all_R.Insert(rec.GetSolarRadiation(), collector->all_R.getCount());
            }
        }
    }
}


void Menu::DisplayMenu()
{
    cout << "\nWeather Data\n";
    cout << "-------------------------\n";
    cout << "1. Average wind speed and sample standard deviation (specific month and year)\n";
    cout << "2. Average ambient air temperature and sample standard deviation (each month of a year)\n";
    cout << "3. Calculate sPCC result for S_T, S_R & T_R (specific month for all years)\n";
    cout << "4. Output monthly summary to file (WindTempSolar.csv)\n";
    cout << "5. Exit\n";
    cout << "-------------------------\n";
}

int Menu::LoadRecords(DataDB & weatherdata, const string & filename)
{
    int index = 0;
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cout << "Error: Could not open file " << filename << endl;
        return -1;
    }

    string headerLine;
    if (!getline(inFile, headerLine))
    {
        cout << "Error: Could not read header line from file " << filename << endl;
        inFile.close();
        return -1;
    }

    stringstream headerStream(headerLine);
    string headerToken;
    int currentColumn = 0;

    int dateTimeIndex = -1;
    int windSpeedIndex = -1;
    int tempIndex = -1;
    int solarRadIndex = -1;

    while (getline(headerStream, headerToken, CSV_DELIMITER))
    {
        if (headerToken == "WAST") dateTimeIndex = currentColumn;
        else if (headerToken == "S") windSpeedIndex = currentColumn;
        else if (headerToken == "T") tempIndex = currentColumn;
        else if (headerToken == "SR") solarRadIndex = currentColumn;

        currentColumn++;
    }

    if (dateTimeIndex == -1 || windSpeedIndex == -1 || tempIndex == -1 || solarRadIndex == -1)
    {
        cout << "Error: One or more required columns not found in the header." << endl;
        inFile.close();
        return -1;
    }

    string line;
    while(getline(inFile, line))
    {
        if (line.empty() || line[0] == '\r')
        {
            continue;
        }

        stringstream ss(line);
        string token;
        int col = 0;

        string dateTimeStr, windSpeedStr, tempStr, solarRadStr;

        while (getline(ss, token, CSV_DELIMITER))
        {
            if (col == dateTimeIndex) { dateTimeStr = token; }
            else if (col == windSpeedIndex) { windSpeedStr = token; }
            else if (col == tempIndex) { tempStr = token; }
            else if (col == solarRadIndex) { solarRadStr = token; }
            col++;
        }

        if (dateTimeStr.empty() || windSpeedStr.empty() || tempStr.empty() || solarRadStr.empty())
        {
            continue;
        }

        WeatherEntry weatherEntry;
        stringstream dateTimeStream(dateTimeStr);
        string tempVal;

        try
        {
            Date tempDate;
            getline(dateTimeStream, tempVal, '/');
            tempDate.SetDay(stoi(tempVal));

            getline(dateTimeStream, tempVal, '/');
            tempDate.SetMonth(stoi(tempVal));

            getline(dateTimeStream, tempVal, ' ');
            tempDate.SetYear(stoi(tempVal));

            weatherEntry.SetDate(tempDate);

            Time tempTime;
            getline(dateTimeStream, tempVal, ':');
            tempTime.SetHour(stoi(tempVal));

            getline(dateTimeStream, tempVal, ':');
            tempTime.SetMinute(stoi(tempVal));

            getline(dateTimeStream, tempVal);
            tempTime.SetSecond(stoi(tempVal));

            weatherEntry.SetTime(tempTime);

            weatherEntry.SetWindSpeed(stof(windSpeedStr) * 3.6f);
            weatherEntry.SetTemperature(stof(tempStr));
            weatherEntry.SetSolarRadiation(stof(solarRadStr));
        }
        catch (const invalid_argument& e)
        {
            cout << "Warning: Skipped record due to non-numeric data fields." << endl;
            continue;
        }
        catch (const out_of_range& e)
        {
            cout << "Warning: Skipped record due to numeric value out of range." << endl;
            continue;
        }

        weatherdata.Insert(weatherEntry);
        index++;
    }

    inFile.close();
    return index;
}

int Menu::LoadFromSourceFile(DataDB & weatherData, const string & filename)
{
    ifstream sourceFile(filename);
    if (!sourceFile.is_open())
    {
        cout << "Error: Could not open source file: " << filename << endl;
        return -1;
    }

    string subFilename;
    int totalRecords = 0;
    int filesProcessed = 0;

    while (getline(sourceFile, subFilename))
    {
        int records = LoadRecords(weatherData, "data/" + subFilename);

        if (records >= 0)
        {
            totalRecords += records;
            filesProcessed++;
            cout << records << " records loaded." << endl;
        }
    }

    sourceFile.close();
    return totalRecords;
}

void Menu::ProcessMenuChoice(int choice, DataDB& weatherData)
{
    int month = -1;
    int year = -1;

    switch (choice)
    {
    case 1:
        cout << "Enter the month (1-12): ";
        if (!(cin >> month) || month < 1 || month > 12)
        {
            cout << "Invalid month. Returning to menu.\n";
            return;
        }
        cout << "Enter the year (e.g., 2025): ";
        if (!(cin >> year))
        {
            cout << "Invalid year. Returning to menu.\n";
            return;
        }
        averageWindSpeedAndStdev(month, year, weatherData);
        break;
    case 2:
        cout << "Enter the year (e.g., 2025): ";
        if (!(cin >> year))
        {
            cout << "Invalid year. Returning to menu.\n";
            return;
        }
        monthlyTemperatureAveragesAndStdev(year, weatherData);
        break;
    case 3:
        cout << "Enter the month (1-12): ";
        if (!(cin >> month) || month < 1 || month > 12)
        {
            cout << "Invalid month. Returning to menu.\n";
            return;
        }
        displaySPCC(month, weatherData);
        break;
    case 4:
        cout << "Enter the year (e.g., 2025): ";
        if (!(cin >> year))
        {
            cout << "Invalid year. Returning to menu.\n";
            return;
        }
        outputSummary(year, weatherData);
        break;
    case 5:
        cout << "Exiting program.\n";
        break;
    default:
        cout << "Invalid choice. Please enter a number between 1 and 5.\n";
    }
}

WeatherData Menu::getRecordsForMonthAndYear(int month, int year, const DataDB& weatherData) const
{
    WeatherData filteredRecords;
    int insertIndex = 0;

    if (month < 1 || month > 12)
    {
        return filteredRecords;
    }

    const DayMap* dayMap = weatherData.GetMonthData(year, month);
    if (dayMap == nullptr)
    {
        return filteredRecords;
    }

    for (DayMap::const_iterator it = dayMap->begin(); it != dayMap->end(); ++it)
    {
        const WeatherData& dayVector = it->second;
        for (int i = 0; i < dayVector.getCount(); ++i)
        {
            filteredRecords.Insert(dayVector[i], insertIndex);
            insertIndex++;
        }
    }

    return filteredRecords;
}

void Menu::averageWindSpeedAndStdev(int month, int year, const DataDB& weatherData) const
{
    WeatherData filtered = getRecordsForMonthAndYear(month, year, weatherData);

    cout << MonthNames[month] << " " << year << ": ";

    if (filtered.getCount() == 0)
    {
        cout << "No Data" << endl;
        return;
    }

    double avgSpeed = Calculate::Average(filtered, "S");
    double stDevSpeed = Calculate::StandardDeviation(filtered, avgSpeed, "S");

    cout << "Average speed: " << fixed << setprecision(1) << avgSpeed << " km/h ";
    cout << "Sample stdev: " << fixed << setprecision(1) << stDevSpeed << endl;
}

void Menu::monthlyTemperatureAveragesAndStdev(int year, const DataDB& weatherData) const
{
    cout << year << endl;

    for (int month = 1; month <= 12; ++month)
    {
        WeatherData filtered = getRecordsForMonthAndYear(month, year, weatherData);

        cout << MonthNames[month] << ": ";

        if (filtered.getCount() == 0)
        {
            cout << "No Data" << endl;
            continue;
        }

        double avgTemp = Calculate::Average(filtered, "T");
        double stDevTemp = Calculate::StandardDeviation(filtered, avgTemp, "T");

        cout << "average: "
             << fixed << setprecision(1) << avgTemp << " degrees C, "
             << "stdev: " << fixed << setprecision(1) << stDevTemp << endl;
    }
}

void Menu::displaySPCC(int month, DataDB& weatherData) const
{
    SPCC_Collector collector;
    collector.targetMonth = month;

    // Execute tree traversal across all years
    weatherData.TraverseYears(sPCC_Visit_Func, &collector);

    cout << "\nSample Pearson Correlation Coefficient for " << MonthNames[month] << endl;

    if (collector.all_S.getCount() < 2)
    {
        cout << "Not enough data to calculate sPCC for " << MonthNames[month] << "." << endl;
        return;
    }

    double s_t = Calculate::Spcc(collector.all_S, collector.all_T);
    double s_r = Calculate::Spcc(collector.all_S, collector.all_R);
    double t_r = Calculate::Spcc(collector.all_T, collector.all_R);

    cout << "S_T: " << fixed << setprecision(2) << s_t << endl;
    cout << "S_R: " << fixed << setprecision(2) << s_r << endl;
    cout << "T_R: " << fixed << setprecision(2) << t_r << endl;
}

void Menu::outputSummary(int year, const DataDB& weatherData) const
{
    ofstream outputFile("WindTempSolar.csv");
    if (!outputFile.is_open())
    {
        cout << "Error opening WindTempSolar.csv for writing." << endl;
        return;
    }

    outputFile << year << endl;
    bool hasAnyMonthlyData = false;

    for (int month = 1; month <= 12; ++month)
    {
        WeatherData filtered = getRecordsForMonthAndYear(month, year, weatherData);
        int count = filtered.getCount();

        if (count == 0)
        {
            continue;
        }

        hasAnyMonthlyData = true;

        double avgSpeed = Calculate::Average(filtered, "S");
        double stDevSpeed = Calculate::StandardDeviation(filtered, avgSpeed, "S");
        double avgTemp = Calculate::Average(filtered, "T");
        double stDevTemp = Calculate::StandardDeviation(filtered, avgTemp, "T");
        double totalSolarRad = Calculate::Total(filtered, "SR") / 1000.0;

        outputFile << MonthNames[month] << ",";
        outputFile << fixed << setprecision(1) << avgSpeed << "(" << fixed << setprecision(1) << stDevSpeed << "),";
        outputFile << fixed << setprecision(1) << avgTemp << "(" << fixed << setprecision(1) << stDevTemp << "),";
        outputFile << fixed << setprecision(1) << totalSolarRad << endl;
    }

    if (!hasAnyMonthlyData)
    {
        outputFile << "No Data" << endl;
        cout << "No data found for year " << year << ". Output written to WindTempSolar.csv" << endl;
    }
    else
    {
        cout << "Data for year " << year << " written to WindTempSolar.csv" << endl;
    }

    outputFile.close();
} // FIXED: Removed trailing extra closing brace
