#
# $Id: Makefile,v 1.1.1.1 2003/08/18 05:39:42 kaohj Exp $
#
# This directory contains a pam_filter filter executable
#
# Created by Andrew Morgan <morgan@transmeta.com> 1996/3/11
#

include ../../../Make.Rules

TITLE=upperLOWER

#

CFLAGS += -I../include

OBJS = $(TITLE).o

####################### don't edit below #######################

all: $(TITLE)

$(TITLE): $(OBJS)
	$(CC) -o $(TITLE) $(OBJS)
	$(STRIP) $(TITLE)

install:
	$(MKDIR) $(FAKEROOT)$(FILTERSDIR)
	$(INSTALL) -m 511 $(TITLE) $(FAKEROOT)$(FILTERSDIR)

remove:
	cd $(FAKEROOT)$(FILTERSDIR) && rm -f $(TITLE)

clean:
	rm -f $(TITLE) $(OBJS) core *~

.c.o:	
	$(CC) $(CFLAGS) -c $<

