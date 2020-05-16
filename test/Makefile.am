MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =

AUTOMAKE_OPTIONS = no-dependencies

#A test
test1_SOURCES= test1.c
test1_CPPFLAGS= -I$(top_srcdir)/src/
test1_LDADD= -lpthread

#Tests

check_PROGRAMS= test1
TESTS = test1
