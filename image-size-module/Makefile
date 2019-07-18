MODULE = pcmanfm-image-size
LIBDIR = /usr/lib/arm-linux-gnueabihf
DESTDIR =
CFLAGS = `pkg-config --cflags --libs libfm` -shared -fPIC -Wall

all:
	gcc -o $(MODULE).so $(CFLAGS) $(MODULE).c imagesize.c

install:
	install $(MODULE).so $(DESTDIR)$(LIBDIR)/libfm/modules

uninstall:
	rm $(DESTDIR)$(LIBDIR)/libfm/modules/$(MODULE).so
