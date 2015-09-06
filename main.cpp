#include <glib.h>
#include<libnotify/notify.h>
#include <gtk/gtk.h>
#include "logging.h"
#include "totimer.h"
#include "pomodori.h"
#include "trayicon.h"
#include "string.h"


int main(int argc, char** argv)
{
    gtk_init(&argc, &argv);
    timer_init();
    tray_init();
    gtk_main();
    return 0;
}