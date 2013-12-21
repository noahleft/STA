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
    CircuitLibrary::GATE* ptr;
    GATE* gate;
    std::map<std::string, GATE*> NameToGATE;
    for (unsigned i=0; i<design.No_Gate(); i++) {
        ptr=design.Gate(i);
        //check whether alloc it before
        if (NameToGATE.find(ptr->name)!=NameToGATE.end()) {
            gate=NameToGATE[ptr->name];
        }
        else {
            gate=new GATE(ptr->name);
            NameToGATE[ptr->name]=gate;
        }
        
        
        netlist.push_back(gate);
        if (ptr->Func==CircuitLibrary::G_PI) {
            PIlist.push_back(gate);
        }
        else if (ptr->Func==CircuitLibrary::G_PO) {
            POlist.push_back(gate);
        }
        
        //link fanin
        for (unsigned i=0; i<ptr->FaninList.size(); i++) {
            if (NameToGATE.find(ptr->FaninList[i]->name)!=NameToGATE.end()) {
                gate->AddFanin(NameToGATE[ptr->FaninList[i]->name]);
            }
            else {
                GATE* tmp=new GATE(ptr->FaninList[i]->name);
                NameToGATE[ptr->FaninList[i]->name]=tmp;
                gate->AddFanin(tmp);
            }
        }
    }
}