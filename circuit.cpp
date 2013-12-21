//
//  circuit.cpp
//  StaticTimingAnalysis
//
//  Created by lin shih-feng on 2013/12/21.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "circuit.h"

CIRCUIT::~CIRCUIT() {
    for (unsigned i=0; i<netlist.size(); i++) {
        delete netlist[i];
    }
}

void CIRCUIT::LoadDesign(CircuitLibrary &design) {
    
}