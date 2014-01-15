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
                riseArrivalFrom.clear();
                riseArrivalFrom.push_back(tmp);
            }
            else if (riseArrivalTime == (tmp->riseArrivalTime + riseGateDelay)) {
                riseArrivalFrom.push_back(tmp);
            }
            
            if (fallArrivalTime < (tmp->fallArrivalTime + fallGateDelay)) {
                fallArrivalTime = (tmp->fallArrivalTime + fallGateDelay);
                fallArrivalFrom.clear();
                fallArrivalFrom.push_back(tmp);
            }
            else if (fallArrivalTime == (tmp->fallArrivalTime + fallGateDelay)) {
                fallArrivalFrom.push_back(tmp);
            }
            
            if (riseArrivalTime < (tmp->fallArrivalTime + riseGateDelay)) {
                riseArrivalTime = (tmp->fallArrivalTime + riseGateDelay);
                riseArrivalFrom.clear();
                riseArrivalFrom.push_back(tmp);
            }
            else if (riseArrivalTime == (tmp->fallArrivalTime + riseGateDelay)) {
                riseArrivalFrom.push_back(tmp);
            }
            
            if (fallArrivalTime < (tmp->riseArrivalTime + fallGateDelay)) {
                fallArrivalTime = (tmp->riseArrivalTime + fallGateDelay);
                fallArrivalFrom.clear();
                fallArrivalFrom.push_back(tmp);
            }
            else if (fallArrivalTime == (tmp->riseArrivalTime + fallGateDelay)) {
                fallArrivalFrom.push_back(tmp);
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
                riseArrivalFrom.clear();
                riseArrivalFrom.push_back(tmp);
            }
            else if (riseArrivalTime == (tmp->riseArrivalTime + riseGateDelay)) {
                riseArrivalFrom.push_back(tmp);
            }
            
            if (fallArrivalTime < (tmp->fallArrivalTime + fallGateDelay)) {
                fallArrivalTime = (tmp->fallArrivalTime + fallGateDelay);
                fallArrivalFrom.clear();
                fallArrivalFrom.push_back(tmp);
            }
            else if (fallArrivalTime == (tmp->fallArrivalTime + fallGateDelay)) {
                fallArrivalFrom.push_back(tmp);
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
                riseArrivalFrom.clear();
                riseArrivalFrom.push_back(tmp);
            }
            else if (riseArrivalTime == (tmp->fallArrivalTime + riseGateDelay)) {
                riseArrivalFrom.push_back(tmp);
            }
            
            if (fallArrivalTime < (tmp->riseArrivalTime + fallGateDelay)) {
                fallArrivalTime = (tmp->riseArrivalTime + fallGateDelay);
                fallArrivalFrom.clear();
                fallArrivalFrom.push_back(tmp);
            }
            else if (fallArrivalTime == (tmp->riseArrivalTime + fallGateDelay)) {
                fallArrivalFrom.push_back(tmp);
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
    if (pathList.size()>5) {
        return;
    }
    if (ptr->No_Fanin()==0) {
        //reach PI
        pathList.push_back(path);
        return;
    }
    if (ptr->GetGateFunc()==CircuitLibrary::G_XOR) {
        
        std::vector<GATE*> gateList;
        std::string R_path,F_path;
        R_path="R "+path;
        F_path="F "+path;
        if (IsRiseSignal) {
            gateList=ptr->GetRiseArrivalFrom();
        }
        else {
            gateList=ptr->GetFallArrivalFrom();
        }
        for (unsigned i=0; i<gateList.size(); i++) {
            ptr=gateList[i];
            if (ptr->GetRiseArrivalTime() > ptr->GetFallArrivalTime()) {
                TracebackLongestPath(pathList, R_path, ptr, true);
            }
            else if (ptr->GetRiseArrivalTime() == ptr->GetFallArrivalTime()) {
                TracebackLongestPath(pathList, R_path, ptr, true);
                TracebackLongestPath(pathList, F_path, ptr, false);
            }
            else {
                TracebackLongestPath(pathList, F_path, ptr, false);
            }
        }
    }
    else {
        std::vector<GATE*> gateList;
        if (IsRiseSignal) {
            gateList=ptr->GetRiseArrivalFrom();
        }
        else {
            gateList=ptr->GetFallArrivalFrom();
        }
        
        if (ptr->IsInversion()) {
            IsRiseSignal=!IsRiseSignal;
        }
        
        if (IsRiseSignal) {
            path="R "+path;
        }
        else {
            path="F "+path;
        }
        for (unsigned i=0; i<gateList.size(); i++) {
            ptr=gateList[i];
            TracebackLongestPath(pathList, path, ptr, IsRiseSignal);
        }
    }
}

std::vector<std::string> GATE::GetLongestPath() {
    
    std::string path;
    bool IsRiseSignal;
    GATE* ptr=this;
    // decide trace back from which output
    if (riseArrivalTime > fallArrivalTime) {
        IsRiseSignal=true;
        path="R";
        std::vector<GATE*> gateList=ptr->GetRiseArrivalFrom();
        ptr=gateList[0];
    }
    else {
        IsRiseSignal=false;
        path="F";
        std::vector<GATE*> gateList=ptr->GetFallArrivalFrom();
        ptr=gateList[0];
    }
    //trace back
    std::vector<std::string> pathList;
    TracebackLongestPath(pathList, path, ptr, IsRiseSignal);
    return pathList;
}

void GATE::CalculateRequireTime(double t) {
    requireTime=t;
}
