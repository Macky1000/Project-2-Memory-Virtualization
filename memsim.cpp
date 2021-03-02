#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
using namespace std;

//#include "VMSim.h"

const int PAGESIZE = 4096; //4 KB (4096 bytes)

/*int totalW;
int totalR;
int eventsNum;
int nFrames;*/

void printResults(const int& nFrames, const int& eventsNum, const int& totalR, const int& totalW);

int getVPN(unsigned addr){
    int ret = addr/PAGESIZE;
    return ret;
}

int main(int argc, char *argv[]){
    //declare our variables we wanna track ()
    int totalW;
    int totalR;
    int eventsNum;
    

    if (argc < 5 || argc > 6){
        string arguments = (argc < 5) ? "few" : "many";
        cout << "too " << arguments << " arguments given. Please use the following format:\nmemsim <tracefile> <nframes> <lru|fifo|vms> <p>(only with vms) <debug|quiet>" << endl;
        exit(1);
    }

    //VM* vm = new VM()

    string traceFile = argv[1]; //store the traceFile

    int nFrames = atoi(argv[2]); //store the number of frames
    
    int algorithm = 0; //set algorithm to 0(LRU) by default unless...
    if(strcmp(argv[3], "fifo")  == 0){//...the argument given is FIFO thus setting algorithm to 1(FIFO) or...
        algorithm = 1;
    } else if(strcmp(argv[3], "vms") == 0){ //...the argument given is VMS thus setting algorithm to 2(VMS)
        algorithm = 2;
    }

    int i = (algorithm == 2) ? 5 : 4; //see if the algorithm chosen was vms and if we need to shift this all to account for <p>
    bool debug = false; //set debug to false unless...
    if(strcmp(argv[i], "debug") == 0){ //...the argument is set to debug 
        debug = true;
    }

    int percentage = 100; //default percentage to 100
    if(algorithm == 2){ //if we're using vms then record the percent
        percentage = atoi(argv[4]); //store percentage of the total program memory
    }

    if(debug){ //debug information
        cout << "------------------------------\n<Debug Information>"<< endl;

        cout << "traceFile: " << traceFile << endl;
        cout << "nFrames: " << nFrames << endl;
        cout << "algorithm: " << argv[3] << "(" << algorithm << ")";
        if(strcmp(argv[3], "lru") != 0 && algorithm == 0){ //only used for debuging to tell if the argument was invalid
            if(debug){cout <<" (defaulting to LRU(0) since argument was invalid)";}
        }
        if(i==5){cout << "\npercentage: " << percentage;}
        cout << "\ndebug: true (obviously)" << endl ;
        cout << "------------------------------\n"<< endl;

        /*test
        totalW = 1;
        totalR = 10;
        eventsNum = 100;
        printResults(nFrames, eventsNum, totalR, totalW);*/
    }
    
    FILE* fp;
    unsigned addr;
    char rw;
    fp = fopen("bzip.trace", "r");
    fscanf(fp,"%x %c", &addr, &rw);
    cout << hex << addr << dec <<  " " << rw << endl;
    cout << hex << getVPN(addr) << dec << endl;



}

void printResults(const int& nFrames, const int& eventsNum, const int& totalR, const int& totalW){
    cout << "Total memory frames: " << nFrames << endl;
    cout << "Events in trace: " << eventsNum << endl;
    cout << "total disk reads: " << totalR << endl;
    cout << "total disk writes: " << totalW << endl;
}