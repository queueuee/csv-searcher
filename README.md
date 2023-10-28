# Общее описание программы
Приложение работает с входным файлом в формате CSV (Comma Separated Values). В
файле содержатся табличные данные. Приложение позволяет осуществлять поиск
значению в указанной колонке. Результат поиска (строки, содержащие найденные
значения) выводится в выходной файл в формате CSV
# Как пользоваться программой

#### Приложение запускается из командной строки:
    search_csv.exe –in <входной_файл> –out <выходной_файл> -enc <кодировка> -col <имя_столбца> -exp <выражение_для_поиска>
Параметры проверяются на корректность, в том числе параметр –exp, который зависит от типа колонки указанной в –col.
Входной файл проверяется на корректность формата (в том числе типов данных в колонках)

#### Пример запуска приложения:
    search_csv.exe –in in_file.csv –out out_file.csv -enc UTF-8 -col Дата_рождения -exp 18.06.1983
