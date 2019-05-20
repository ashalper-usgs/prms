## Automake file for MMF library tests. Process this file with
## automake to produce Makefile.in

TESTS = alloc_space
check_PROGRAMS = alloc_space
alloc_space_SOURCES = $(top_builddir)/mmf/alloc_space.c $(top_builddir)/mmf/mms.h
alloc_space_CFLAGS = @CHECK_CFLAGS@
alloc_space_LDADD = $(top_builddir)/mmf/libmmf.a @CHECK_LIBS@
