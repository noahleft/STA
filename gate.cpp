//
//  gate.cpp
//  StaticTimingAnalysis
//
//  Created by lin shih-feng on 2013/12/21.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "gate.h"


std::string GATE::GetFunc(){
    switch (Func) {
        case CircuitLibrary::G_AND:
            if (IsInv) {return "NAND";}
            else return "AND";
            break;
        case CircuitLibrary::G_OR:
            if (IsInv) {return "NOR";}
            else return "OR";
            break;
        case CircuitLibrary::G_BUF:
            if (IsInv) {return "NOT";}
            else return "BUFF";
            break;
        case CircuitLibrary::G_XOR:
            if (IsInv) {return "XNOR";}
            else return "XOR";
            break;
        case CircuitLibrary::G_PI:
            return "INPUT";
            break;
        case CircuitLibrary::G_PO:
            return "OUTPUT";
            break;
        default:
            return "";
            break;
    }
}



void GATE::CalculateArrivalTime() {
    riseArrivalTime=0;
    fallArrivalTime=0;
    
    if (Func==CircuitLibrary::G_XOR) {
        //all logic fanin will possibly trigger
        for (unsigned i=0; i<Fanin.size(); i++) {
            GATE* tmp=Fanin[i];
            
            if (riseArrivalTime < (tmp->riseArrivalTime + riseGateDelay)) {
                riseArrivalTime = (tmp->riseArrivalTime + riseGateDelay);
                riseArrivalFrom = tmp;
            }
            if (fallArrivalTime < (tmp->fallArrivalTime + fallGateDelay)) {
                fallArrivalTime = (tmp->fallArrivalTime + fallGateDelay);
                fallArrivalFrom = tmp;
            }
            if (riseArrivalTime < (tmp->fallArrivalTime + riseGateDelay)) {
                riseArrivalTime = (tmp->fallArrivalTime + riseGateDelay);
                riseArrivalFrom = tmp;
            }
            if (fallArrivalTime < (tmp->riseArrivalTime + fallGateDelay)) {
                fallArrivalTime = (tmp->riseArrivalTime + fallGateDelay);
                fallArrivalFrom = tmp;
            }
        }
    }
    else if (!IsInv) {
        //positive-logic need same input logic
        //Rise-signal come will generate rising signal
        for (unsigned i=0; i<Fanin.size(); i++) {
            GATE* tmp=Fanin[i];
            
            if (riseArrivalTime < (tmp->riseArrivalTime + riseGateDelay)) {
                riseArrivalTime = (tmp->riseArrivalTime + riseGateDelay);
                riseArrivalFrom = tmp;
            }
            if (fallArrivalTime < (tmp->fallArrivalTime + fallGateDelay)) {
                fallArrivalTime = (tmp->fallArrivalTime + fallGateDelay);
                fallArrivalFrom = tmp;
            }
        }
    }
    else {
        //negative-logic need inverse input logic
        //Rise-signal come will generate falling signal
        for (unsigned i=0; i<Fanin.size(); i++) {
            GATE* tmp=Fanin[i];
            
            if (riseArrivalTime < (tmp->fallArrivalTime + riseGateDelay)) {
                riseArrivalTime = (tmp->fallArrivalTime + riseGateDelay);
                riseArrivalFrom = tmp;
            }
            if (fallArrivalTime < (tmp->riseArrivalTime + fallGateDelay)) {
                fallArrivalTime = (tmp->riseArrivalTime + fallGateDelay);
                fallArrivalFrom = tmp;
            }
        }
    }
    
    if (riseArrivalTime>fallArrivalTime) {
        arrivalTime=riseArrivalTime;
    }
    else {
        arrivalTime=fallArrivalTime;
    }
    
}

void TracebackLongestPath(std::vector<std::string>& pathList,std::string path,GATE* ptr,bool IsRiseSignal) {
    path=ptr->GetName()+" "+path;
    if (ptr->No_Fanin()==0) {
        //reach PI
        pathList.push_back(path);
        return;
    }
    if (ptr->GetGateFunc()==CircuitLibrary::G_XOR) {
        GATE* gate_ptr;
        if (IsRiseSignal) {
            gate_ptr=ptr->GetRiseArrivalFrom();
        }
        else gate_ptr=ptr->GetFallArrivalFrom();
        if (gate_ptr->GetRiseArrivalTime() > gate_ptr->GetFallArrivalTime()) {
            IsRiseSignal=true;
        }
        else IsRiseSignal=false;
    }
    else if (ptr->IsInversion()) {
        IsRiseSignal=!IsRiseSignal;
    }
    
    if (IsRiseSignal) {
        path="R "+path;
        ptr=ptr->GetRiseArrivalFrom();
    }
    else {
        path="F "+path;
        ptr=ptr->GetFallArrivalFrom();
    }
    TracebackLongestPath(pathList, path, ptr, IsRiseSignal);
}

std::vector<std::string> GATE::GetLongestPath() {
    
    std::string path;
    bool IsRiseSignal;
    GATE* ptr=this;
    // decide trace back from which output
    if (riseArrivalTime > fallArrivalTime) {
        IsRiseSignal=true;
        path="R";
        ptr=ptr->riseArrivalFrom;
    }
    else {
        IsRiseSignal=false;
        path="F";
        ptr=ptr->fallArrivalFrom;
    }
    //trace back
    std::vector<std::string> pathList;
    TracebackLongestPath(pathList, path, ptr, IsRiseSignal);
    return pathList;
}

void GATE::CalculateRequireTime(double t) {
    requireTime=t;
}
