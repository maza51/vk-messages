#ifndef INDICATOR_H
#define	INDICATOR_H

#include "Globals.h"
#include "Auth.h"
#include "Vk.h"
#include "Window.h"

class Indicator {
public:
    Indicator();
    virtual ~Indicator();
    void Show();
    void SwIcon(bool w);
protected:
    static AppIndicator *self_indicator;
    static gboolean Timer(gpointer data);
    static void ActivateVK();
    static void Quit();
};

#endif

