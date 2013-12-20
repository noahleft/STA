//
//  libraryParser.h
//  STA
//
//  Created by lin shih-feng on 2013/12/20.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#ifndef __STA__libraryParser__
#define __STA__libraryParser__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>

class DelayLibrary {
private:
    struct GATE {
        std::string name;
        double delay_rise;
        double delay_fall;
        double delay_fanout;
        
    };
    
    std::ifstream infile;
    std::map<std::string,GATE*> LookupTable;
    
    void Parser();
    void AllocGate(std::string Name,double delay_r,double delay_f,double delay_fanout);
    
public:
    DelayLibrary(){}
    ~DelayLibrary();
    int InitialLibrary(std::string filename);
};

#endif /* defined(__STA__libraryParser__) */
