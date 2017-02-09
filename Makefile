#makefile for MIToolbox
#Author: Adam Pocock, apocock@cs.man.ac.uk
#Created 11/03/2010
#Updated 22/02/2014 - Added make install
#Updated 05/09/2016 - Repackaging
#
#
#Copyright 2010-2017 Adam Pocock, The University Of Manchester
#www.cs.manchester.ac.uk
#
#This file is part of MIToolbox, licensed under the 3-clause BSD license.

PREFIX = /usr/local
CFLAGS = -O3 -fPIC -std=c89 -pedantic -Wall -Werror
INCLUDES = -Iinclude
CC = gcc
objects = build/ArrayOperations.o build/CalculateProbability.o \
		  build/Entropy.o build/MutualInformation.o \
		  build/RenyiEntropy.o build/RenyiMutualInformation.o \
		  build/WeightedEntropy.o build/WeightedMutualInformation.o
          
libMIToolbox.so : $(objects)
	$(CC) $(CFLAGS) -shared -o libMIToolbox.so $(objects) -lm

build/%.o: src/%.c 
	@mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDES) -DCOMPILE_C -o build/$*.o -c $<
	
.PHONY : debug x86 x64 matlab matlab-debug intel install test
debug:
	$(MAKE) libMIToolbox.so "CFLAGS = -g -DDEBUG -fPIC"

x86:
	$(MAKE) libMIToolbox.so "CFLAGS = -O3 -fPIC -m32"
	
x64:
	$(MAKE) libMIToolbox.so "CFLAGS = -O3 -fPIC -m64"
	
intel:
	$(MAKE) libMIToolbox.so "CC = icc" "CFLAGS = -O2 -fPIC -xHost"

clean:
	-rm -fr build
	-rm -f matlab/*.o matlab/*.mex*
	-rm -f libMIToolbox.so

install: libMIToolbox.so
	@echo "Installing libMIToolbox.so to $(PREFIX)/lib"
	@cp -v libMIToolbox.so $(PREFIX)/lib
	@mkdir -p $(PREFIX)/include
	@echo "Installing MIToolbox's header files to $(PREFIX)/include/MIToolbox"
	@cp -rv include/MIToolbox $(PREFIX)/include/

test:
	$(CC) -std=c89 $(INCLUDES) -L. -o test.out test/testMIToolbox.c -lMIToolbox
