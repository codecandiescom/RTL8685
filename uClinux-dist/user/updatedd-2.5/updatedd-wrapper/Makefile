# -- updatedd: Makefile.in --
#
# Copyright (C) 2004, 2005 Philipp Benner
#
# This file is part of UpdateDD - http://updatedd.philipp-benner.de.
#
# UpdateDD is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# any later version.
#
# UpdateDD is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with UpdateDD; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

SHELL		= /bin/sh -e

bin		= updatedd-wrapper
conf		= updatedd-wrapper.conf

prefix		= /usr/local
exec_prefix	= ${prefix}
bindir		= ${exec_prefix}/bin
sysconfdir	= ${prefix}/etc
mandir		= ${prefix}/man
srcdir		= .

INSTALL		= /usr/bin/install -c

all:
	./create-config $(prefix)
clean:
	$(RM) updatedd-wrapper.conf

distclean:
	$(RM) Makefile
	$(RM) create-config
	$(RM) updatedd-wrapper

install:
	$(INSTALL) -d $(DESTDIR)$(bindir)
	$(INSTALL) -m 755 $(bin) $(DESTDIR)$(bindir)

	if test ! -e $(DESTDIR)$(sysconfdir)/$(conf); then		\
		$(INSTALL) -d $(DESTDIR)$(sysconfdir);			\
		$(INSTALL) -m 600 $(conf) $(DESTDIR)$(sysconfdir);	\
	fi

	$(INSTALL) -d $(DESTDIR)$(mandir)/man1
	$(INSTALL) -d $(DESTDIR)$(mandir)/man5

	$(INSTALL) -m 644 $(srcdir)/updatedd-wrapper.1 $(DESTDIR)$(mandir)/man1
	$(INSTALL) -m 644 $(srcdir)/updatedd-wrapper.conf.5 $(DESTDIR)$(mandir)/man5

uninstall:
	$(RM) $(bindir)$(bin)
	$(RM) $(sysconfdir)$(conf)

	$(RM) $(mandir)/man1/updatedd-wrapper.1
	$(RM) $(mandir)/man5/updatedd-wrapper.conf.5

.PHONY: all clean distclean install uninstall
