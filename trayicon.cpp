//
// Created by joe on 9/6/15.
//

#include "trayicon.h"
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "pomodori.h"
#include "logging.h"
#include "totimer.h"

#define FREESYM "/usr/share/icons/gnome/scalable/actions/view-list-symbolic.svg"
#define BUSYSYM "/usr/share/icons/gnome/scalable/actions/view-dual-symbolic.svg"

const int objn = 4;
const char* objs[] = {"Paper","Study","Homework","Project"};

GtkStatusIcon *tray;
GtkWidget *tray_menu;

void menucall(GtkMenuItem *menuitem,gpointer user_data)
{
    tres *lastres = new tres;
    lastres->time=0;
    lastres->reason=new char[10];
    strcpy(lastres->reason,(char *)user_data);
    timer_set(lastres,POTIME);
    tray_activate((char *)user_data);
}

void on_right (GtkStatusIcon *status_icon,guint button,guint activate_time,gpointer user_data){
    gtk_menu_popup(GTK_MENU(tray_menu),NULL,NULL,NULL,NULL,button,activate_time);
}

void closeall(GtkMenuItem *menuitem,gpointer user_data)
{
    exit(0);
}

void stop(GtkMenuItem *menuitem,gpointer user_data)
{
    timer_kill();
}

void starttimer(const char* reason);

void tray_init()
{
    tray = gtk_status_icon_new();
    tray_deactivate();
    gtk_status_icon_set_visible(tray, TRUE);

    tray_menu = gtk_menu_new ();    /* Don't need to show menus */

    /* Create the menu items */
    GtkWidget *items[objn];
    for (int i=0;i<objn;++i)
    {
        items[i]=gtk_menu_item_new_with_label (objs[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL (tray_menu), items[i]);
        g_signal_connect (items[i], "activate", G_CALLBACK(menucall), gpointer(objs[i]));
        gtk_widget_show (items[i]);
    }
    GtkWidget *stop_item = gtk_menu_item_new_with_label ("Stop");
    GtkWidget *exit_item = gtk_menu_item_new_with_label ("Exit");
    GtkWidget *sep_item = gtk_separator_menu_item_new();

    gtk_menu_shell_append(GTK_MENU_SHELL (tray_menu), sep_item);
    gtk_menu_shell_append(GTK_MENU_SHELL (tray_menu), stop_item);
    gtk_menu_shell_append(GTK_MENU_SHELL (tray_menu), exit_item);

    /* Attach the callback functions to the activate signal */
    g_signal_connect (stop_item, "activate", G_CALLBACK(stop), NULL);
    g_signal_connect (exit_item, "activate", G_CALLBACK(closeall), NULL);

    /* We do need to show menu items */
    gtk_widget_show (sep_item);
    gtk_widget_show (stop_item);
    gtk_widget_show (exit_item);

    g_signal_connect (tray, "popup-menu", G_CALLBACK(on_right), NULL);
}

void tray_activate(char* info)
{
    gtk_status_icon_set_from_file(tray,BUSYSYM);
    char inf[30];
    sprintf(inf,APPNAME " - %s",info);
    gtk_status_icon_set_tooltip_text(tray, inf);
}

void tray_deactivate()
{
    gtk_status_icon_set_from_file(tray,FREESYM);
    gtk_status_icon_set_tooltip_text(tray, APPNAME);
}