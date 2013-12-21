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
        
        gate->SetFunc(ptr->Func);
        gate->SetInv(ptr->IsInv);
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

void CIRCUIT::CalculateGateDelay(DelayLibrary &delayLibrary) {
    for (unsigned i=0; i<No_Gate(); i++) {
        GATE* gate=netlist[i];
        
        if (gate->GetGateFunc()==CircuitLibrary::G_PI || gate->GetGateFunc()==CircuitLibrary::G_PO) {
            gate->SetRiseDelay(0);
            gate->SetFallDelay(0);
            continue;
        }
        
        std::string gateFunc=gate->GetFunc();
        unsigned FanoutNum=gate->No_Fanout();
        double UnitFanoutDelay=delayLibrary.GetFanoutDelay(gateFunc);
        double RiseDelay=delayLibrary.GetRiseDelay(gateFunc);
        double FallDelay=delayLibrary.GetFallDelay(gateFunc);
        gate->SetRiseDelay(RiseDelay+UnitFanoutDelay*FanoutNum);
        gate->SetFallDelay(FallDelay+UnitFanoutDelay*FanoutNum);
    }
}

void CIRCUIT::Levelization() {
    for (unsigned i=0; i<No_Gate(); i++) {
        netlist[i]->ResetToken();
        netlist[i]->SetLevel(0);
        netlist[i]->ResetScheduled();
    }
    
    for (unsigned i=0; i<No_PI(); i++) {
        PIlist[i]->SetLevel(0);
        for (unsigned j=0; j<PIlist[i]->No_Fanout(); j++) {
            PIlist[i]->GetFanout(j)->IncToken();
            if (!PIlist[i]->GetFanout(j)->IsScheduled()) {
                queue.push(PIlist[i]->GetFanout(j));
                PIlist[i]->GetFanout(j)->SetScheduled();
            }
        }
    }
    
    while (!queue.empty()) {
        GATE* gate=queue.front();
        queue.pop();
        
        if (gate->GetToken()!=gate->No_Fanin()) {
            queue.push(gate);
            continue;
        }
        
        unsigned tmp_level=0;
        for (unsigned i=0; i<gate->No_Fanin(); i++) {
            if (tmp_level<gate->GetFanin(i)->GetLevel()) {
                tmp_level=gate->GetFanin(i)->GetLevel();
            }
        }
        
        gate->SetLevel(tmp_level+1);
        for (unsigned i=0; i<gate->No_Fanout(); i++) {
            gate->GetFanout(i)->IncToken();
            if (!gate->GetFanout(i)->IsScheduled()) {
                queue.push(gate->GetFanout(i));
                gate->GetFanout(i)->SetScheduled();
            }
        }
    }
    
    for (unsigned i=0; i<netlist.size(); i++) {
        if (MaxLevel<netlist[i]->GetLevel()) {
            MaxLevel=netlist[i]->GetLevel();
        }
    }
    MaxLevel++;
}

