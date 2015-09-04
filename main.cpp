#include <glib.h>
#include<libnotify/notify.h>
#include <gtk/gtk.h>
#include "logging.h"
#include "totimer.h"

int main(int argc, char** argv)
{
    if (argc<2)
        return 0;
    gtk_init(&argc, &argv);
    notify_init("pomodori");
    tres lastres;
    lastres.time=0;
    lastres.reason=argv[1];
    settimer(&lastres,1);
    gtk_main();
    return 0;
}