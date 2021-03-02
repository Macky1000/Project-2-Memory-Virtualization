#ifndef __VMSim_H
#define __VMSim_H

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

/*class VM{
    private:
        int totalR = 0;
        int totalW = 0;
        int eventsNum = 0;
        int totalMemFrames = 0;
    public:
        VM();
        VM();
        void printResults();
};*/

class Page{
    private:
        
    public:

};

//im just listing these for now but they have to be high level functions but i think they ment high order functions where we can pass them through other functions
void fifo();
void lru();
void segmentedFifo(); //rename to segmented-fifo()

void printResults();

//string traceFile;
int algorithm;
bool debug;
int percentage;
int nFrames;

int totalR;
int totalW;
int eventsNum;


#endif