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
#include <cstdlib>
#include <string>

class DelayLibrary {
private:
    FILE *pFile;
    
    
    void Parser();
    
public:
    DelayLibrary(std::string filename) {
        pFile = fopen(filename.c_str(), "r");
        if (pFile==NULL) {
            std::cout<<filename<<" doesn't exist."<<std::endl;
            exit(-1);
        }
    }
};

#endif /* defined(__STA__libraryParser__) */
