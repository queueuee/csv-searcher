#include "Header.h"

int main(int argc, char*argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string input_in;
    string input_out;
    string encoding;
    string input_col;
    string input_exp;

    for (int i = 1; i < argc; i += 2)
    {
        string option = argv[i];
        string value = argv[i + 1];

        if (option == "-in")
            input_in = value;
        else if (option == "-out")
            input_out = value;
        else if (option == "-enc")
            encoding = value;
        else if (option == "-col")
            input_col = value;
        else if (option == "-exp")
            input_exp = value;
        else 
        {
            cerr << "Ошибка. Некорректный параметр: " << option << "\n";
            cerr << "Попробуйте в данных для поиска заменить пробелы на '_'";
            return 1;
        }
    }

    CSVSearcher search_csv_a(input_in);
    vector<string> res = search_csv_a.SearchByColumn(input_col, input_exp);
    search_csv_a.SaveResultToFile(res, input_out);
}