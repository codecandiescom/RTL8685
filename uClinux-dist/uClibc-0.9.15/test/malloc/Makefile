# Makefile for uClibc
#
# Copyright (C) 2000,2001 Erik Andersen <andersen@uclibc.org>
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU Library General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option) any
# later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU Library General Public License for more
# details.
#
# You should have received a copy of the GNU Library General Public License
# along with this program; if not, write to the Free Software Foundation, Inc.,
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

TESTDIR=../
include $(TESTDIR)/Rules.mak


TARGETS=malloc
TARGETS+=testmalloc testmalloc_glibc 
TARGETS+=mallocbug mallocbug_glibc
all: $(TARGETS)

malloc: malloc.c Makefile $(TESTDIR)/Config $(TESTDIR)/Rules.mak $(CC)
	-@ echo "-------"
	-@ echo " "
	-@ echo "Compiling vs uClibc: "
	-@ echo " "
	$(CC) $(CFLAGS) -c $< -o $@.o
	$(CC) $(LDFLAGS) $@.o -o $@ $(EXTRA_LIBS)
	$(STRIPTOOL) -x -R .note -R .comment $@
	-./$@
	-@ echo " "

testmalloc_source:
	-@ echo "-------"
	-@ echo "testmalloc.c source: "
	-@ echo " "
	-@ cat testmalloc.c
	-@ echo " "

testmalloc: testmalloc.c Makefile $(TESTDIR)/Config $(TESTDIR)/Rules.mak $(CC)
	-@ echo "-------"
	-@ echo " "
	-@ echo "Compiling vs uClibc: "
	-@ echo " "
	$(CC) $(CFLAGS) -c $< -o $@.o
	$(CC) $(LDFLAGS) $@.o -o $@ $(EXTRA_LIBS)
	$(STRIPTOOL) -x -R .note -R .comment $@
	-$(LDD) $@
	ls -l $@
	-./$@
	-@ echo " "

testmalloc_glibc: testmalloc.c Makefile
	-@ echo "-------"
	-@ echo " "
	-@ echo "Compiling vs GNU libc: "
	-@ echo " "
	$(HOST_CC) $(GLIBC_CFLAGS) -c $< -o $@.o
	$(HOST_CC) $(GLIBC_LDFLAGS) $@.o -o $@
	$(STRIPTOOL) -x -R .note -R .comment $@
	-$(LDD) $@
	ls -l $@
	-./$@
	-@ echo " "

mallocbug: mallocbug.c Makefile $(TESTDIR)/Config $(TESTDIR)/Rules.mak $(CC)
	-@ echo "-------"
	-@ echo " "
	-@ echo "Compiling vs uClibc: "
	-@ echo " "
	$(CC) $(CFLAGS) -c $< -o $@.o
	$(CC) $(LDFLAGS) $@.o -o $@ $(EXTRA_LIBS)
	$(STRIPTOOL) -x -R .note -R .comment $@
	-$(LDD) $@
	ls -l $@
	-./$@
	-@ echo " "

mallocbug_glibc: mallocbug.c Makefile
	-@ echo "-------"
	-@ echo " "
	-@ echo "Compiling vs GNU libc: "
	-@ echo " "
	$(HOST_CC) $(GLIBC_CFLAGS) -c $< -o $@.o
	$(HOST_CC) $(GLIBC_LDFLAGS) $@.o -o $@
	$(STRIPTOOL) -x -R .note -R .comment $@
	-$(LDD) $@
	ls -l $@
	-./$@
	-@ echo " "


clean:
	rm -f *.[oa] *~ core $(TARGETS)


