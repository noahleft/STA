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
#include <iostream>

class CIRCUIT {
private:
    
    std::vector<GATE*> PIlist;
    std::vector<GATE*> POlist;
    std::vector<GATE*> netlist;
    
public:
    
    CIRCUIT(){}
    ~CIRCUIT();
    
    void LoadDesign(CircuitLibrary &);
    
};

#endif /* defined(__StaticTimingAnalysis__circuit__) */
