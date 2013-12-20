//
//  main.cpp
//  STA
//
//  Created by lin shih-feng on 2013/12/20.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include <iostream>
#include "libraryParser.h"
#include "circuitParser.h"
using namespace std;

DelayLibrary library;
CIRCUIT circuit;

int main(int argc, const char * argv[])
{
    string DelayLibrary="nctu_18.tech";
    
    int Status_DelayLibrary=library.InitialLibrary(DelayLibrary);
    if (Status_DelayLibrary==0) {
        cout<<"You shall check library file name or path please."<<endl;
        return -1;
    }
    
    string CircuitFile="c17.bench";
    
    int Status_Circuit=circuit.InitialCircuit(CircuitFile);
    if (Status_Circuit==0) {
        cout<<"You shall check circuit file name or path please."<<endl;
        return -1;
    }
    
    return 0;
}

