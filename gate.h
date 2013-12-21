//
//  gate.h
//  StaticTimingAnalysis
//
//  Created by lin shih-feng on 2013/12/21.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef __StaticTimingAnalysis__gate__
#define __StaticTimingAnalysis__gate__
#include "circuitParser.h"
#include <iostream>
#include <string>
#include <vector>

class GATE {
private:
    
    std::string name;
    std::vector<GATE*> Fanin;
    std::vector<GATE*> Fanout;
    CircuitLibrary::GATEFUNC Func;
    bool IsInv;
    unsigned level;
    unsigned token;
    bool scheduled;
    
    double arrivalTime;
    double requireTime;
    double riseDelay;
    double fallDelay;
    
public:
    GATE(std::string n):name(n),level(0),token(0),scheduled(false),arrivalTime(0),requireTime(0),riseDelay(0),fallDelay(0){}
    
    void AddFanin(GATE* ptr){Fanin.push_back(ptr);ptr->Fanout.push_back(this);}
    GATE* GetFanin(unsigned idx){return Fanin[idx];}
    GATE* GetFanout(unsigned idx){return Fanout[idx];}
    void SetFunc(CircuitLibrary::GATEFUNC func){Func=func;}
    void SetInv(bool inv){IsInv=inv;}
    void SetRiseDelay(double d){riseDelay=d;}
    void SetFallDelay(double d){fallDelay=d;}
    void SetLevel(unsigned l){level=l;}
    void IncToken(){token++;}
    void ResetToken(){token=0;}
    bool IsScheduled(){return scheduled;}
    void SetScheduled(){scheduled=true;}
    void ResetScheduled(){scheduled=false;}
    
    std::string GetName(){return name;}
    CircuitLibrary::GATEFUNC GetGateFunc(){return Func;}
    unsigned No_Fanin(){return (unsigned)Fanin.size();}
    unsigned No_Fanout(){return (unsigned)Fanout.size();}
    unsigned GetLevel(){return level;}
    unsigned GetToken(){return token;}
    std::string GetFunc(){
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
};

#endif /* defined(__StaticTimingAnalysis__gate__) */
