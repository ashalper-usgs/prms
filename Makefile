# U.S. Geological Survey
#
# File - Makefile
#
# Purpose - Top-level Makefile for PRMS.
#
# Author - Andrew Halper
#

all: prms

prms: Args Control Globals Space prms.chpl
	chpl $@.chpl -o main

Args: Globals Args.chpl
	chpl $@.chpl

Globals: PRMSList Globals.chpl
	chpl $@.chpl

Space:	Globals PRMSList Space.chpl
	chpl $@.chpl

# circular dependencies here

Control: Dimension Globals PRMSList Control.chpl
	chpl $@.chpl

PRMSList: Globals Control PRMSList.chpl
	chpl $@.chpl

Dimension: %: %.chpl
	chpl $<

clean:
	rm -f Args Control Dimension Globals PRMSList Space main *~
