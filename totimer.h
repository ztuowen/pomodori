//
// Created by joe on 9/3/15.
//

#ifndef POMODORI_TOTIMER_H
#define POMODORI_TOTIMER_H

#include <libnotify/notify.h>
#include "logging.h"
#include "glib.h"

#define POTIME 25
#define POTEXT 5

bool notify(gpointer user_data);

int settimer(tres* lastres,guint32 wait);

#endif //POMODORI_TOTIMER_H
