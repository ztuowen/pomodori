//
// Created by joe on 9/3/15.
//

#include "logging.h"
#include "stdlib.h"
#include<iostream>
#include <fstream>

using namespace std;
void log(tres* res,int code)
{
    if (code)
    {
        ofstream fot;
        fot.open("~/.pomodori");
        fot<<1<<endl;
    }
    exit(0);
}