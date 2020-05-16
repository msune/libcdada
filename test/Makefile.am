MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =

AUTOMAKE_OPTIONS = no-dependencies

#Tests
check_PROGRAMS= map_test set_test
TESTS = map_test set_test

map_test_SOURCES= map_test.c
map_test_CPPFLAGS= -I$(top_srcdir)/src/
map_test_LDADD= -lpthread ../src/libcdata.la

set_test_SOURCES= set_test.c
set_test_CPPFLAGS= -I$(top_srcdir)/src/
set_test_LDADD= -lpthread ../src/libcdata.la

#Valgrind
if VALGRIND_ENABLED
TESTS_ENVIRONMENT=valgrind --quiet --trace-children=yes --error-exitcode=1 \
				--dsymutil=yes --leak-check=yes \
				--leak-check-heuristics=all \
				--suppressions=$(top_srcdir)/test/locale.supp
endif
