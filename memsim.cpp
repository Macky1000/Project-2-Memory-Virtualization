#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]){
    if (argc != 5){
        string arguments = (argc < 5) ? "few" : "many";
        cout << "too" << arguments << "arguments given. Please use the following format:\nmemsim <tracefile> <nframes> <lru|fifo|vms> <debug|quiet>" << endl;
        exit(1);
    }
    
    //argv;
}