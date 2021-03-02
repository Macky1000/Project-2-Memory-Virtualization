#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <map>
using namespace std;

//#include "VMSim.h"

const int PAGESIZE = 4096; //4 KB (4096 bytes)

class Page{
public:
    unsigned int pgNum; //maybe not needed
    //int validBit;
    int previousAccess;
    bool dirtyFlag;
    Page(unsigned int a);
};

Page::Page(unsigned int a){
    this->pgNum = a;
    //this->validBit = 0;
    this->previousAccess = 0;
    this->dirtyFlag = false;
}

void printResults(const int& nFrames, const int& eventsNum);//, const int& totalR, const int& totalW);

int getVPN(unsigned addr);

void lru();
void fifo();
void segmentedFifo();

int totalW;
int totalR;

int main(int argc, char *argv[]){
    //declare our variables we wanna track ()
    totalW = 0;
    totalR = 0;
    int eventsNum = 0;
    

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
    
    vector<Page*> pageTable;
    map<unsigned int, int> addressLookup;

    FILE* fp;
    unsigned addr;
    char rw;
    fp = fopen(argv[1], "r");
    
    i = 0;
    int lim = 0; //test for only 20 entries
    while (fscanf(fp,"%x %c", &addr, &rw) != EOF && lim < 20){
        eventsNum++; //I think this is an event idk tho
        //(rw == 'R') ? totalR++ : totalW++; //record those totals for the final print
        unsigned int VPN = getVPN(addr); //get the virtual address number from the address then use that for page number.
        if(debug){
            cout << hex << addr << dec <<  " " << rw << endl;
            cout << hex << VPN << dec << endl;
            cout << "VPN in decimal: " << VPN << endl;
        }
        
        if(addressLookup.count(VPN) != 1){//test to see if we have a page already added to the lookup (and thus, has been loaded in before)
            if(pageTable.size() == nFrames){//see if the page table is already full
                if(debug) {cout << "page full (this is where the algorithms come in)" << endl;}//test
                
                switch (algorithm){
                case 0: //LRU 
                    lru();
                    break;
                case 1: //FIFO
                    fifo();
                    break;
                case 2:
                    segmentedFifo();
                    break;
                default:
                    if(debug) {cout << "something very wrong happened with the chosen algorithm" << endl;}//test
                    break;
                }

            }else{//if the page table is not full yet, create a new page for it.
                if(debug) {cout << "new page num: " << i << endl;}
                Page* currPage = new Page(VPN); //make a new page since the page table is empty
                pageTable.push_back(currPage); //add new page to page table

                if(debug) {
                    cout << "PageTable element: " << i << "\nElement's page num: " << pageTable[i]->pgNum << endl;
                    cout << /*"Page's validBit: " << pageTable[i]->validBit <<*/ "Page previousAccess: " << pageTable[i]->previousAccess << endl;
                    cout << "Page dirtyFlag: " << pageTable[i]->dirtyFlag << endl;

                    cout << "------------------------------"<< endl;
                }
                
                addressLookup.emplace(VPN,i);
                i++; //just keep track of the element we're putting in
            }
        }else{//look up in the page table where it is
            if(pageTable[addressLookup[VPN]]->pgNum == VPN){//looks pretty complex but it isnt. Basically, take the VPN, go to the map to find what element it would be in the pageTable, go to given element in the page table and ask the page there what it's page number is. If the numbers match, we got a hit. 
                if(debug) {cout << "Hit!\n------------------------------" << endl;}
            }else{
                if(debug) {cout << "Miss!\n------------------------------" << endl;}

                /*if(pageTable[addressLookup[VPN]]->dirtyFlag == true){//if the page we're about to replace is dirty, then increment the total write counter.
                    totalW++;
                }*/
                switch (algorithm){
                case 0: //LRU 
                    lru();
                    break;
                case 1: //FIFO
                    fifo();
                    break;
                case 2:
                    segmentedFifo();
                    break;
                default:
                    if(debug) {cout << "something very wrong happened with the chosen algorithm" << endl;}//test
                    break;
                }
            }
        }
        
        if(rw == 'W'){
            pageTable[addressLookup[VPN]]->dirtyFlag = true;
        }
        
        //if(lim % 10000 == 0){cout << lim << endl;}
        lim++;
    }

    if(debug) {cout << "\n------------------------------\n<Heres the results>" << endl;}//test

    //totalW = 111;
    //totalR = 222;
    printResults(nFrames, eventsNum);//, totalR, totalW); //print 'em
    return(0);
}

int getVPN(unsigned int addr){
    int ret = addr/PAGESIZE;
    return ret;
}

void printResults(const int& nFrames, const int& eventsNum){//, const int& totalR, const int& totalW){
    cout << "Total memory frames: " << nFrames << endl;
    cout << "Events in trace: " << eventsNum << endl;
    cout << "total disk reads: " << totalR << endl;
    cout << "total disk writes: " << totalW << endl;
}

void lru(){
    return;
}
void fifo(){
    return;
}
void segmentedFifo(){
    return;
}