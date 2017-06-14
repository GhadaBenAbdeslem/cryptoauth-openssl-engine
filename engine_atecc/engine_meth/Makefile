CFLAGS_EXT=
CWD:=		$(shell pwd)
#HW?= 		-DECC_DEBUG
HW?=		-DUSE_ECCX08 -DECC_DEBUG

CFLAGS+= -fPIC -g -O0 $(HW) -DATCA_HAL_I2C $(CFLAGS_EXT)

SRC=	$(wildcard *.c)

.PHONY:	clean

MODULES=	$(patsubst %.c,%.o,$(SRC))
LIBNAME=	libeccx08_meth

all:	$(MODULES) Makefile
	$(AR) $(LIBNAME).a $(MODULES)
	$(RANLIB) $(LIBNAME).a

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) -c $<

clean:
	rm -f *.o *.a
