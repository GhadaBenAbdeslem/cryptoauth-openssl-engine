LIBNAME=        libunity
LIB=            $(LIBNAME).a
AR+=            r

include ../Makefile.generic

tgt_local:
	$(CC) -o unity.o -c unity.c
	$(AR) $(LIB) unity.o

ecc-test: tgt_local
	$(CC) -c ecc-test-main.c $(CFLAGS) -I. -I..
	$(CC) -o ecc-test-main ecc-test-main.o ../test/tls/atcatls_tests.o -Lcryptoauthlib/lib -leccx08_meth -lcryptoauth  -Lcryptoauthlib/test -lunity -lm -lc -lrt

install: ;
