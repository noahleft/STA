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
#include "circuit.h"
using namespace std;

DelayLibrary library;
CircuitLibrary designLibrary;
CIRCUIT circuit;
void Fileout();

int main(int argc, const char * argv[])
{
    string DelayLibrary="nctu_18.tech";
    
    int Status_DelayLibrary=library.InitialLibrary(DelayLibrary);
    if (Status_DelayLibrary==0) {
        cout<<"You shall check library file name or path please."<<endl;
        return -1;
    }
    
    string CircuitFile="c17.bench";
    
    int Status_Circuit=designLibrary.InitialCircuit(CircuitFile);
    if (Status_Circuit==0) {
        cout<<"You shall check circuit file name or path please."<<endl;
        return -1;
    }
    
    circuit.LoadDesign(designLibrary);
    circuit.CalculateGateDelay(library);
    circuit.Levelization();
    circuit.CalculateArrivalTime();
    
    
    Fileout();
    return 0;
}

void Fileout() {
    cout<<circuit.No_PI()<<" "<<circuit.No_PO()<<" "<<circuit.No_Gate()-circuit.No_PI()-circuit.No_PO()<<endl;
    
    for (unsigned i=0; i<circuit.No_PO(); i++) {
        GATE* gate=circuit.PO_Gate(i);
        cout<<gate->GetFanin(0)->GetName()<<" "<<gate->GetArrivalTime();
        cout<<endl;
    }
}