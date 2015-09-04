//
// Created by joe on 9/3/15.
//

#include "totimer.h"
#include<stdlib.h>

void quit(NotifyNotification *note,gpointer user_data)
{
    tres* lastres = (tres*)user_data;
    log(lastres,0);
}

void timeup(NotifyNotification *note,const char *action,gpointer user_data){
    g_object_unref(G_OBJECT(note));
    tres* lastres = (tres*)user_data;
    switch (action[0]){
        case 'M':
            settimer(lastres, 5);
            break;
        case 'G':
            log(lastres,1);
            break;
        case 'F':
        default:
            log(lastres,0);
            break;
    }
}

bool notify(gpointer user_data)
{
    tres* lastres = (tres*)user_data;
    NotifyNotification *n;
    n = notify_notification_new ("Tomodori","Time's Up", NULL);
    notify_notification_set_urgency(n,NOTIFY_URGENCY_CRITICAL);
    notify_notification_add_action(n,"M", "More",(NotifyActionCallback)timeup,lastres,NULL);
    notify_notification_add_action(n,"G", "Good",(NotifyActionCallback)timeup,lastres,NULL);
    g_signal_connect (n, "closed", G_CALLBACK(quit), NULL);
//    printf("1");
    notify_notification_set_timeout(n,0); //3 seconds
    notify_notification_show(n,NULL);
    return FALSE;
}

int settimer(tres* lastres, guint32 wait)
{
    lastres->time = lastres->time + wait;
    g_timeout_add(wait*60*1000,(GSourceFunc)notify,lastres);
}