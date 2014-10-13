# Generated automatically from Makefile.in by configure.
###########################################################################
# Makefile.in for Samba - rewritten for autoconf support
# Copyright Andrew Tridgell 1992-1998
###########################################################################

FLTFLAGS += -s 128000

prefix=
exec_prefix=${prefix}
mandir=${prefix}/man

LIBS=$(LIBCRYPT)
#-lreadline -ldl  -lcrypt
CPPFLAGS=
AWK=mawk

INSTALLCMD=/usr/bin/install -c

srcdir=.
SHELL=/bin/sh

BASEDIR= /
BINDIR = /bin
# we don't use sbindir because we want full compatibility with
# the previous releases of Samba
SBINDIR = /bin
LIBDIR = /etc/config
VARDIR = /var/log
MANDIR = ${prefix}/home/samba/man
SAMBABOOK = ${prefix}/home/samba/swat/using_samba

# The permissions to give the executables
INSTALLPERMS = 0755

# set these to where to find various files
# These can be overridden by command line switches (see smbd(8))
# or in smb.conf (see smb.conf(5))
SMBLOGFILE = $(VARDIR)/log.smb
NMBLOGFILE = $(VARDIR)/log.nmb
CONFIGFILE = $(LIBDIR)/smb.conf
LMHOSTSFILE = $(LIBDIR)/lmhosts
DRIVERFILE = $(LIBDIR)/printers.def
PASSWD_PROGRAM = /bin/passwd
# This is where smbpasswd et al go
PRIVATEDIR = $(LIBDIR)

SMB_PASSWD_FILE = $(PRIVATEDIR)/smbpasswd

# This is where SWAT images and help files go
SWATDIR = /home/samba/swat

# the directory where lock files go
LOCKDIR = $(VARDIR)/locks

# The directory where code page definition files go
CODEPAGEDIR = /home/samba/codepages

# The current codepage definition list.
CODEPAGELIST= 437 737 775 850 852 861 932 866 949 950 936 1251 ISO8859-1 ISO8859-2 ISO8859-5 ISO8859-7 KOI8-R

# where you are going to have the smbrun binary. This defaults to the 
# install directory. This binary is needed for correct printing
# and magic script execution. This should be an absolute path!
# Also not that this should include the name "smbrun" on the end (the
# name of the executable)
SMBRUN = $(BINDIR)/smbrun

PASSWD_FLAGS = -DPASSWD_PROGRAM=\"$(PASSWD_PROGRAM)\" -DSMB_PASSWD_FILE=\"$(SMB_PASSWD_FILE)\"
FLAGS1 = $(CFLAGS) -Iinclude -I$(srcdir)/include -I$(srcdir)/ubiqx -I$(srcdir)/smbwrapper $(CPPFLAGS) -DSMBLOGFILE=\"$(SMBLOGFILE)\" -DNMBLOGFILE=\"$(NMBLOGFILE)\"
FLAGS2 = -DCONFIGFILE=\"$(CONFIGFILE)\" -DLMHOSTSFILE=\"$(LMHOSTSFILE)\"  
FLAGS3 = -DSWATDIR=\"$(SWATDIR)\" -DSBINDIR=\"$(SBINDIR)\" -DLOCKDIR=\"$(LOCKDIR)\" -DSMBRUN=\"$(SMBRUN)\" -DCODEPAGEDIR=\"$(CODEPAGEDIR)\"
FLAGS4 = -DDRIVERFILE=\"$(DRIVERFILE)\" -DBINDIR=\"$(BINDIR)\"
FLAGS5 = $(FLAGS1) $(FLAGS2) $(FLAGS3) $(FLAGS4) -DHAVE_INCLUDES_H
FLAGS  = $(ISA) $(FLAGS5) $(PASSWD_FLAGS)
FLAGS32  = $(ISA32) $(FLAGS5) $(PASSWD_FLAGS)

