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

Globals: NHMList Globals.chpl
	chpl $@.chpl

Space:	Globals NHMList Space.chpl
	chpl $@.chpl

NHMList: Control NHMList.chpl
	chpl $@.chpl

Dimension Control: %: %.chpl
	chpl $<

clean:
	rm -f Args Control Dimension Globals NHMList Space main *~
