MODULE = pcmanfm-audio-length
LIBDIR = /usr/lib/arm-linux-gnueabihf
DESTDIR =
CFLAGS = `pkg-config --cflags libfm taglib` -ltag_c -shared -fPIC -Wall

all:
	gcc -o $(MODULE).so $(CFLAGS) $(MODULE).c

install:
	install $(MODULE).so $(DESTDIR)$(LIBDIR)/libfm/modules

uninstall:
	rm $(DESTDIR)$(LIBDIR)/libfm/modules/$(MODULE).so
