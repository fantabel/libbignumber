CC=g++
CFLAGS=-c -Wall -std=c++0x -pedantic -I /opt/log4cxx/include
LNFLAGS=./lib/liblog4cxx.a
OUT = libnumber.a
OTEST = testsuite
CC = g++
ODIR = obj
SDIR = src
INC = -Iheaders

all: $(OUT)

# Components of the library.
library-objects = \
	BigUnsigned.o \
	BigInteger.o \
	BigIntegerAlgorithms.o \
	BigUnsignedInABase.o \
	BigIntegerUtils.o \

library-headers = \
	NumberlikeArray.hh \
	BigUnsigned.hh \
	BigInteger.hh \
	BigIntegerAlgorithms.hh \
	BigUnsignedInABase.hh \
	BigIntegerLibrary.hh \

_OBJS = $(library-objects)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.cc
	$(CC) -c $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS)
	ar rvs $(OUT) $(OBJS) $(LNFLAGS)
#	cp $(OUT) tests

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o $(OUT)
	rm -rf html latex
	make clean -C tests

.PHONY: tests
tests: libnumber.a
#	cp libnumber.a tests
	make -C tests
	tests/test_suite
