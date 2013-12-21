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
    
public:
    
};

#endif /* defined(__StaticTimingAnalysis__gate__) */
