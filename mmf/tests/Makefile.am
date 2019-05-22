## Automake file for MMF library tests. Process this file with
## automake to produce Makefile.in

TESTS = check_alloc_space
check_PROGRAMS = check_alloc_space
check_alloc_space_SOURCES = check_alloc_space.c ../alloc_space.h
check_alloc_space_CFLAGS = @CHECK_CFLAGS@
check_alloc_space_LDADD = ../libmmf.a @CHECK_LIBS@
