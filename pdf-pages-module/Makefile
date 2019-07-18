MODULE = pcmanfm-pdf-pages
LIBDIR = /usr/lib/arm-linux-gnueabihf
DESTDIR =
CFLAGS = `pkg-config --cflags --libs libfm poppler-glib` -shared -fPIC -Wall

all:
	gcc -o $(MODULE).so $(CFLAGS) $(MODULE).c

install:
	install $(MODULE).so $(DESTDIR)$(LIBDIR)/libfm/modules

uninstall:
	rm $(DESTDIR)$(LIBDIR)/libfm/modules/$(MODULE).so
