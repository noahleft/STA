//
//  circuitParser.cpp
//  STA
//
//  Created by lin shih-feng on 2013/12/20.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include "circuitParser.h"

CIRCUIT::~CIRCUIT() {
    std::map<std::string, GATE*>::iterator iter;
    for (iter=CircuitMap.begin(); iter!=CircuitMap.end(); iter++) {
        delete iter->second;
    }
}

int CIRCUIT::InitialCircuit(std::string filename) {
    
    if (fopen(filename.c_str(), "r")==NULL) {
        std::cout<<filename<<" doesn't exist"<<std::endl;
        return 0;
    }
    infile.open(filename.c_str());
    Parser();
    return 1;
}

void CIRCUIT::AllocGate(std::string Name, std::string Func, std::string Fanin) {
    GATE* gate;
    if (CircuitMap.find(Name)!=CircuitMap.end()) {
        gate=CircuitMap[Name];
    }
    else {
        gate=new GATE;
        CircuitMap[Name]=gate;
        gate->name=Name;
    }
    
    netlist.push_back(gate);
    
    //decode func
    {
        if (Func.compare("AND")==0) {gate->Func=G_AND; gate->IsInv=false;}
        else if (Func.compare("NAND")==0) {gate->Func=G_AND; gate->IsInv=true;}
        else if (Func.compare("OR")==0) {gate->Func=G_OR; gate->IsInv=false;}
        else if (Func.compare("NOR")==0) {gate->Func=G_OR; gate->IsInv=true;}
        else if (Func.compare("BUF")==0) {gate->Func=G_BUF; gate->IsInv=false;}
        else if (Func.compare("INV")==0) {gate->Func=G_BUF; gate->IsInv=true;}
        else if (Func.compare("NOT")==0) {gate->Func=G_BUF; gate->IsInv=true;}
        else if (Func.compare("XOR")==0) {gate->Func=G_XOR; gate->IsInv=false;}
        else if (Func.compare("XNOR")==0) {gate->Func=G_XOR; gate->IsInv=true;}
        else if (Func.compare("PI")==0) {gate->Func=G_PI; gate->IsInv=false;}
        else if (Func.compare("PO")==0) {gate->Func=G_PO; gate->IsInv=false;}
        
    }
    
    //decode fanin
    {
        Fanin+=',';
        std::string::size_type idx;
        while (Fanin.length()!=0) {
            if (Fanin[0]==',') {break;}
            std::string gateName;
            idx=Fanin.find(',');
            gateName=Fanin.substr(0,idx);
            Fanin=Fanin.substr(idx+1);
            
            if (CircuitMap.find(gateName)!=CircuitMap.end()) {
                gate->FaninList.push_back(CircuitMap[gateName]);
                CircuitMap[gateName]->FanoutList.push_back(gate);
            }
            else {
                GATE* ptr=new GATE;
                ptr->name=gateName;
                CircuitMap[gateName]=ptr;
                gate->FaninList.push_back(ptr);
                ptr->FanoutList.push_back(gate);
            }
        }
    }
}

void EraseSpaceAndTab(std::string &str) {
    for (int i=0; i<str.size(); i++) {
        if (str[i]==' ' || str[i]=='\t') {
            str.erase(i,1);
            i--;
        }
    }
}

void CIRCUIT::Parser() {
    std::string str;
    std::string::size_type idx;
    while (!infile.eof()) {
        getline(infile,str);
        EraseSpaceAndTab(str);
        if (str.length()==0) {continue;}
        
        if (str.substr(0,5).compare("INPUT")==0) {
            str=str.substr(6);
            idx=str.rfind(')');
            str=str.substr(0,idx);
            AllocGate(str, "PI", "");
        }
        else if (str.substr(0,6).compare("OUTPUT")==0) {
            str=str.substr(7);
            idx=str.rfind(')');
            str=str.substr(0,idx);
            AllocGate("PO_"+str, "PO", str);
        }
        else {
            idx=str.find('=');
            std::string name=str.substr(0,idx);
            str=str.substr(idx+1);
            idx=str.find('(');
            std::string func=str.substr(0,idx);
            str=str.substr(idx+1);
            idx=str.rfind(')');
            str=str.substr(0,idx);
            AllocGate(name, func, str);
        }
    }
}



