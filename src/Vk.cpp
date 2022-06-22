#include "Vk.h"

string Vk::Token;
bool Vk::isMail;
std::thread Vk::thread1;

string Vk::GetToken()
{
    if (strlen(Token.c_str()) >= 1) {
        return Token;
    } else {
        ifstream in((PathToHome + "/.vktoken.txt").c_str());
        in>>Token;
        in.close();
        return Token;
    }
}

void Vk::Messages()
{
    if (Vk::thread1.joinable()) Vk::thread1.join();
    Vk::thread1 = std::thread([&] () {
        LongPoll(0, "", "");
    });
}

void Vk::SetOff()
{
    Curl::Easy("https://api.vk.com/method/account.setOffline?",
            true,
            "uid=67752651&"
            "access_token=" + GetToken());
}

void Vk::LongPoll(int ts, string server, string key)
{
    while (true) {
        if (ts > 0) {
            string json = Curl::Easy("http://" + server + "?",
                    true,
                    "act=a_check&"
                    "wait=25&"
                    "key=" + key + "&"
                    "ts=" + to_string(ts));
            //cout << "LongPoll if (ts > 0)" << json << endl;
            if (json.size() >= 1) {
                if (json.find("failed") == string::npos) {
                    ParsePoll(json);

                    istringstream is(json);
                    boost::property_tree::ptree pt;
                    boost::property_tree::read_json(is, pt);
                    ts = pt.get<int>("ts");
                } else {
                    ts = 0;
                }
            }
        } else {
            string json = Curl::Easy("https://api.vk.com/method/messages.getLongPollServer?",
                    true,
                    "uid=67752651&"
                    "access_token=" + GetToken());
            //cout << "LongPoll else" << json << endl;

            if (json.size() >= 1) {
                istringstream is(json);
                boost::property_tree::ptree pt;
                boost::property_tree::read_json(is, pt);
                key = pt.get<std::string>("response.key");
                server = pt.get<std::string>("response.server");
                ts = pt.get<int>("response.ts");
            }
        }
    }
}

void Vk::ParsePoll(string w)
{
    istringstream is(w);
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(is, pt);

    BOOST_FOREACH(auto &v, pt.get_child("updates"))
    {
        boost::property_tree::ptree::const_iterator it = v.second.begin();
        int sw = it->second.get_value<int>();
        switch (sw) {
            case 6:
            {
                isMail = false;
                Indicator ind;
                ind.SwIcon(false);
                break;
            }
            case 61:
            {
                ++it;
                if (GetSettings("tuping")) {
                    Typing(it->second.get_value<string>());
                }
                break;
            }
            case 80:
            {
                ++it;
                if (it->second.get_value<int>() == 1 && GetSettings("newmail")) {
                    checkNewMail();
                }
                break;
            }
        }
    }
}

void Vk::checkNewMail()
{
    string json = Curl::Easy("https://api.vk.com/method/execute.CheckNewMail?",
            true,
            "v=5.28&"
            "access_token=" + GetToken());
    //cout << "NewMail" << json << endl;

    if (json.size() >= 1) {
        if (json.find("User authorization failed") == string::npos) {
            istringstream is(json);
            boost::property_tree::ptree pt;
            boost::property_tree::read_json(is, pt);
            if (pt.get<string>("response") != "1") {
                string first_name = pt.get<string>("response.first_name");
                string last_name = pt.get<string>("response.last_name");
                string photo_100 = pt.get<string>("response.photo_100");
                string text = pt.get<string>("response.text");
                Curl::SaveImage(photo_100, "/tmp/vk_new_mail_img.jpg");

                /* notify-osd on ubuntu 12.04........... */
                if (system(("killall notify-osd; notify-send \"" + first_name + " " + last_name + "\" \""
                        + text +
                        "\" -i \"/tmp/vk_new_mail_img.jpg\"").c_str()) == 0);

                //Noti(first_name + " " + last_name, text, "/tmp/vk_new_mail_img.jpg", 3000);

                isMail = true;
                Indicator ind;
                ind.SwIcon(true);
            }
        } else {
            if (Auth::isAuthUser()) {
                sleep(1);
                checkNewMail();
            } else {
                exit(1);
            }
        }
    }
}

void Vk::Typing(string uid)
{
    string json = Curl::Easy("https://api.vk.com/method/users.get?",
            true,
            "user_ids=" + uid + "&"
            "fields=photo_100&"
            "v=5.28");

    if (json.size() >= 1) {
        istringstream is(json);
        boost::property_tree::ptree pt;
        boost::property_tree::read_json(is, pt);

        BOOST_FOREACH(auto v, pt.get_child("response"))
        {
            string first_name = v.second.get<string>("first_name");
            string last_name = v.second.get<string>("last_name");
            string photo_100 = v.second.get<string>("photo_100");
            string text = "набирает сообщение...";

            Curl::SaveImage(photo_100, "/tmp/vk_new_mail_img.jpg");

            //if (system(("notify-send \"" + first_name + " " + last_name + "\" \""
            //        + text +
            //        "\" -i \"/tmp/vk_new_mail_img.jpg\"").c_str()) == 0);

            Noti(first_name + " " + last_name, text, "/tmp/vk_new_mail_img.jpg", 1000);
        }
    }
}

void Vk::Noti(string name, string text, string img, int time)
{
    notify_init("vk-messages");
    NotifyNotification *n = notify_notification_new(name.c_str(),
            text.c_str(),
            img.c_str());
    notify_notification_set_timeout(n, time);
    notify_notification_show(n, NULL);
    notify_uninit();
}