SPROGS = bin/smbd bin/nmbd 
#bin/swat
#PROGS1 = bin/testparm bin/smbstatus
# bin/smbclient bin/smbspool bin/testprns 
#PROGS2 = bin/rpcclient bin/smbpasswd bin/make_smbcodepage bin/make_unicodemap  
MPROGS =
ifeq ($(CONFIG_USER_SAMBA_SMBMOUNT),y)
MPROGS = bin/smbmount bin/smbmnt bin/smbumount
endif
PROGS = $(PROGS1) $(PROGS2) $(MPROGS) 
#bin/nmblookup bin/make_printerdef 

SCRIPTS = $(srcdir)/script/smbtar $(srcdir)/script/addtosmbpass $(srcdir)/script/convert_smbpasswd

QUOTAOBJS=noquotas.o

######################################################################
# object file lists
######################################################################

LIB_OBJ = lib/charcnv.o lib/charset.o lib/debug.o lib/fault.o \
          lib/getsmbpass.o lib/interface.o lib/kanji.o lib/md4.o \
          lib/interfaces.o lib/pidfile.o lib/replace.o \
          lib/signal.o lib/slprintf.o lib/system.o lib/doscalls.o lib/time.o \
	  lib/ufc.o lib/genrand.o lib/username.o lib/access.o lib/smbrun.o \
	  lib/bitmap.o lib/crc32.o lib/snprintf.o \
	  lib/util_str.o lib/util_sid.o \
	  lib/util_unistr.o lib/util_file.o \
	  lib/util.o lib/util_sock.o lib/util_sec.o smbd/ssl.o lib/fnmatch.o \
	  lib/talloc.o lib/hash.o

UBIQX_OBJ = ubiqx/ubi_BinTree.o ubiqx/ubi_Cache.o ubiqx/ubi_SplayTree.o \
            ubiqx/ubi_dLinkList.o ubiqx/ubi_sLinkList.o ubiqx/debugparse.o

PARAM_OBJ = param/loadparm.o param/params.o 

LIBSMB_OBJ = libsmb/clientgen.o libsmb/namequery.o libsmb/nmblib.o \
             libsmb/nterr.o libsmb/smbdes.o libsmb/smbencrypt.o \
             libsmb/smberr.o libsmb/credentials.o libsmb/pwd_cache.o \
	     libsmb/passchange.o

RPC_SERVER_OBJ = rpc_server/srv_lsa.o \
                 rpc_server/srv_lsa_hnd.o rpc_server/srv_netlog.o \
                 rpc_server/srv_pipe_hnd.o rpc_server/srv_reg.o \
                 rpc_server/srv_samr.o rpc_server/srv_srvsvc.o \
                 rpc_server/srv_util.o rpc_server/srv_wkssvc.o \
		rpc_server/srv_pipe.o

RPC_PARSE_OBJ = rpc_parse/parse_lsa.o rpc_parse/parse_misc.o \
                rpc_parse/parse_net.o rpc_parse/parse_prs.o \
                rpc_parse/parse_reg.o rpc_parse/parse_rpc.o \
                rpc_parse/parse_samr.o rpc_parse/parse_srv.o \
                rpc_parse/parse_wks.o rpc_parse/parse_sec.o

RPC_CLIENT_OBJ = \
		rpc_client/cli_login.o    \
		rpc_client/cli_netlogon.o \
		rpc_client/cli_pipe.o     \
		rpc_client/cli_lsarpc.o   \
		rpc_client/cli_wkssvc.o   \
		rpc_client/cli_srvsvc.o   \
		rpc_client/cli_reg.o   \
		rpc_client/cli_samr.o 


LOCKING_OBJ = locking/locking.o locking/locking_shm.o locking/locking_slow.o \
              locking/shmem.o locking/shmem_sysv.o

PASSDB_OBJ = passdb/passdb.o passdb/smbpassfile.o passdb/smbpass.o \
             passdb/pass_check.o passdb/ldap.o passdb/nispass.o passdb/smbpasschange.o

PROFILE_OBJ = profile/profile.o

