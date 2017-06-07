CFLAGS_EXT=
CWD:=		$(shell pwd)
#HW?= 		-DECC_DEBUG
HW?=		-DUSE_ECCX08 -DECC_DEBUG

CFLAGS= -I. -I.. -I../.. \
	-I../cryptoauthlib/lib \
	-I../cryptoauthlib/lib/tls \
	-fPIC -g -O0 $(HW) $(CFLAGS_EXT)

SRC=	$(wildcard *.c)

.PHONY:	clean

MODULES=	$(patsubst %.c,%.o,$(SRC))
LIBNAME=	libeccx08_meth

all:	$(MODULES) Makefile
	$(AR) -r $(LIBNAME).a $(MODULES)
	$(RANLIB) $(LIBNAME).a

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) -c $<

clean:
	rm -f *.o *.a
