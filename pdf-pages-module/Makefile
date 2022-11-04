MODULE = pcmanfm-pdf-pages
LIBDIR = /usr/lib/x86_64-linux-gnu
DESTDIR =
CFLAGS = `pkg-config --cflags --libs libfm` -shared -fPIC -Wall

all:
	gcc -o $(MODULE).so $(CFLAGS) $(MODULE).c

install:
	install $(MODULE).so $(DESTDIR)$(LIBDIR)/libfm/modules

uninstall:
	rm $(DESTDIR)$(LIBDIR)/libfm/modules/$(MODULE).so
