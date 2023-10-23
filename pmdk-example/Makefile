PMDK_ROOT=$(realpath ../pmdk)
CC = gcc 
CFLAGS = -g -I${PMDK_ROOT}/lib/include
LDLIBS=-lndctl -ldaxctl -lpthread

.PHONY: all
all: init bins

init:
	git submodule init
	git submodule update
	make -C ${PMDK_ROOT} -j`nproc`	
	make -C ${PMDK_ROOT} install prefix=${PMDK_ROOT}/lib
	
bin/test_pool: pool/pool.c ${PMDK_ROOT}/lib/lib/libpmemobj.a ${PMDK_ROOT}/lib/lib/libpmem2.a ${PMDK_ROOT}/lib/lib/libpmem.a
	mkdir  -p $(dir $@)
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^


.PHONY: bins
bins: bin/test_pool