SMBD_OBJ1 = smbd/server.o smbd/files.o smbd/chgpasswd.o smbd/connection.o \
            smbd/dfree.o smbd/dir.o smbd/password.o smbd/conn.o smbd/fileio.o \
            smbd/ipc.o smbd/mangle.o smbd/negprot.o \
            smbd/message.o smbd/nttrans.o smbd/pipes.o smbd/predict.o \
            smbd/$(QUOTAOBJS) smbd/reply.o smbd/trans2.o smbd/uid.o \
	    smbd/dosmode.o smbd/filename.o smbd/open.o smbd/close.o smbd/blocking.o \
	    smbd/process.o smbd/oplock.o smbd/service.o smbd/error.o

PRINTING_OBJ = printing/pcap.o printing/print_svid.o printing/printing.o \
		printing/print_cups.o

SMBD_OBJ = $(SMBD_OBJ1) $(PARAM_OBJ) $(LIBSMB_OBJ) $(UBIQX_OBJ) \
           $(RPC_SERVER_OBJ) $(RPC_CLIENT_OBJ) $(RPC_PARSE_OBJ) \
           $(LOCKING_OBJ) $(PASSDB_OBJ) $(PRINTING_OBJ) $(PROFILE_OBJ) $(LIB_OBJ)


NMBD_OBJ1 = nmbd/asyncdns.o nmbd/nmbd.o nmbd/nmbd_become_dmb.o \
            nmbd/nmbd_become_lmb.o nmbd/nmbd_browserdb.o \
            nmbd/nmbd_browsesync.o nmbd/nmbd_elections.o \
            nmbd/nmbd_incomingdgrams.o nmbd/nmbd_incomingrequests.o \
            nmbd/nmbd_lmhosts.o nmbd/nmbd_logonnames.o nmbd/nmbd_mynames.o \
            nmbd/nmbd_namelistdb.o nmbd/nmbd_namequery.o \
            nmbd/nmbd_nameregister.o nmbd/nmbd_namerelease.o \
            nmbd/nmbd_nodestatus.o nmbd/nmbd_packets.o \
            nmbd/nmbd_processlogon.o nmbd/nmbd_responserecordsdb.o \
            nmbd/nmbd_sendannounce.o nmbd/nmbd_serverlistdb.o \
            nmbd/nmbd_subnetdb.o nmbd/nmbd_winsproxy.o nmbd/nmbd_winsserver.o \
            nmbd/nmbd_workgroupdb.o nmbd/nmbd_synclists.o

NMBD_OBJ = $(NMBD_OBJ1) $(PARAM_OBJ) $(LIBSMB_OBJ) $(UBIQX_OBJ) \
           $(LIB_OBJ)

SWAT_OBJ = web/cgi.o web/diagnose.o web/startstop.o web/statuspage.o \
           web/swat.o $(LIBSMB_OBJ) $(LOCKING_OBJ) \
           $(PARAM_OBJ) $(PASSDB_OBJ) $(RPC_CLIENT_OBJ) $(RPC_PARSE_OBJ) \
           $(UBIQX_OBJ) $(LIB_OBJ) $(PRINTING_OBJ)

SMBRUN_OBJ = utils/smbrun.o lib/util_sec.o

SMBSH_OBJ = smbwrapper/smbsh.o smbwrapper/shared.o \
            $(PARAM_OBJ) $(UBIQX_OBJ) $(LIB_OBJ)

MAKE_SMBCODEPAGE_OBJ = utils/make_smbcodepage.o $(PARAM_OBJ) \
                       $(UBIQX_OBJ) $(LIB_OBJ)

MAKE_UNICODEMAP_OBJ = utils/make_unicodemap.o $(PARAM_OBJ) \
                       $(UBIQX_OBJ) $(LIB_OBJ)

MAKE_PRINTERDEF_OBJ = utils/make_printerdef.o $(PARAM_OBJ) \
                      $(UBIQX_OBJ) $(LIB_OBJ)

STATUS_OBJ = utils/status.o $(LOCKING_OBJ) $(PARAM_OBJ) \
             $(UBIQX_OBJ) $(PROFILE_OBJ) $(LIB_OBJ)

