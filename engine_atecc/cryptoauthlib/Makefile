CWD:=	$(shell pwd)
CFLAGS+= -I. -I../.. -fPIC -g -O0
SRC:=	$(wildcard *.c)
export CFLAGS

DIRECTORIES=	$(shell find . -maxdepth 1 ! -path . -type d)
SUBDIRS=	$(DIRECTORIES)

.PHONY:	tgt_lib tgt_test clean

MODULES=	$(patsubst %.c,%.o,$(SRC))

all:	tgt_lib tgt_test $(MODULES) 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

tgt_lib:
	make -w -C lib

tgt_test:
	make -w -C test

install:
	for a in $(SUBDIRS); do $(MAKE) -C $$a $@; done

clean:
	rm -f *.o *.a
	$(foreach subdir,$(basename $(SUBDIRS)),$(MAKE) -w -C $(subdir) clean;)
