//
// Created by joe on 9/3/15.
//

#include "totimer.h"
#include<stdio.h>
#include "pomodori.h"
#include "trayicon.h"

bool timeout;
guint timerid;

void timer_kill()
{
    if (timeout)
    {
        g_source_remove(timerid);
        timeout=false;
        tray_deactivate();
    }
}

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
            timer_set(lastres, POTEXT);
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
    timeout=false;
    tres* lastres = (tres*)user_data;
    NotifyNotification *n;
    char str[20];
    if (lastres->time>POTIME)
        sprintf(str,"Time's up!(%d)",lastres->time-POTIME);
    else
        sprintf(str,"Time's up!");
    n = notify_notification_new (APPNAME,str, NULL);
    notify_notification_set_urgency(n,NOTIFY_URGENCY_CRITICAL);
    notify_notification_add_action(n,"M", "More",(NotifyActionCallback)timeup,lastres,NULL);
    notify_notification_add_action(n,"G", "Good",(NotifyActionCallback)timeup,lastres,NULL);
    g_signal_connect (n, "closed", G_CALLBACK(quit), NULL);
    notify_notification_set_timeout(n,0); //3 seconds
    notify_notification_show(n,NULL);
    return FALSE;
}

void timer_set(tres* lastres, guint32 wait)
{
    if (!timeout)
    {
        timeout=true;
        lastres->time = lastres->time + wait;
        timerid = g_timeout_add(wait*60*1000,(GSourceFunc)notify,lastres);
    }
}

void timer_init()
{
    timeout=false;
    notify_init(APPNAME);
}