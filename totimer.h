//
// Created by joe on 9/3/15.
//

#ifndef POMODORI_TOTIMER_H
#define POMODORI_TOTIMER_H

#include <libnotify/notify.h>
#include "logging.h"
#include "glib.h"

#define POTIME 1
#define POTEXT 5

void timer_init();

bool notify(gpointer user_data);

void timer_set(tres* lastres,guint32 wait);

void timer_kill();

#endif //POMODORI_TOTIMER_H
