# U.S. Geological Survey
#
# File - Makefile
#
# Purpose - Top-level Makefile for PRMS.
#
# Author - Andrew Halper
#

all: prms
	chpl *.chpl -o main

clean:
	rm -f Args Control Dimension Globals PRMSList Space Structs main *~
