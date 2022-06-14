#ifndef JSONCHECKER_H
#define JSONCHECKER_H

#include <iostream>
#include <string>
#include <exception>



using namespace std;

class JsonException: public std::exception
{
private:
    string msg;
    int place;
public:
    JsonException(string error, int place)
    {
        this->msg = error;
        this->place=place;
    }
    int getPlace() {return place;}
    string getMessage(){return msg;}
};


#endif // JSONCHECKER_H
