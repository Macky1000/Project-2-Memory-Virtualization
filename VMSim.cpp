#include "VMSim.h"

void printResults(){
    cout << "Total memory frames: " << nFrames;
    cout << "Events in trace: " << eventsNum;
    cout << "total disk reads: " << totalR;
    cout << "total disk writes: " << totalW;
}