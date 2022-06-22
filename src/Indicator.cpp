#include "Indicator.h"

AppIndicator *Indicator::self_indicator;

Indicator::Indicator()
{
}

Indicator::~Indicator()
{
}

void Indicator::Show()
{
    GtkWidget *menu, *item, *separator;

    menu = gtk_menu_new();

    self_indicator = app_indicator_new("vk-app",
            "vk",
            APP_INDICATOR_CATEGORY_APPLICATION_STATUS);

    app_indicator_set_menu(self_indicator, GTK_MENU(menu));
    app_indicator_set_status(self_indicator, APP_INDICATOR_STATUS_ACTIVE);

    app_indicator_set_icon(self_indicator, (PathToApp + "/data/vk.svg").c_str());

    item = gtk_menu_item_new_with_label("Open Vk");
    gtk_widget_show(item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
    g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(ActivateVK), NULL);

    separator = gtk_separator_menu_item_new();
    gtk_widget_show(separator);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), separator);

    item = gtk_menu_item_new_with_label("Quit");
    gtk_widget_show(item);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
    g_signal_connect(G_OBJECT(item), "activate", G_CALLBACK(Quit), NULL);
}

gboolean Indicator::Timer(gpointer data)
{
    return FALSE;
}

void Indicator::SwIcon(bool w)
{
    if (w) {
        app_indicator_set_icon(self_indicator, (PathToApp + "/data/vk_noti.svg").c_str());
    } else {
        app_indicator_set_icon(self_indicator, (PathToApp + "/data/vk.svg").c_str());
    }
}

void Indicator::ActivateVK()
{
    //Window w;
    //w.ShowWindow();
}

void Indicator::Quit()
{
    //if (Vk::thread1.joinable()) Vk::thread1.join();
    gtk_main_quit();
}