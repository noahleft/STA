//
//  circuitParser.h
//  STA
//
//  Created by lin shih-feng on 2013/12/20.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef __STA__circuitParser__
#define __STA__circuitParser__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>
#include <fstream>

class CIRCUIT {
private:
    enum GATEFUNC{G_PI,G_PO,G_AND,G_OR,G_BUF};
    struct GATE{
        std::string name;
        bool IsInv;
        GATEFUNC Func;
        std::vector<GATE*> FaninList;
        std::vector<GATE*> FanoutList;
    };
    
    std::ifstream infile;
    std::map<std::string,GATE*> CircuitMap;
    
    void Parser();
    void AllocGate(std::string Name,std::string Func,std::string Fanin);
    
public:
    CIRCUIT(){}
    ~CIRCUIT();
    int InitialCircuit(std::string filename);
};


#endif /* defined(__STA__circuitParser__) */
