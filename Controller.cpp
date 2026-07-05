#include "Controller.h"

void Controller::DisplayMenu()
{
    cout << "\nWeather Data\n";
    cout << "-------------------------\n";
    cout << "1. Average wind speed and sample standard deviation (specific month and year)\n";
    cout << "2. Average ambient air temperature and sample standard deviation (each month of a year)\n";
    cout << "3. Total solar radiation (each month of a year)\n";
    cout << "4. Output monthly summary to file (WindTempSolar.csv)\n";
    cout << "5. Exit\n";
    cout << "-------------------------\n";
}

int Controller::LoadRecords(WeatherData & weatherdata, const string & filename)
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
            if (col == dateTimeIndex)
            {
                 dateTimeStr = token;
            }
            else if (col == windSpeedIndex)
            {
                 windSpeedStr = token;
            }
            else if (col == tempIndex)
            {
                 tempStr = token;
            }
            else if (col == solarRadIndex)
            {
                 solarRadStr = token;
            }

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
            // --- Parse Date ---
            getline(dateTimeStream, tempVal, '/');
            weatherEntry.m_date.SetDay(stoi(tempVal));

            getline(dateTimeStream, tempVal, '/');
            weatherEntry.m_date.SetMonth(stoi(tempVal));

            getline(dateTimeStream, tempVal, ' ');
            weatherEntry.m_date.SetYear(stoi(tempVal));

            // --- Parse Time ---
            getline(dateTimeStream, tempVal, ':');
            weatherEntry.m_time.SetHour(stoi(tempVal));

            getline(dateTimeStream, tempVal, ':');
            weatherEntry.m_time.SetMinute(stoi(tempVal));

            getline(dateTimeStream, tempVal);
            weatherEntry.m_time.SetSecond(stoi(tempVal));

            weatherEntry.m_windSpeed = stof(windSpeedStr) * 3.6f;
            weatherEntry.m_temperature = stof(tempStr);
            weatherEntry.m_solarRadiation = stof(solarRadStr);
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

        // Store Record
        weatherdata.Insert(weatherEntry, index);
        index++;
    }

    inFile.close();
    return index;
}

int Controller::LoadFromSourceFile(WeatherData & weatherData, const string & filename)
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

void Controller::ProcessMenuChoice(int choice, const WeatherData& weatherData)
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
        cout << "Enter the year (e.g., 2025): ";
        if (!(cin >> year))
        {
            cout << "Invalid year. Returning to menu.\n";
            return;
        }
        monthlyTotalSolarRadiation(year, weatherData);
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

WeatherData Controller::getRecordsForMonthAndYear(int month, int year, const WeatherData& weatherData) const
{
    WeatherData filteredRecords;
    int insertIndex = 0;

    if (month < 1 || month > 12)
    {
        return filteredRecords;
    }

    for (int i = 0; i < weatherData.getCount(); ++i)
    {
        const WeatherEntry& weatherEntry = weatherData[i];
        if (weatherEntry.m_date.GetMonth() == month && weatherEntry.m_date.GetYear() == year)
        {
            filteredRecords.Insert(weatherEntry, insertIndex);
            insertIndex++;
        }
    }

    return filteredRecords;
}

void Controller::averageWindSpeedAndStdev(int month, int year, const WeatherData& weatherData) const
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

// Menu Option 2
void Controller::monthlyTemperatureAveragesAndStdev(int year, const WeatherData& weatherData) const
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

void Controller::monthlyTotalSolarRadiation(int year, const WeatherData& weatherData) const
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

        double totalSolarRad = Calculate::Total(filtered, "SR") / 1000.0;

        cout << fixed << setprecision(1) << totalSolarRad << " kWh/m2" << endl;
    }
}

void Controller::outputSummary(int year, const WeatherData& weatherData) const
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
            continue; // Skip month if no data
        }

        hasAnyMonthlyData = true;

        double avgSpeed = Calculate::Average(filtered, "S");
        double stDevSpeed = Calculate::StandardDeviation(filtered, avgSpeed, "S");
        double avgTemp = Calculate::Average(filtered, "T");
        double stDevTemp = Calculate::StandardDeviation(filtered, avgTemp, "T");
        double totalSolarRad = Calculate::Total(filtered, "SR") / 1000.0; // kWh/m2

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
}
