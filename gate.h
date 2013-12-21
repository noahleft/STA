//
//  gate.h
//  StaticTimingAnalysis
//
//  Created by lin shih-feng on 2013/12/21.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef __StaticTimingAnalysis__gate__
#define __StaticTimingAnalysis__gate__

#include <iostream>
#include <string>
#include <vector>

class GATE {
private:
    
    std::string name;
    std::vector<GATE*> Fanin;
    std::vector<GATE*> Fanout;
    
    double arrivalTime;
    double requireTime;
    double riseDelay;
    double fallDelay;
    
public:
    GATE(std::string n):name(n),arrivalTime(0),requireTime(0),riseDelay(0),fallDelay(0){}
    
    void AddFanin(GATE* ptr){Fanin.push_back(ptr);ptr->Fanout.push_back(this);}
    GATE* GetFanin(unsigned idx){return Fanin[idx];}
    
    std::string GetName(){return name;}
};

#endif /* defined(__StaticTimingAnalysis__gate__) */