TESTPARM_OBJ = utils/testparm.o \
               $(PARAM_OBJ) $(UBIQX_OBJ) $(LIB_OBJ)

TESTPRNS_OBJ = utils/testprns.o $(PARAM_OBJ) $(PRINTING_OBJ) $(UBIQX_OBJ) \
               $(LIB_OBJ)

SMBPASSWD_OBJ = utils/smbpasswd.o $(PARAM_OBJ) $(LIBSMB_OBJ) $(PASSDB_OBJ) \
                $(UBIQX_OBJ) $(RPC_CLIENT_OBJ) $(RPC_PARSE_OBJ) $(LIB_OBJ)

RPCCLIENT_OBJ = rpcclient/rpcclient.o \
             rpcclient/display.o \
             rpcclient/cmd_lsarpc.o \
             rpcclient/cmd_wkssvc.o \
             rpcclient/cmd_samr.o \
             rpcclient/cmd_reg.o \
             rpcclient/cmd_srvsvc.o \
             rpcclient/cmd_netlogon.o \
             $(PARAM_OBJ) $(LIBSMB_OBJ) $(UBIQX_OBJ) $(LIB_OBJ) \
             $(RPC_CLIENT_OBJ) $(RPC_PARSE_OBJ) $(PASSDB_OBJ)

SMBWRAPPER_OBJ = smbwrapper/smbw.o smbwrapper/wrapped.o \
		smbwrapper/smbw_dir.o smbwrapper/smbw_stat.o \
		smbwrapper/realcalls.o smbwrapper/shared.o \
		$(LIBSMB_OBJ) $(PARAM_OBJ) \
                $(UBIQX_OBJ) $(LIB_OBJ)

CLIENT_OBJ = client/client.o client/clitar.o \
             $(PARAM_OBJ) $(LIBSMB_OBJ) $(UBIQX_OBJ) $(LIB_OBJ)

CUPS_OBJ = client/smbspool.o $(PARAM_OBJ) $(LIBSMB_OBJ) $(UBIQX_OBJ) $(LIB_OBJ)

MOUNT_OBJ = client/smbmount.o \
             $(PARAM_OBJ) $(LIBSMB_OBJ) $(UBIQX_OBJ) $(LIB_OBJ)

MNT_OBJ = client/smbmnt.o \
             $(PARAM_OBJ) $(LIBSMB_OBJ) $(UBIQX_OBJ) $(LIB_OBJ)

UMOUNT_OBJ = client/smbumount.o \
             $(PARAM_OBJ) $(LIBSMB_OBJ) $(UBIQX_OBJ) $(LIB_OBJ)

NMBLOOKUP_OBJ = utils/nmblookup.o $(PARAM_OBJ) $(UBIQX_OBJ) \
                $(LIBSMB_OBJ) $(LIB_OBJ)

SMBTORTURE_OBJ = utils/torture.o utils/nbio.o $(LIBSMB_OBJ) $(PARAM_OBJ) \
                 $(UBIQX_OBJ) $(LIB_OBJ)

MASKTEST_OBJ = utils/masktest.o $(LIBSMB_OBJ) $(PARAM_OBJ) \
                 $(UBIQX_OBJ) $(LIB_OBJ)

RPCTORTURE_OBJ = utils/rpctorture.o \
             rpcclient/display.o \
             rpcclient/cmd_lsarpc.o \
             rpcclient/cmd_wkssvc.o \
             rpcclient/cmd_samr.o \
             rpcclient/cmd_srvsvc.o \
             rpcclient/cmd_netlogon.o \
             $(PARAM_OBJ) $(LIBSMB_OBJ) $(UBIQX_OBJ) $(LIB_OBJ) \
             $(RPC_CLIENT_OBJ) $(RPC_PARSE_OBJ) $(PASSDB_OBJ)

DEBUG2HTML_OBJ = utils/debug2html.o ubiqx/debugparse.o

