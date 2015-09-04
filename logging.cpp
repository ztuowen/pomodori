//
// Created by joe on 9/3/15.
//

#include "logging.h"
#include "stdlib.h"
#include<iostream>
#include <fstream>
#include <ctime>

using namespace std;
void log(tres* res,int code)
{
    if (code)
    {
        ofstream fot;
        fot.open("~/.pomodori");
        time_t now = time(0);
        fot<<ctime(&now)<<endl;
    }
    exit(0);
}