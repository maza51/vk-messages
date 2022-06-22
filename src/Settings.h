#ifndef SETTINGS_H
#define	SETTINGS_H

#include "Globals.h"

class Settings {
public:
    Settings();
    virtual ~Settings();
    gboolean GetSettings(string s);
private:
    GSettings *setting;

};

#endif

