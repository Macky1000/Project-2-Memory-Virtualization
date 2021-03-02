#include "VMSim.h"

VM
void printResults(){
    cout << "Total memory frames: " << nFrames<< endl;
    cout << "Events in trace: " << eventsNum << endl;
    cout << "total disk reads: " << totalR << endl;
    cout << "total disk writes: " << totalW << endl;
}