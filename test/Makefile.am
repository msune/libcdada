MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =

AUTOMAKE_OPTIONS = no-dependencies

#A test
map_test_SOURCES= map_test.c
map_test_CPPFLAGS= -I$(top_srcdir)/src/
map_test_LDADD= -lpthread ../src/libcdata.la

#Tests
check_PROGRAMS= map_test
TESTS = map_test

#Valgrind
if VALGRIND_ENABLED
TESTS_ENVIRONMENT=valgrind --quiet --trace-children=yes --error-exitcode=1 \
				--dsymutil=yes --leak-check=yes \
				--leak-check-heuristics=all \
				--suppressions=$(top_srcdir)/test/locale.supp
endif
