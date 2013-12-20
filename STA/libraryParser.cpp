//
//  libraryParser.cpp
//  STA
//
//  Created by lin shih-feng on 2013/12/20.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "libraryParser.h"

DelayLibrary::~DelayLibrary() {
    std::map<std::string, GATE*>::iterator iter;
    for (iter=LookupTable.begin(); iter!=LookupTable.end(); iter++) {
        delete iter->second;
    }
}

int DelayLibrary::InitialLibrary(std::string filename) {
    pFile = fopen(filename.c_str(), "r");
    if (pFile==NULL) {
        std::cout<<filename<<" doesn't exist."<<std::endl;
        return 0;
    }
    Parser();
    return 1;
}

void DelayLibrary::AllocGate(std::string name, double r, double f, double fanout) {
    GATE* gate=new GATE();
    gate->name=name;
    gate->delay_rise=r;
    gate->delay_fall=f;
    gate->delay_fanout=fanout;
    LookupTable[name]=gate;
}

void DelayLibrary::Parser() {
    
}