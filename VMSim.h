#ifndef __VMSim_H
#define __VMSim_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
using namespace std;


//forget all about this stuff.



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
        int pgNum;
    public:

};

//im just listing these for now but they have to be high level functions but i think they ment high order functions where we can pass them through other functions
void fifo();
void lru();
void segmentedFifo(); //rename to segmented-fifo()

void printResults();

//page table
vector<Page*> pageTable;

extern string traceFile;
extern int algorithm;
extern bool debug;
extern int percentage;
extern int nFrames;

extern int totalR;
extern int totalW;
extern int eventsNum;


#endif