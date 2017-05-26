CWD:=	$(shell pwd)
CFLAGS+= -I. -I../.. -fPIC -g -O0
SRC:=	$(wildcard *.c)
export CFLAGS

DIRECTORIES=	$(shell find . -maxdepth 1 ! -path . -type d)
SUBDIRS=	$(DIRECTORIES)

.PHONY:	tgt_lib tgt_test clean

all:	tgt_lib tgt_test ecc-test

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

tgt_lib:
	make -w -C lib

tgt_test:
	make -w -C test

ecc-test: tgt_lib tgt_test
	$(CC) -c ecc-test-main.c $(CFLAGS) $(LDFLAGS) -I ./lib/ -I ./test/
	$(CC) -o ecc-test-main ecc-test-main.o $(LDFLAGS) test/tls/atcatls_tests.o -L lib -L test -lm -lc -lrt -lcryptoauth -lunity

install:
	for a in $(SUBDIRS); do $(MAKE) -C $$a $@; done
	install -d $(DESTDIR)/usr/bin
	install -m 0755 ecc-test-main $(DESTDIR)/usr/bin/

clean:
	rm -f *.o *.a
	$(foreach subdir,$(basename $(SUBDIRS)),$(MAKE) -w -C $(subdir) clean;)
