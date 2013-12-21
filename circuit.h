//
//  circuit.h
//  StaticTimingAnalysis
//
//  Created by lin shih-feng on 2013/12/21.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef __StaticTimingAnalysis__circuit__
#define __StaticTimingAnalysis__circuit__
#include "gate.h"
#include "circuitParser.h"
#include "libraryParser.h"
#include <iostream>
#include <queue>

class CIRCUIT {
private:
    
    std::vector<GATE*> PIlist;
    std::vector<GATE*> POlist;
    std::vector<GATE*> netlist;
    std::queue<GATE*> queue;
    unsigned MaxLevel;
    
public:
    
    CIRCUIT(){}
    ~CIRCUIT();
    
    void LoadDesign(CircuitLibrary &);
    void CalculateGateDelay(DelayLibrary &);
    void Levelization();
    
    unsigned No_PI(){return (unsigned)PIlist.size();}
    unsigned No_PO(){return (unsigned)POlist.size();}
    unsigned No_Gate(){return (unsigned)netlist.size();}
    
    GATE* PO_Gate(unsigned idx){return POlist[idx];}
};

#endif /* defined(__StaticTimingAnalysis__circuit__) */
