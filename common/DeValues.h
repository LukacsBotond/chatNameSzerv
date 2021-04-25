#ifndef DeValues_H
#define DeValues_H

#include <iostream>

class DeValues
{
private:
    /* data */
public:
    DeValues();
    ~DeValues();
    /*
    int* StringToIntP(std::string input,int size,int* ret);
    float* StringToFloatP(std::string input,int size,float* ret);
    double* StringToDoubleP(std::string input,int size,double* ret);
    char* StringToCharP(std::string input,int size,char* ret);
    std::string* StringToStringP(std::string input,int size,std::string* ret);
    bool* StringToBoolP(std::string input,int size,bool* ret);
    */
    unsigned int Decode255(std::string code);
    
};

#endif