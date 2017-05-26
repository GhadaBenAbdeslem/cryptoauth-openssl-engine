LIBNAME=        libunity
LIB=            $(LIBNAME).a
AR+=            r

include ../Makefile.generic

tgt_local:
	$(CC) -o unity.o -c unity.c
	$(AR) $(LIB) unity.o

install: ;
