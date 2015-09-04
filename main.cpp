#include <glib.h>
#include<libnotify/notify.h>
#include <gtk/gtk.h>
#include "logging.h"
#include "totimer.h"

int main(int argc, char** argv)
{
    gtk_init(&argc, &argv);
    notify_init("Tomodori");
    tres lastres;
    lastres.time=0;
    settimer(&lastres,POTIME);
    gtk_main();
    return 0;
}