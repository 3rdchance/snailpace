PMDK_ROOT=$(realpath ../pmdk)
OBJCPP_ROOT=$(realapth ../libpmemobj-cpp)
CC = gcc 
CXX = g++
CFLAGS = -g -I${PMDK_ROOT}/lib/include
LDLIBS=-lndctl -ldaxctl -lpthread
CXXFLAGS = -I${OBJCPP_ROOT}/include

.PHONY: all
all: init bins

.PHONY: bins
bins: bin/test_pool bin/test_pool_cpp

init:
	git submodule init
	git submodule update
	make -C ${PMDK_ROOT} -j`nproc`	
	make -C ${PMDK_ROOT} install prefix=${PMDK_ROOT}/lib
	
bin/test_pool: pool/pool.c ${PMDK_ROOT}/lib/lib/libpmemobj.a ${PMDK_ROOT}/lib/lib/libpmem2.a ${PMDK_ROOT}/lib/lib/libpmem.a
	mkdir  -p $(dir $@)
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $^


bin/test_pool_cpp: pool/pool.cpp ${PMDK_ROOT}/lib/lib/libpmemobj.a ${PMDK_ROOT}/lib/lib/libpmem2.a ${PMDK_ROOT}/lib/lib/libpmem.a
	mkdir  -p $(dir $@)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LDLIBS) -o $@ $^