SMBFILTER_OBJ = utils/smbfilter.o $(LIBSMB_OBJ) $(PARAM_OBJ) \
                 $(UBIQX_OBJ) $(LIB_OBJ)

PROTO_OBJ = $(SMBD_OBJ) $(NMBD_OBJ) $(SWAT_OBJ) $(CLIENT_OBJ) \
	    $(RPCCLIENT_OBJ) $(SMBWRAPPER_OBJ) $(SMBTORTURE_OBJ)

PICOBJS = $(SMBWRAPPER_OBJ:.o=.a)
PICOBJS32 = $(SMBWRAPPER_OBJ:.o=.a32)

######################################################################
# now the rules...
######################################################################

all : CHECK $(SPROGS) $(PROGS) 

romfs:
	$(ROMFSINST) -e CONFIG_USER_SAMBA /etc/default/smb.conf
	$(ROMFSINST) -e CONFIG_USER_SAMBA_NMBD bin/nmbd /bin/nmbd
	$(ROMFSINST) -e CONFIG_USER_SAMBA_SMBD bin/smbd /bin/smbd
	$(ROMFSINST) -e CONFIG_USER_SAMBA_SMBMOUNT bin/smbmnt /bin/smbmnt
	$(ROMFSINST) -e CONFIG_USER_SAMBA_SMBMOUNT bin/smbmount /bin/smbmount
	$(ROMFSINST) -e CONFIG_USER_SAMBA_SMBUMOUNT bin/smbumount /bin/smbumount

smbwrapper : CHECK bin/smbsh bin/smbwrapper.so 

smbtorture : CHECK bin/smbtorture

masktest : CHECK bin/masktest

rpctorture : CHECK bin/rpctorture

debug2html : CHECK bin/debug2html

smbfilter : CHECK bin/smbfilter

.SUFFIXES:
.SUFFIXES: .c .o .a .a32

CHECK:
	@echo "Using FLAGS = $(FLAGS)"
	@echo "Using FLAGS32 = $(FLAGS32)"
	@echo "Using LIBS = $(LIBS)"

MAKEDIR = || exec false; \
	  if test -d "$$dir"; then :; else \
	  echo mkdir "$$dir"; \
	  mkdir -p "$$dir" >/dev/null 2>&1 || \
	  test -d "$$dir" || \
	  mkdir "$$dir" || \
	  exec false; fi || exec false

# the lines below containing `#' are for atomatic dependency tracking
# they will only work with GNU make, gcc and --enable-maintainer-mode
# without --enable-maintainer-mode, they do nothing
.c.o: # .deps/.dummy
	@if (: >> $@ || : > $@) >/dev/null 2>&1; then rm -f $@; else \
	 dir=`echo $@ | sed 's,/[^/]*$$,,;s,^$$,.,'` $(MAKEDIR); fi
#	@if (: >> .deps/$@ || : > .deps/$@) >/dev/null 2>&1; then :; \
#	 else dir=.deps/`echo $@ | sed 's,/[^/]*$$,,;s,^$$,.,'` \
#	      $(MAKEDIR); fi; rm -f .deps/$@ .deps/$@d
	@echo Compiling $*.c
	@$(CC) -I. -I$(srcdir) $(FLAGS) -c $< \
	  -o $@ # -Wp,-MD,.deps/$@
#	-mv `echo $@ | sed 's%^.*/%%g'` $@
#	@sed 's|^'`echo $@ | sed 's,.*/,,'`':|$@:|' \
#	  <.deps/$@ >.deps/$@d && \
#	rm -f .deps/$@ && : >.deps/.stamp

.c.a: # .deps/.dummy
	@if (: >> $@ || : > $@) >/dev/null 2>&1; then rm -f $@; else \
	  dir=`echo $@ | sed 's,/[^/]*$$,,;s,^$$,.,'` $(MAKEDIR); fi
