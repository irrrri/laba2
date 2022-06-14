#include "fileworker.h"

void fileWorker::readData()
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
    delete[] line;
    delete [] this ->filename;
}

fileWorker::fileWorker(char* filename)
{
    this->filename=new char[strlen(filename)];
    strcpy(this->filename, filename);
}

std::string fileWorker::getStr()
{
    return this->str;
}




