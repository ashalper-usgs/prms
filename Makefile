# Makefile -- Top-level makefile for PRMS.

include ./makelist

all:
	cd lib && $(MAKE)
	cd src && $(MAKE)

clean:
	cd lib && $(MAKE) clean
	cd src && $(MAKE) clean
	rm -f *~
