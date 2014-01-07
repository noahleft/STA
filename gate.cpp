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
    
    if (!IsInv) {
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

std::string GATE::GetLongestPath() {
    
    std::string path;
    bool IsRiseSignal;
    GATE* ptr=this;
    
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
    
    while (ptr->No_Fanin()!=0) {
        
        if (IsRiseSignal) {
            path=ptr->GetName()+" "+path;
            if (ptr->IsInv) {
                IsRiseSignal=!IsRiseSignal;
            }
            if (IsRiseSignal) {
                path="R "+path;
            }
            else {
                path="F "+path;
            }
            ptr=ptr->riseArrivalFrom;
        }
        else {
            path=ptr->GetName()+" "+path;
            if (ptr->IsInv) {
                IsRiseSignal=!IsRiseSignal;
            }
            if (IsRiseSignal) {
                path="R "+path;
            }
            else {
                path="F "+path;
            }
            ptr=ptr->fallArrivalFrom;
        }
        
        
    }
    path=ptr->GetName()+" "+path;
    return path;
}

void GATE::CalculateRequireTime(double t) {
    requireTime=t;
}
