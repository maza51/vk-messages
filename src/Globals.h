#ifndef GLOBALS_H
#define	GLOBALS_H

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <curl/curl.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <webkit/webkit.h>
#include <thread>

#include <gtkmm.h>
#include <libnotify/notify.h>
#include <libappindicator/app-indicator.h>

using namespace std;
using namespace boost;

extern string PathToApp;
extern string PathToHome;

#endif

