#include "Auth.h"

void Auth::LoadFinished(WebKitWebView *web_view, WebKitWebFrame *web_frame, gpointer data)
{
    auto window = (GtkWidget*) data;
    string url = webkit_web_view_get_uri(web_view);
    size_t pos = url.find("access_token");
    if (pos != string::npos) {
        try {
            /* A ne4ego pogklu4atj biblioteku */
            char cmd[250];
            sprintf(cmd, "echo \'%s\' | grep -Po  \'access_token=\\K([^&]+)\'", url.c_str());

            FILE * f = popen(cmd, "r");
            char buf[300];
            if (fgets(buf, 300, f));
            pclose(f);

            ofstream out((PathToHome + "/.vktoken.txt").c_str());
            out << (buf);
            out.close();
            
            Vk v;
            v.Messages();
            v.SetOff();

            Indicator ind;
            ind.Show();

            gtk_widget_hide_on_delete(window);
        } catch (...) {
            webkit_web_view_load_html_string(web_view,
                    "<html align=\"center\">Restart the application</html>", "");
        }
    }
}

void Auth::AuthUser()
{
    GtkWidget *window, *box, *scroll, *web_view;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    SoupSession *session;
    session = webkit_get_default_session();
    SoupCookieJar* cookie = soup_cookie_jar_text_new((PathToHome + "/.vkcookies.txt").c_str(), FALSE);
    soup_session_add_feature(session, SOUP_SESSION_FEATURE(cookie));

    gtk_window_set_title(GTK_WINDOW(window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 500);
    gtk_container_set_border_width(GTK_CONTAINER(window), 8);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    //g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(window), box);

    scroll = gtk_scrolled_window_new(NULL, NULL);
    g_object_set(scroll, "shadow-type", GTK_SHADOW_IN, NULL);
    gtk_box_pack_start(GTK_BOX(box), scroll, TRUE, TRUE, 0);

    web_view = webkit_web_view_new();
    gtk_container_add(GTK_CONTAINER(scroll), web_view);
    webkit_web_view_open(WEBKIT_WEB_VIEW(web_view), "https://oauth.vk.com/authorize?"
            "client_id=4736418&"
            "scope=messages&"
            "redirect_uri=http://oauth.vk.com/blank.html&"
            "display=mobile&"
            "response_type=token");
    g_signal_connect(web_view, "load-finished", G_CALLBACK(LoadFinished), window);
    gtk_widget_show_all(window);
}

bool Auth::isAuthUser()
{
    string json = Curl::Easy("https://oauth.vk.com/authorize?"
            "client_id=4736418&"
            "scope=messages&"
            "redirect_uri=http://oauth.vk.com/blank.html&"
            "display=wap&"
            "response_type=token",
            false,
            "");

    string cmd = "echo \'" + json + "\' | grep -Po  \'access_token=\\K([^&]+)\'";

    FILE* pipe = popen(cmd.c_str(), "r");
    char buffer[128];
    std::string result = "";
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);

    if (result.size() > 1) {
        ofstream out((PathToHome + "/.vktoken.txt").c_str());
        out << (result);
        out.close();
        return true;
    }
    return false;
}