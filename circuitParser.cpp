//
//  circuitParser.cpp
//  STA
//
//  Created by lin shih-feng on 2013/12/20.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "circuitParser.h"

CIRCUIT::~CIRCUIT() {
    std::map<std::string, GATE*>::iterator iter;
    for (iter=CircuitMap.begin(); iter!=CircuitMap.end(); iter++) {
        delete iter->second;
    }
}

int CIRCUIT::InitialCircuit(std::string filename) {
    
    if (fopen(filename.c_str(), "r")==NULL) {
        std::cout<<filename<<" doesn't exist"<<std::endl;
        return 0;
    }
    infile.open(filename.c_str());
    Parser();
    return 1;
}

void CIRCUIT::Parser() {
    
}