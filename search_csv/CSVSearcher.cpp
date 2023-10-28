#include "Header.h"

bool CSVSearcher::IsFileDataCorrect(ifstream& file)
{
    string line;
    int current_stroka = 0;
    while (getline(file, line))
    {
        string field;
        int current_column = 0;

        while (CatchTheCell(line, field))
        {
            if (columnsTypes[current_column] == "")
            {
                cerr << "Пустой заголовок. Колонка: " << current_column + 1;
                return false;
            }
            if (field == "")
            {
                cerr << "Пустая ячейка. Колонка: " << current_column + 1 << ", строка: " << current_stroka + 1;
                return false;
            }

            if (!CheckDataByType(columnsTypes[current_column], field))
            {
                cerr << "Колонка: " << current_column + 1 << ", строка: " << current_stroka + 1;
                return false;
            }
            current_column++;
        }
        current_stroka++;
    }
    return true;
}
bool CSVSearcher::IsInputDataCorrect(const string& column_name, const string& value)
{
    for (int i = 0; i < columnsNames.size(); i++)
    {
        if (columnsNames[i] == column_name)
            if (CheckDataByType(columnsTypes[i], value))
                return true;
            else
            {
                cerr << " Ошибка ввода.";
                return false;
            }
    }

}
bool CSVSearcher::CheckDataByType(const string& data, const string& type)
{
    if (data == DATE_TYPE)
    {
        if (type.length() != 10)
        {
            cerr << "Некорректный формат даты. ";
            return false;
        }

        int day = stoi(type.substr(0, 2));
        int month = stoi(type.substr(3, 2));
        int year = stoi(type.substr(6, 4));

        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 100 || year > 3000)
        {
            cerr << "Некорректный формат даты. ";
            return false;
        }
    }
    else if (data == INTEGER_TYPE)
    {
        try
        {
            size_t pos;
            int number = stoi(type, &pos);

            if (pos != type.length())
            {
                cerr << "Некорректный формат данных integer. ";
                return false;
            }
        }
        catch (const invalid_argument& e)
        {
            cerr << "Некорректный формат данных integer. ";
            return false;
        }
        catch (const out_of_range& e)
        {
            cerr << "Слишком большое число integer. ";
            return false;
        }
    }
    else if (data == FLOAT_TYPE)
    {
        try
        {
            size_t pos;
            float number = stof(type, &pos);

            if (pos != type.length())
            {
                cerr << "Некорректный формат данных float. ";
                return false;
            }
        }
        catch (const invalid_argument& e)
        {
            cerr << "Некорректный формат данных float. ";
            return false;
        }
        catch (const out_of_range& e)
        {
            cerr << "Слишком большое число float. ";
            return false;
        }
    }
    return true;
}
bool CSVSearcher::CatchTheCell(string& str, string& result)
{
    char quotes = '\"';
    size_t quotesIndex = 0, delimiterIndex = string::npos;
    if (str[0] == quotes)
        quotesIndex = str.find(quotes, 1);
    while (quotesIndex != 0 && quotesIndex + 1 < str.length())
    {
        if (str[quotesIndex + 1] == quotes)
            quotesIndex = str.find(quotes, quotesIndex + 2);
        else
        {
            delimiterIndex = quotesIndex + 1;
            break;
        }
    }


    if(delimiterIndex == string::npos || str[delimiterIndex] != quotes)
        delimiterIndex = str.find(delimiter, quotesIndex);

    while (delimiterIndex != string::npos)
    {
        result = str.substr(0, delimiterIndex);
        str.erase(0, delimiterIndex + 1);
        return true;
    }
    if (!str.empty())
    {
        result = str;
        str.clear();
        return true;
    }
    return false;
}

void CSVSearcher::GetHeaderNameAndType(ifstream& file)
{
    getline(file, headers);
    istringstream iss(headers);
    string header, line = headers;
    int currentColumn = 0;
    while (CatchTheCell(line, header))
    {
        istringstream HeaderData(header);
        string headerName, headerDataType;
        HeaderData >> headerName;
        HeaderData >> headerDataType;
        columnsNames.push_back(headerName);
        if(headerDataType == STRING_TYPE ||headerDataType == DATE_TYPE ||headerDataType == INTEGER_TYPE ||headerDataType == FLOAT_TYPE)
            columnsTypes.push_back(headerDataType);
        else
        {
            cursedData = true;
            cerr << "Недопустимый тип данных колонки №" << currentColumn +1;
            return;
        }
        currentColumn++;
    }
}
void CSVSearcher::ColumnToSearch(const string& columnToFind)
{
    int currentColumn = 0;

    for (int currentColumn = 0; currentColumn < columnsNames.size(); currentColumn++)
    {
        if (columnsNames[currentColumn] == columnToFind)
        {
            columnToSearch = currentColumn;
            return;
        }
    }

    cursedData = true;
    cerr << "Ошибка. Колонка с названием " << columnToFind << " не найдена\n";
}
CSVSearcher::CSVSearcher(const string& filename) : filename(filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Ошибка. Не удалось открыть файл " << filename;
        cursedData = true;
        return;
    }
    GetHeaderNameAndType(file);

    if (cursedData || !IsFileDataCorrect(file))
    {
        cerr << "\nОшибка. Неверный формат данных файла " << filename;
        cursedData = true;
    }

    file.close();
}

string CSVSearcher::StringToCSVFormat(const string& str)
{
    string strCSV = str;
    char quotes = '\"';

    if (strCSV.find_first_of(";\"") != string::npos)
    {
        size_t quotesIndex = strCSV.find(quotes);
        while (quotesIndex != string::npos)
        {
            strCSV.insert(strCSV.begin() + quotesIndex, quotes);
            quotesIndex = strCSV.find(quotes, quotesIndex+2);
        }
        strCSV.insert(strCSV.begin(), quotes);
        strCSV.insert(strCSV.end(), quotes);
    }

    return strCSV;
}
vector<string> CSVSearcher::SearchByColumn(string& column_name, string& value)
{
    vector<string> results;

    if (cursedData || !IsInputDataCorrect(column_name, value))
        return results;

    ifstream file(filename);

    column_name = StringToCSVFormat(column_name);
    value = StringToCSVFormat(value);

    ColumnToSearch(column_name);

    string lineToSave, line;
    // игнорируем шапку таблицы
    getline(file, line);
    while (getline(file, line))
    {
        string field;
        lineToSave = line;
        int current_column = 0;

        while (CatchTheCell(line, field))
        {
            if (current_column == columnToSearch)
            {
                if (field == value)
                {
                    results.push_back(lineToSave);
                    break;
                }
            }
            current_column++;
        }
    }

    file.close();
    return results;
}
void CSVSearcher::SaveResultToFile(vector<string> result, const string& file_name)
{
    if (cursedData)
        return;
    if (result.empty())
    {
        cerr << "Искомая строка не найдена.";
        return;
    }
    ofstream file(file_name);
    file << headers << "\n";

    for (int i = 0; i < result.size() && result.size() > 0; i++)
        file << result[i] << "\n";
    cout << "Успех";
    file.close();
}