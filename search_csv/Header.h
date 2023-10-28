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
    // �������� �����
    string filename;
    // ����� �������
    string headers;
    // �����������
    char delimiter = ';';
    // ������� ��� ������
    int columnToSearch = 0;
    // ��� ������� / �������� �������
    vector<string> columnsTypes, columnsNames;
    // ��������� ���� ������ � ��������
    const string STRING_TYPE = "String", DATE_TYPE = "Date", INTEGER_TYPE = "Integer", FLOAT_TYPE = "Float";
    // ����������� ������
    bool cursedData = false;

    // �������� �������� ����� �� ������
    bool IsFileDataCorrect(ifstream& file);
    // �������� ������ ��� ������ �� ������������ ���� �������
    bool IsInputDataCorrect(const string& column_name, const string& value);
    // �������� ������ �� ������������ ����
    bool CheckDataByType(const string& data, const string& type);
    // ��������� ����� ������� �� ����� ������� � �� ����
    void GetHeaderNameAndType(ifstream& file);
    // ����������� ������� �������, ������� ���� ������
    void ColumnToSearch(const string& columnToFind);
    // ��������� ������ �� ������
    bool CatchTheCell(string& str, string& result);
    // ������� ������ � csv ������
    string StringToCSVFormat(const string& str);
public:
    CSVSearcher(const string& filename);
    // ����� � �������� ������� �������� ��������
    vector<string> SearchByColumn(string& column_name, string& value);
    // ���������� ���������� � ����
    void SaveResultToFile(vector<string> result, const string& file_name);
};
