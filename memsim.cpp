#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include <stdio.h>
//#include <cstdlib> //for literally only for atoi
using namespace std;

const int PAGESIZE = 4096; //4 KB (4096 bytes)

int main(int argc, char *argv[]){
    if (argc != 5){
        string arguments = (argc < 5) ? "few" : "many";
        cout << "too " << arguments << " arguments given. Please use the following format:\nmemsim <tracefile> <nframes> <lru|fifo|vms> <debug|quiet>" << endl;
        exit(1);
    }

    bool debug = false; //set debug to false unless...
    if(strcmp(argv[4], "debug") == 0){ //...the argument is set to debug 
        debug = true;
    }

    string traceFile(argv[1]); //store the traceFile

    int nFrames = atoi(argv[2]); //store the number of frames
    
    int algorithm = 0; //set algorithm to 0(LRU) by default unless...
    if(strcmp(argv[3], "fifo")  == 0){//...the argument given is FIFO thus setting algorithm to 1(FIFO) or...
        algorithm = 1;
    } else if(strcmp(argv[3], "vms") == 0){ //...the argument given is VMS thus setting algorithm to 2(VMS)
        algorithm = 2;
    } else if(strcmp(argv[3], "vms") != 0){ //only used for debuging to tell if the argument was invalid
        if(debug) cout<<"defaulting to LRU since argument was invalid"<< endl;
    }
    

    if(debug){ //debug information
        cout << "traceFile: " << traceFile << endl;
        cout << "nFrames: " << nFrames << endl;
        cout << "algorithm: " << argv[3] << "(" << algorithm << ")" << endl;
        cout << "debug: true (obviously)" << endl ;
    }
    
}