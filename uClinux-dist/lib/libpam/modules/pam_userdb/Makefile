#
# This Makefile controls a build process of $(TITLE) module for
# Linux-PAM. You should not modify this Makefile (unless you know
# what you are doing!).

# $Id: Makefile,v 1.1.1.1 2003/08/18 05:39:42 kaohj Exp $
# Created by Cristian Gafton <gafton@redhat.com>

include ../../Make.Rules

TITLE=pam_userdb

ifeq ($(HAVE_NDBM_H),yes)
 WHICH_DB=ndbm
 MODULE_SIMPLE_EXTRALIBS = -lndbm
else
ifeq ($(HAVE_LIBDB),yes)
 WHICH_DB=db
 MODULE_SIMPLE_EXTRALIBS = -ldb
else
 WHICH_DB=none
endif
endif

ifeq ($(WHICH_DB),none)

include ../dont_makefile

else

MODULE_SIMPLE_EXTRAFILES = conv

include ../Simple.Rules

endif
