#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>

using namespace std;

class CSVSearcher
{
private:
    // название файла
    string filename;
    // шапка таблицы
    string headers;
    // разделитель
    char delimiter = ';';
    // колонка дл€ поиска
    int columnToSearch = 0;
    // тип колонки / название колонки
    vector<string> columnsTypes, columnsNames;
    // возможные типы данных в колонках
    const string STRING_TYPE = "String", DATE_TYPE = "Date", INTEGER_TYPE = "Integer", FLOAT_TYPE = "Float";
    // испорченные данные
    bool cursedData = false;

    // проверка входного файла на ошибки
    bool IsFileDataCorrect(ifstream& file);
    // проверка данных дл€ поиска на соответствие типу столбца
    bool IsInputDataCorrect(const string& column_name, const string& value);
    // проверка данных на соответствие типу
    bool CheckDataByType(const string& data, const string& type);
    // разбиение шапки таблицы на имена колонок и их типы
    void GetHeaderNameAndType(ifstream& file);
    // определение индекса колонки, которую надо искать
    void ColumnToSearch(const string& columnToFind);
    // отделение €чейки из строки
    bool CatchTheCell(string& str, string& result);
    // перевод строки в csv формат
    string StringToCSVFormat(const string& str);
public:
    CSVSearcher(const string& filename);
    // поиск в заданной колонке заданное значение
    vector<string> SearchByColumn(string& column_name, string& value);
    // сохранение результата в файл
    void SaveResultToFile(vector<string> result, const string& file_name);
};
