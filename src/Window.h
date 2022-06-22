#ifndef WINDOW_H
#define	WINDOW_H

#include "Globals.h"

class Window : public Gtk::Window {
public:
    Window();
protected:
    Gtk::Box VBox;
    Gtk::ToolButton Button1, Button2, Button3, Button4, Button5, Button6, Button7;
    Gtk::ScrolledWindow ScrollW1;
private:
};

#endif

