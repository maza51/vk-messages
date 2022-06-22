#ifndef VK_H
#define	VK_H

#include "Globals.h"
#include "Curl.h"
#include "Auth.h"
#include "Indicator.h"
#include "Settings.h"

class Vk : public Settings {
public:
    string GetToken();
    void Messages();
    void SetOff();
    void LongPoll(int ts, string server, string key);
    void checkNewMail();
    void Typing(string uid);
    void Noti(string name, string text, string img, int time);
    static bool isMail;
    static std::thread thread1;
private:
    void ParsePoll(string w);
    static string Token;
};

#endif

