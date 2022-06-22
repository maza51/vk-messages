bin_PROGRAMS = vk-messages

AM_CPPFLAGS = \
	$(vk_messages_CFLAGS) -std=c++0x

AM_CFLAGS =\
	 -Wall\
	 -g

vk_messages_LDFLAGS = \
	-Wl,--export-dynamic

vk_messages_LDADD = $(vk_messages_LIBS)

vk_messages_SOURCES = \
	Globals.h \
	main.cpp \
	Curl.h \
	Curl.cpp \
	Auth.h \
	Auth.cpp \
	Indicator.h \
	Indicator.cpp\
	Window.h \
	Window.cpp \
	Vk.h \
	Vk.cpp \
	Settings.h \
	Settings.cpp