//
//  main.cpp
//  STA
//
//  Created by lin shih-feng on 2013/12/20.
//  Copyright (c) 2013年 lin shih-feng. All rights reserved.
//

#include <iostream>
#include "libraryParser.h"
using namespace std;

DelayLibrary library;

int main(int argc, const char * argv[])
{
    string DelayLibrary="nctu_18.tech";
    
    if (library.InitialLibrary(DelayLibrary)==0) {
        return -1;
    }
    
    return 0;
}

