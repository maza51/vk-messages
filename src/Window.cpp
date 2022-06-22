#include <webkitgtk-3.0/webkit/webkitwebview.h>

#include "Window.h"

Window::Window()
{
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file((PathToApp + "/data/VkWind.glade").c_str());
    builder->get_widget("window1", Window);
}