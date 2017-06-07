#
# Makefile
#

#
# Support for submodule repository operations including:
# init, build, clean, dclean, install
#

CWD:=		$(shell pwd)
UNAME_S:= 	$(shell uname -s)
ARCH:= 		$(shell arch)
#HW= 		-DECC_DEBUG
#HW=		-DUSE_SLOT2_FOR_CERT -DUSE_ECCX08 -DECC_DEBUG
HW=		-DUSE_ECCX08 -DECC_DEBUG
CFLAGS_EXT=	

export DESTDIR
export CFLAGS
export LDFLAGS

.PHONY:	tgt_engine_atecc \
	build_engine_atecc clean_engine_atecc install_engine_atecc \
	tgt_tlsdemo clean_tlsdemo 

all:	build_engine_atecc tgt_tlsdemo

clean:	clean_engine_atecc clean_tlsdemo
install: install_engine_atecc

# ENGINE_ATECC
build_engine_atecc:
	make -w -C engine_atecc HW='$(HW)' CFLAGS_EXT='$(CFLAGS_EXT)' gnu

clean_engine_atecc:
	make -w -C engine_atecc clean

install_engine_atecc: build_engine_atecc
	make -w -C engine_atecc install

# TLS demo client/server
tgt_tlsdemo: build_engine_atecc
	make -w -C client-server HW='$(HW)'

clean_tlsdemo:
	make -w -C client-server clean

