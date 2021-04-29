#include "DeValues.h"
#include <iostream>

using namespace std;

DeValues::DeValues(){}

DeValues::~DeValues(){}

string DeValues::decString(string rec){
    return rec.substr(1);
}

int DeValues::decInt(string rec){
    return stoi(rec.substr(1));
}

/*
int* DeValues::StringToIntP(string input,int size,int* ret){
    int shift = 0;
    unsigned int plength=0;
    for(int i=0;i<size;i++){
        plength = Decode255(input.substr(shift,2));
        ret[i] = stoi(input.substr(shift+2,plength));
        shift+=(2+plength);
    }
    return ret;
}

float* DeValues::StringToFloatP(string input,int size,float* ret){
    int shift = 0;
    unsigned int plength=0;
    for(int i=0;i<size;i++){
        plength = Decode255(input.substr(shift,2));
        ret[i] = stof(input.substr(shift+2,plength));
        shift+=(2+plength);
    }
    return ret;
}

double* DeValues::StringToDoubleP(string input,int size,double* ret){
    int shift = 0;
    unsigned int plength=0;
    for(int i=0;i<size;i++){
        plength = Decode255(input.substr(shift,2));
        ret[i] = stod(input.substr(shift+2,plength));
        shift+=(2+plength);
    }
    return ret;
}

char* DeValues::StringToCharP(string input,int size,char* ret){
    int shift = 0;
    for(int i=0;i<size-1;i++){
        ret[i] = input.substr(shift+2,1)[0];
        shift+=(2+1);
    }
    return ret;
}

string* DeValues::StringToStringP(string input,int size,string* ret){
    int shift = 0;
    unsigned int plength=0;
    for(int i=0;i<size;i++){
        plength = Decode255(input.substr(shift,2));
        ret[i] = input.substr(shift+2,plength);
        shift+=(2+plength);
    }
    return ret;
}

bool* DeValues::StringToBoolP(string input,int size,bool* ret){
    int shift = 0;
    for(int i=0;i<size;i++){
        ret[i] = stoi(input.substr(shift+2,1));
        shift+=(2+1);
    }
    return ret;
}
*/
unsigned int DeValues::Decode255(string code){
    unsigned int hossz = 0;
    unsigned int mult = 1;
    for (int i = 1; i >= 0; i--)
    {
        hossz += ((unsigned char)code[i] * mult);
        mult *= 256;
    }
    return hossz;
}