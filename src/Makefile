TARGETS	= $(OBJDIR)../data/Splasher.h $(OBJDIR)Splasher$(EXEEXT)
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
BINDIR	= $(PREFIX)/bin
SBINDIR	= $(PREFIX)/sbin
CC	= cc
CPPFLAGSF= -I ../include
CPPFLAGS=
CFLAGSF	= -W `pkg-config --cflags libApp`
CFLAGS	= -Wall -g -O2 -pedantic
LDFLAGSF= `pkg-config --libs libApp` -Wl,--export-dynamic
LDFLAGS	= 
EXEEXT	=
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

$(OBJDIR)../data/Splasher.h: ../data/Splasher.interface
	./appbroker.sh -P "$(PREFIX)" -- "$(OBJDIR)../data/Splasher.h"

Splasher_OBJS = $(OBJDIR)splasher.o $(OBJDIR)main.o
Splasher_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
Splasher_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)Splasher$(EXEEXT): $(Splasher_OBJS)
	$(CC) -o $(OBJDIR)Splasher$(EXEEXT) $(Splasher_OBJS) $(Splasher_LDFLAGS)

$(OBJDIR)splasher.o: splasher.c ../data/Splasher.h
	$(CC) $(Splasher_CFLAGS) -o $(OBJDIR)splasher.o -c splasher.c

$(OBJDIR)main.o: main.c
	$(CC) $(Splasher_CFLAGS) -o $(OBJDIR)main.o -c main.c

clean:
	$(RM) -- $(../data/Splasher.h_OBJS) $(Splasher_OBJS)
	./appbroker.sh -c -P "$(PREFIX)" -- "$(OBJDIR)../data/Splasher.h"

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)
	$(MKDIR) $(DESTDIR)$(BINDIR)
	$(INSTALL) -m 0755 $(OBJDIR)Splasher$(EXEEXT) $(DESTDIR)$(BINDIR)/Splasher$(EXEEXT)

uninstall:
	$(RM) -- $(DESTDIR)$(BINDIR)/Splasher$(EXEEXT)

.PHONY: all clean distclean install uninstall
