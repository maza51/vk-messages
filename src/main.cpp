#include "Globals.h"
#include "Indicator.h"
#include "Auth.h"

string PathToApp = "/usr/share/vk-messages";
string PathToHome = getenv("HOME");

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    //notify_init("Test");
    //NotifyNotification *n = notify_notification_new("321", "123", NULL);
    //notify_notification_set_timeout(n, 1000);
    //notify_notification_show(n, NULL);
    
    if (Auth::isAuthUser()) {
        Vk v;
        v.Messages();
        v.SetOff();

        Indicator ind;
        ind.Show();
    } else {
        Auth::AuthUser();
    }

    gtk_main();
    return 0;
}