#ifndef AUTH_H
#define	AUTH_H

#include "Globals.h"
#include "Vk.h"
#include "Curl.h"

class Auth {
public:
    static void AuthUser();
    static bool isAuthUser();
protected:
    static void LoadFinished(WebKitWebView *web_view, WebKitWebFrame *web_frame, gpointer data);
};

#endif

