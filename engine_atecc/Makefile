CFLAGS_EXT=
LIBNAME=	libateccx08
SRC=		engine_atecc_binder.c
OBJ=		engine_atecc_binder.o 
HEADER=		ecc-crypto_openssl.h
HW?=		-DUSE_ECCX08 -DECC_DEBUG

PIC=		-fPIC
CFLAGS+=	-Iengine_meth -I $(TOP) -I ../../.. -I $(TOP)/include -I../../../include $(PIC) -DENGINE_DYNAMIC_SUPPORT -DATCA_HAL_I2C \
		-DFLAT_INC $(HW) $(CFLAGS_EXT)

LIB=		$(LIBNAME).a
SHLIB=		$(LIBNAME).so

export DESTDIR
export CFLAGS
export LDFLAGS

all: gnu

tgt_engine_meth:
	make -w -C engine_meth HW='$(HW)' CFLAGS_EXT='$(CFLAGS_EXT)'

clean:
	rm -f *.o *.a *.so* *.exp
	make -w -C engine_meth clean

install:
	install -d $(INSTALL_PREFIX)$(INSTALLTOP)/$(LIBDIR)/engines/
	install -m 555 $(SHLIB) $(INSTALL_PREFIX)$(INSTALLTOP)/$(LIBDIR)/engines/

FORCE.update:
update:		FORCE.update
		perl ../../../util/mkerr.pl -conf ecc-crypto.ec \
			-nostatic -staticloader -write ecc-crypto.c

gnu:		$(SHLIB).gnu  
tru64:		$(SHLIB).tru64
solaris:	$(SHLIB).solaris
irix:		$(SHLIB).irix
hpux32:		$(SHLIB).hpux32
hpux64:		$(SHLIB).hpux64
aix:		$(SHLIB).aix

$(LIB):		$(OBJ)
		$(AR) $(LIB) $(OBJ)
		- $(RANLIB) $(LIB)
LIBAMETH=engine_meth/libeccx08_meth.a

LINK_SO=	\
  $(LD) -r -o $(LIBNAME).o $$ALLSYMSFLAGS $(LIB) $(LIBAMETH) && \
  ($(NM) -Pg $(LIBNAME).o | grep ' [BDT] ' | cut -f1 -d' ' > $(LIBNAME).exp; \
   $$SHAREDCMD $$SHAREDFLAGS -o $(SHLIB) $(LIBNAME).o ../../crypto/ec/ec_ameth.o $(TARGET_LDFLAGS) -lc \
    -Lengine_meth -leccx08_meth -lcryptoauth -lm -lrt)

$(SHLIB).gnu:	$(LIB) tgt_engine_meth
		ALLSYMSFLAGS='--whole-archive' \
		SHAREDFLAGS='-shared -Wl,-soname=$(SHLIB)' \
		SHAREDCMD='$(CC)'; \
		$(LINK_SO)
		touch $(SHLIB).gnu
$(SHLIB).tru64:	$(LIB)
		A-Wl,-soname=engine_eccx08.so-Wl,-soname=engine_eccx08.so  LLSYMSFLAGS='-all' \
		SHAREDFLAGS='-shared' \
		SHAREDCMD='$(CC)'; \
		$(LINK_SO)
		touch $(SHLIB).tru64
$(SHLIB).solaris:	$(LIB)
		ALLSYMSFLAGS='-z allextract' \
		SHAREDFLAGS='-G -h $(SHLIB)' \
		SHAREDCMD='$(CC)'; \
		$(LINK_SO)
		touch $(SHLIB).solaris
$(SHLIB).irix:	$(LIB)
		ALLSYMSFLAGS='-all' \
		SHAREDFLAGS='-shared -Wl,-soname,$(SHLIB)' \
		SHAREDCMD='$(CC)'; \
		$(LINK_SO)
		touch $(SHLIB).irix
$(SHLIB).hpux32:	$(LIB)
		ALLSYMSFLAGS='-Fl' \
		SHAREDFLAGS='+vnocompatwarnings -b -z +s +h $(SHLIB)' \
		SHAREDCMD='/usr/ccs/bin/ld'; \
		$(LINK_SO)
		touch $(SHLIB).hpux32
$(SHLIB).hpux64:	$(LIB)
		ALLSYMSFLAGS='+forceload' \
		SHAREDFLAGS='-b -z +h $(SHLIB)' \
		SHAREDCMD='/usr/ccs/bin/ld'; \
		$(LINK_SO)
		touch $(SHLIB).hpux64
$(SHLIB).aix:	$(LIB)
		ALLSYMSFLAGS='-bnogc' \
		SHAREDFLAGS='-G -bE:$(LIBNAME).exp -bM:SRE' \
		SHAREDCMD='$(CC)'; \
		$(LINK_SO)
		touch $(SHLIB).aix

depend:
		sed -e '/^# DO NOT DELETE.*/,$$d' < Makefile > Makefile.tmp
		echo '# DO NOT DELETE THIS LINE -- make depend depends on it.' >> Makefile.tmp
		$(CC) -M $(CFLAGS) $(SRC) >> Makefile.tmp
		perl ../../util/clean-depend.pl < Makefile.tmp > Makefile.new
		rm -f Makefile.tmp Makefile
		mv Makefile.new Makefile

# DO NOT DELETE THIS LINE -- make depend depends on it.
