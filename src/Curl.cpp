#include "Curl.h"

size_t Curl::Write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*) userp)->append((char*) contents, size * nmemb);
    return size * nmemb;
}

string Curl::Easy(string url, bool post, string param)
{
    CURL *curl;
    CURLcode res;
    string readBuffer;
    //int retries = 2;

    curl = curl_easy_init();
    if (curl) {
        //do {
        if (post) {
            curl_easy_setopt(curl, CURLOPT_POST, 1);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, param.c_str());
        } else {
            curl_easy_setopt(curl, CURLOPT_HEADER, TRUE);
        }
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, TRUE);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 1);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, (PathToHome + "/.vkcookies.txt").c_str());
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, (PathToHome + "/.vkcookies.txt").c_str());
        res = curl_easy_perform(curl);
        //} while (CURLE_OK != res && retries--);

        curl_easy_cleanup(curl);

        return readBuffer;
    }
}

void Curl::SaveImage(string url, string path)
{
    CURL *image;
    CURLcode imgresult;
    FILE *fp;

    image = curl_easy_init();
    if (image) {
        fp = fopen(path.c_str(), "w");
        if (fp == NULL) cout << "File cannot be opened";

        curl_easy_setopt(image, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(image, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(image, CURLOPT_URL, url.c_str());

        imgresult = curl_easy_perform(image);
    }
    curl_easy_cleanup(image);
    fclose(fp);
}