#	@if (: >> .deps/$@ || : > .deps/$@) >/dev/null 2>&1; then :; \
#	 else dir=.deps/`echo $@ | sed 's,/[^/]*$$,,;s,^$$,.,'` \
#	      $(MAKEDIR); fi; rm -f .deps/$@ .deps/$@d
	@echo Compiling $*.c with -fpic
	@$(CC) -I. -I$(srcdir) $(FLAGS) -fpic -c $< \
	  -o $*.a.o # -Wp,-MD,.deps/$@
#	-mv `echo $@ | sed -e 's%^.*/%%g' -e 's%\.a$$%.o%'` $@.o
#	@sed 's|^'`echo $*\.a\.o | sed 's,.*/,,'`':|$@:|' \
#	  <.deps/$@ >.deps/$@d && \
#	rm -f .deps/$@ && : >.deps/.stamp
	@mv $*.a.o $@

# this is for IRIX
.c.a32: # .deps/.dummy
	@if (: >> $@ || : > $@) >/dev/null 2>&1; then rm -f $@; else \
	  dir=`echo $@ | sed 's,/[^/]*$$,,;s,^$$,.,'` $(MAKEDIR); fi
#	@if (: >> .deps/$@ || : > .deps/$@) >/dev/null 2>&1; then :; \
#	 else dir=.deps/`echo $@ | sed 's,/[^/]*$$,,;s,^$$,.,'` \
#	      $(MAKEDIR); fi; rm -f .deps/$@ .deps/$@d
	@echo Compiling $*.c with -fpic and -32
	@$(CC) -32 -I. -I$(srcdir) $(FLAGS32) -fpic -c $< \
	  -o $*.a32.o # -Wp,-MD,.deps/$@
#	-mv `echo $@ | sed -e 's%^.*/%%g' -e 's%\.a32$$%.o%'` $@.o
#	@sed 's|^'`echo $*.a32.o | sed 's,.*/,,'`':|$@:|' \
#	  <.deps/$@ >.deps/$@d && \
#	rm -f .deps/$@ && : >.deps/.stamp
	@mv $*.a32.o $@

bin/.dummy:
	@if (: >> $@ || : > $@) >/dev/null 2>&1; then :; else \
	  dir=bin $(MAKEDIR); fi
	@: >> $@ || : > $@ # what a fancy emoticon!

