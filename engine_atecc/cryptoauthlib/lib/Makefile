CWD:=$(shell pwd)
SRC:=$(wildcard *.c)

DIRECTORIES=$(shell find . -maxdepth 1 ! -path . -type d)
SUBDIRS=$(DIRECTORIES)

.PHONY:	clean

MODULES=$(patsubst %.c,%.o,$(SRC))
#O_FILES=$(shell find . -name \*.o)
O_FILES=$(wildcard **/**/*.o)
O_FILES+=$(wildcard **/*.o)
LIBNAME=libcryptoauth

all:	$(MODULES)
	- $(foreach subdir,$(basename $(SUBDIRS)),$(shell make -w -C $(subdir)))
	@echo "OFILES: $(O_FILES)"
	$(AR) -r $(LIBNAME).a $(MODULES) $(O_FILES)
	$(RANLIB) $(LIBNAME).a

.PHONY: install
install: $(LIBNAME).a
	install -d $(DESTDIR)/usr/lib/
	install -m 0644 $(LIBNAME).a $(DESTDIR)/usr/lib/

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o *.a
	$(foreach subdir,$(basename $(SUBDIRS)),$(MAKE) -w -C $(subdir) clean;)

