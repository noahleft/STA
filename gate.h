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
    double riseGateDelay;
    double fallGateDelay;
    double riseArrivalTime;
    GATE* riseArrivalFrom;
    double fallArrivalTime;
    GATE* fallArrivalFrom;
    
public:
    GATE(std::string n):name(n),level(0),token(0),scheduled(false),arrivalTime(0),requireTime(0),riseGateDelay(0),fallGateDelay(0),riseArrivalTime(0),riseArrivalFrom(NULL),fallArrivalTime(0),fallArrivalFrom(NULL){}
    
    void AddFanin(GATE* ptr){Fanin.push_back(ptr);ptr->Fanout.push_back(this);}
    GATE* GetFanin(unsigned idx){return Fanin[idx];}
    GATE* GetFanout(unsigned idx){return Fanout[idx];}
    void SetFunc(CircuitLibrary::GATEFUNC func){Func=func;}
    void SetInv(bool inv){IsInv=inv;}
    void SetRiseGateDelay(double d){riseGateDelay=d;}
    void SetFallGateDelay(double d){fallGateDelay=d;}
    void SetLevel(unsigned l){level=l;}
    void IncToken(){token++;}
    void ResetToken(){token=0;}
    bool IsScheduled(){return scheduled;}
    void SetScheduled(){scheduled=true;}
    void ResetScheduled(){scheduled=false;}
    void SetRiseArrivalTime(double d){riseArrivalTime=d;}
    void SetFallArrivalTime(double d){fallArrivalTime=d;}
    void CalculateArrivalTime();
    void CalculateRequireTime(double t);
    
    std::string GetName(){return name;}
    CircuitLibrary::GATEFUNC GetGateFunc(){return Func;}
    unsigned No_Fanin(){return (unsigned)Fanin.size();}
    unsigned No_Fanout(){return (unsigned)Fanout.size();}
    unsigned GetLevel(){return level;}
    unsigned GetToken(){return token;}
    double GetRiseArrivalTime(){return riseArrivalTime;}
    double GetFallArrivalTime(){return fallArrivalTime;}
    double GetArrivalTime(){return riseArrivalTime>fallArrivalTime?riseArrivalTime:fallArrivalTime;}
    double GetRequireTime(){return requireTime;}
    double GetSlack(){return requireTime-arrivalTime;}
    std::string GetFunc();
    std::string GetLongestPath();
};

#endif /* defined(__StaticTimingAnalysis__gate__) */
