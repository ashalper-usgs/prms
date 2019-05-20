## Automake file for MMF library tests. Process this file with
## automake to produce Makefile.in

TESTS = alloc_space
check_PROGRAMS = alloc_space
alloc_space_SOURCES = ../alloc_space.c ../alloc_space.h
alloc_space_CFLAGS = @CHECK_CFLAGS@
alloc_space_LDADD = ../libmmf.a @CHECK_LIBS@
