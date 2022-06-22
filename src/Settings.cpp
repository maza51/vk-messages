#include "Settings.h"

Settings::Settings()
{
    setting = g_settings_new("apps.vk-messages");
    
}

Settings::~Settings()
{
}

gboolean Settings::GetSettings(string s)
{
    return g_settings_get_boolean(setting, s.c_str());
}

