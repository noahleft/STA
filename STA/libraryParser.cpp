//
//  libraryParser.cpp
//  STA
//
//  Created by lin shih-feng on 2013/12/20.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "libraryParser.h"

DelayLibrary::~DelayLibrary() {
    std::map<std::string, GATE*>::iterator iter;
    for (iter=LookupTable.begin(); iter!=LookupTable.end(); iter++) {
        delete iter->second;
    }
}

int DelayLibrary::InitialLibrary(std::string filename) {
    
    if (fopen(filename.c_str(), "r")==NULL) {
        std::cout<<filename<<" doesn't exist."<<std::endl;
        return 0;
    }
    infile.open(filename.c_str());
    Parser();
    return 1;
}

void DelayLibrary::AllocGate(std::string name, double r, double f, double fanout) {
    GATE* gate=new GATE();
    gate->name=name;
    gate->delay_rise=r;
    gate->delay_fall=f;
    gate->delay_fanout=fanout;
    LookupTable[name]=gate;
}

void ExtractData(std::string &str) {
    bool isAlpha=false;
    for (int i=0; i<str.size(); i++) {
        if (str[i]==' ') {str[i]='\t';}
        if (str[i]=='\t') {
            if (isAlpha) {
                isAlpha=false;
            }
            else str.erase(i);
        }
        else {
            isAlpha=true;
        }
    }
}

void DelayLibrary::Parser() {
    std::string str;
    while (!infile.eof()) {
        getline(infile,str);
        if (str.length()==0) {continue;}
        ExtractData(str);
        
        std::string::size_type idx=str.find('\t');
        
        std::string Name=str.substr(0,idx);
        str=str.substr(idx+1);
        idx=str.find('\t');
        double delay_rise=atof(str.substr(0,idx).c_str());
        str=str.substr(idx+1);
        idx=str.find('\t');
        double delay_fall=atof(str.substr(0,idx).c_str());
        str=str.substr(idx+1);
        double delay_fanout=atof(str.c_str());
        
        AllocGate(Name, delay_rise, delay_fall, delay_fanout);
    }
    
}