#ifndef CURL_H
#define	CURL_H

#include "Globals.h"

using namespace std;

class Curl {
public:
    static string Easy(string url, bool post, string param);
    static void SaveImage(string url, string path);
protected:
    static size_t Write_callback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif

