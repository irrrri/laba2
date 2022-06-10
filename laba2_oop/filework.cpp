#include "filework.h"

void fileWork::readData()
{
    FILE* file = fopen(this->filename, "r");
    std::string s;
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* line = new char[size];
    while(!feof(file)){
        fgets(line, size+1, file);
        s.append(line);
    }
    fclose(file);
    this->str=s;
   }

fileWork::fileWork(char* filename)
{
    this->filename=new char[strlen(filename)];
    strcpy(this->filename, filename);
}

std::string fileWork::getStr()
{
    return this->str;
}




