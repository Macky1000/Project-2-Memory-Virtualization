#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
//#include <map>
using namespace std;

//#include "VMSim.h"

const int PAGESIZE = 4096; //4 KB (4096 bytes)

class Page{
public:
    int pgNum; //maybe not needed
    int validBit;
    int previousAccess;
    bool dirtyFlag;
    Page(int a);
};

Page::Page(int a){
    this->pgNum = a;
    this->validBit = 0;
    this->previousAccess = 0;
    this->dirtyFlag = false;
}

void printResults(const int& nFrames, const int& eventsNum, const int& totalR, const int& totalW);

int getVPN(unsigned addr);

void fifo();
void lru();
void segmentedFifo();

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
    
    //turn it on in a min
    vector<Page*> pageTable;
    vector<unsigned int> addressLookup;
    //map<unsigned int, int> addressLookup;
    /*for (size_t i = 0; i < nFrames; i++)
    {
        if(debug) {cout << "new page num: " << i << endl;}
        Page* newPage = new Page(i);
        pageTable.push_back(newPage);
        if(debug) {
            cout << "PageTable element: " << i << "\nElement's page num: " << pageTable[i]->pgNum << endl;
            cout << "Page's validBit: " << pageTable[i]->validBit << "\nPage previousAccess: " << pageTable[i]->previousAccess << endl;
            cout << "Page dirtyFlag: " << pageTable[i]->dirtyFlag << endl;

            cout << "------------------------------"<< endl;
        }
    }*/

    FILE* fp;
    unsigned addr;
    char rw;
    fp = fopen(argv[1], "r");
    
    int lim = 0; //test for only 20 entries
    while (fscanf(fp,"%x %c", &addr, &rw) != EOF && lim < 20){
        if(debug){
            //cout << addr << endl;
            cout << hex << addr << dec <<  " " << rw << endl;
            cout << hex << getVPN(addr) << dec << endl;
        }

        lim++;
    }



    /*
    unsigned addr;
    char rw;
    //Open input.txt for reading
    ifstream infile(traceFile);
    if (!infile.is_open()){//test to see if the file is opened
        if(debug){cout << "Couldn't open " << traceFile << " for reading!\n";}
        exit(1);
    }
    //fp = fopen(traceFile, "r");
    int lim = 0; 
    string test;
    while(infile >> addr >> rw && lim < 20){
        //infile >> addr;
        //infile >> rw;
        cout << addr << endl;
        //cout << hex << addr << dec <<  " " << rw << endl;
        //cout << hex << getVPN(addr) << dec << endl;
        lim++; //limit test.
    }*/ 


}

int getVPN(unsigned addr){
    int ret = addr/PAGESIZE;
    return ret;
}

void printResults(const int& nFrames, const int& eventsNum, const int& totalR, const int& totalW){
    cout << "Total memory frames: " << nFrames << endl;
    cout << "Events in trace: " << eventsNum << endl;
    cout << "total disk reads: " << totalR << endl;
    cout << "total disk writes: " << totalW << endl;
}

void fifo(){

}
void lru(){

}
void segmentedFifo(){

}