#include "stringwork.h"

/*char* QstringToCharArray(QString qstr)
{
    char *str = (char*)malloc(sizeof(char)*(qstr.size() + 1));
    int i;
    for (i = 0; i < qstr.size(); i++)
    {
        str[i] = qstr.at(i).unicode();
    }
    str[i] = 0;
    return str;
}

//Преобразование массива строк в формат QStringList
QStringList ConvertRowToQTFormat(char **row, int size)
{
    QStringList string = {};
    for(int i = 0; i < size; i++){
        string.append(QString::fromUtf8(row[i]));
    }
    return string;
}*/
