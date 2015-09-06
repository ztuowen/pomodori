//
// Created by joe on 9/3/15.
//

#ifndef POMODORI_LOGGING_H
#define POMODORI_LOGGING_H

#include <glib.h>

typedef struct tres {
    guint32 time;
    char* reason;
} tres;

void log(tres* res,int code);

#endif //POMODORI_LOGGING_H
