MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =

AUTOMAKE_OPTIONS = no-dependencies

#Tests
check_PROGRAMS= list_test map_test set_test
TESTS = list_test map_test set_test

list_test_SOURCES= list_test.c
list_test_CPPFLAGS= -I$(top_srcdir)/include/
list_test_LDADD= -lpthread ../src/libcdata.la

map_test_SOURCES= map_test.c
map_test_CPPFLAGS= -I$(top_srcdir)/include/
map_test_LDADD= -lpthread ../src/libcdata.la

set_test_SOURCES= set_test.c
set_test_CPPFLAGS= -I$(top_srcdir)/include/
set_test_LDADD= -lpthread ../src/libcdata.la

#Valgrind
if VALGRIND_ENABLED
TESTS_ENVIRONMENT=valgrind --quiet --trace-children=yes --error-exitcode=1 \
				--dsymutil=yes --leak-check=yes \
				--leak-check-heuristics=all \
				--suppressions=$(top_srcdir)/test/locale.supp
endif