bin/smbd: $(SMBD_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(SMBD_OBJ) $(LIBS) $(LDLIBS)

bin/nmbd: $(NMBD_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(NMBD_OBJ) $(LIBS) $(LDLIBS)

bin/swat: $(SWAT_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(SWAT_OBJ) $(LIBS) $(LDLIBS)

bin/smbrun: $(SMBRUN_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(SMBRUN_OBJ) $(LIBS) $(LDLIBS)

bin/rpcclient: $(RPCCLIENT_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(RPCCLIENT_OBJ) $(LIBS) $(LDLIBS)

bin/smbclient: $(CLIENT_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(CLIENT_OBJ) $(LIBS) $(LDLIBS)

bin/smbspool: $(CUPS_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(CUPS_OBJ) $(LIBS) $(LDLIBS)

bin/smbmount: $(MOUNT_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(MOUNT_OBJ) $(LIBS) $(LDLIBS)

bin/smbmnt: $(MNT_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(MNT_OBJ) $(LIBS) $(LDLIBS)

bin/smbumount: $(UMOUNT_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(UMOUNT_OBJ) $(LIBS) $(LDLIBS)

bin/testparm: $(TESTPARM_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(TESTPARM_OBJ) $(LIBS) $(LDLIBS)

bin/testprns: $(TESTPRNS_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(TESTPRNS_OBJ) $(LIBS) $(LDLIBS)

bin/smbstatus: $(STATUS_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(STATUS_OBJ) $(LIBS) $(LDLIBS)

bin/smbpasswd: $(SMBPASSWD_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(SMBPASSWD_OBJ) $(LIBS) $(LDLIBS)

bin/make_smbcodepage: $(MAKE_SMBCODEPAGE_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(MAKE_SMBCODEPAGE_OBJ) $(LIBS) $(LDLIBS)

bin/make_unicodemap: $(MAKE_UNICODEMAP_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(MAKE_UNICODEMAP_OBJ) $(LIBS) $(LDLIBS)

bin/nmblookup: $(NMBLOOKUP_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(NMBLOOKUP_OBJ) $(LIBS) $(LDLIBS)

bin/make_printerdef: $(MAKE_PRINTERDEF_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(MAKE_PRINTERDEF_OBJ) $(LIBS) $(LDLIBS)

bin/smbtorture: $(SMBTORTURE_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(SMBTORTURE_OBJ) $(LIBS) $(LDLIBS)

bin/masktest: $(MASKTEST_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(MASKTEST_OBJ) $(LIBS) $(LDLIBS)

bin/rpctorture: $(RPCTORTURE_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(RPCTORTURE_OBJ) $(LIBS) $(LDLIBS)

bin/debug2html: $(DEBUG2HTML_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(DEBUG2HTML_OBJ) $(LIBS) $(LDLIBS)

bin/smbfilter: $(SMBFILTER_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(SMBFILTER_OBJ) $(LIBS) $(LDLIBS)

bin/smbwrapper.a: $(PICOBJS)
	@echo Linking shared library $@
	@$(CC) -shared -o $@ $(PICOBJS) $(LIBS) $(LDLIBS)

bin/smbwrapper.32.a: $(PICOBJS32)
	@echo Linking library $@
	@$(CC) -32 -shared -o $@ $(PICOBJS32) $(LIBS) $(LDLIBS)

bin/smbsh: $(SMBSH_OBJ) bin/.dummy
	@echo Linking $@
	@$(CC) $(LDFLAGS) $(LFLAGS) -o $@ $(SMBSH_OBJ) $(LIBS) $(LDLIBS)

install: installbin installman installscripts installcp installswat

installdirs:
	$(SHELL) $(srcdir)/install-sh -d -m $(INSTALLPERMS) \
	$(BASEDIR) $(SBINDIR) $(BINDIR) $(LIBDIR) $(VARDIR) $(CODEPAGEDIR)

installservers: all installdirs
	@$(SHELL) $(srcdir)/script/installbin.sh $(INSTALLPERMS) $(BASEDIR) $(SBINDIR) $(LIBDIR) $(VARDIR) $(SPROGS)

installbin: all installdirs
	@$(SHELL) $(srcdir)/script/installbin.sh $(INSTALLPERMS) $(BASEDIR) $(SBINDIR) $(LIBDIR) $(VARDIR) $(SPROGS)
	@$(SHELL) $(srcdir)/script/installbin.sh $(INSTALLPERMS) $(BASEDIR) $(BINDIR) $(LIBDIR) $(VARDIR) $(PROGS)

installscripts: installdirs
	@$(SHELL) $(srcdir)/script/installscripts.sh $(INSTALLPERMS) $(BINDIR) $(SCRIPTS)

installcp: installdirs
	@$(SHELL) $(srcdir)/script/installcp.sh $(srcdir) $(LIBDIR) $(CODEPAGEDIR) $(BINDIR) $(CODEPAGELIST)

installswat: installdirs
	@$(SHELL) $(srcdir)/script/installswat.sh $(SWATDIR) $(srcdir) $(SAMBABOOK)

# revert to the previously installed version
revert:
	@$(SHELL) $(srcdir)/script/revert.sh $(SBINDIR) $(SPROGS) 
	@$(SHELL) $(srcdir)/script/revert.sh $(BINDIR) $(PROGS) $(SCRIPTS)

installman:
	@$(SHELL) $(srcdir)/script/installman.sh $(MANDIR) $(srcdir) ""

uninstall: uninstallman uninstallbin uninstallscripts uninstallcp

uninstallman:
	@$(SHELL) $(srcdir)/script/uninstallman.sh $(MANDIR) $(srcdir)

uninstallbin:
	@$(SHELL) $(srcdir)/script/uninstallbin.sh $(INSTALLPERMS) $(BASEDIR) $(SBINDIR) $(LIBDIR) $(VARDIR) $(SPROGS)
	@$(SHELL) $(srcdir)/script/uninstallbin.sh $(INSTALLPERMS) $(BASEDIR) $(BINDIR) $(LIBDIR) $(VARDIR) $(PROGS)

uninstallscripts:
	@$(SHELL) $(srcdir)/script/uninstallscripts.sh $(INSTALLPERMS) $(BINDIR) $(SCRIPTS)

uninstallcp:
	@$(SHELL) $(srcdir)/script/uninstallcp.sh $(CODEPAGEDIR) $(CODEPAGELIST)

clean: 
	-rm -f core */*~ *~ */*.o */*.a */*.a32 */*.so

proto: 
	@echo rebuilding include/proto.h
	@cd $(srcdir) && $(AWK) -f script/mkproto.awk `echo $(PROTO_OBJ) | tr ' ' '\n' | sed -e 's/\.o/\.c/g' | sort -u | egrep -v 'ubiqx/|wrapped'` > include/proto.h

etags:
	etags `find . -name "*.[ch]" | grep -v /CVS/`

ctags:
	ctags `find . -name "*.[ch]" | grep -v /CVS/`

realclean: clean
	-rm -f config.log $(PROGS) $(SPROGS) bin/.dummy
	-rmdir bin

distclean: realclean
	-rm -f include/config.h include/stamp-h Makefile
	-rm -f config.status config.cache so_locations
	-rm -rf .deps

#
# This target is for documenation updators. It regenerates
# the man pages and HTML docs from the YODL source files.
# In order for this target to work YODL must be installed
# and working on your system. JRA.
yodldocs:
	@$(SHELL) $(srcdir)/script/makeyodldocs.sh $(srcdir)

# this target is really just for my use. It only works on a limited
# range of machines and is used to produce a list of potentially
# dead (ie. unused) functions in the code. (tridge)
finddead:
	nm */*.o |grep 'U ' | awk '{print $$2}' | sort -u > nmused.txt
	nm */*.o |grep 'T ' | awk '{print $$3}' | sort -u > nmfns.txt
	comm -13 nmused.txt nmfns.txt 

# Rules for maintainers (--enable-maintainer-mode)
AUTOCONF=/usr/bin/autoconf
AUTOHEADER=/usr/bin/autoheader

# when configure.in is updated, reconfigure
$(srcdir)/configure: # $(srcdir)/configure.in $(srcdir)/aclocal.m4
	cd $(srcdir) && $(AUTOCONF)

config.status: $(srcdir)/configure
	$(SHELL) ./config.status --recheck

# Makefile: $(srcdir)/Makefile.in config.status \
# 	  include/stamp-h # just to ensure that config.h is up-to-date
# 	CONFIG_FILES=$@ CONFIG_HEADERS= $(SHELL) ./config.status

# note that nothing depends on config.h, so will probably be rebuilt
# only when explicitly requested, unless dependency tracking is enabled
include/config.h: include/stamp-h
	@:

include/stamp-h: $(srcdir)/include/config.h.in config.status
	CONFIG_FILES= CONFIG_HEADERS=include/config.h $(SHELL) ./config.status
	@echo > include/stamp-h

$(srcdir)/include/config.h.in: $(srcdir)/include/stamp-h.in
	@:

$(srcdir)/include/stamp-h.in: # $(srcdir)/acconfig.h $(srcdir)/configure.in
	cd $(srcdir) && $(AUTOHEADER)
	@date -u > $@

# automatic dependency tracking rules
.deps/.dummy:
	@if (: >> $@ || : > $@) >/dev/null 2>&1; then :; else \
	  dir=.deps $(MAKEDIR); fi
	@: >> $@ || : > $@ # what a fancy emoticon!

.deps/.stamp: .deps/.dummy
	@: >> $@ || : > $@

.deps/depend: .deps/.stamp
	@echo Updating dependencies
	@: | cat `find .deps -type f -name \*d` >$@ 2>/dev/null || true

#-include .deps/depend
