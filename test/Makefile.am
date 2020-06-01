MAINTAINERCLEANFILES = Makefile.in

SUBDIRS =

AUTOMAKE_OPTIONS = no-dependencies

noinst_PROGRAMS= benchmark

#Tests
check_PROGRAMS= bbitmap_test list_test map_test set_test str_test combined_test stack_test
TESTS = bbitmap_test list_test map_test set_test str_test combined_test stack_test

bbitmap_test_SOURCES= bbitmap_test.c
bbitmap_test_CPPFLAGS= -I$(top_srcdir)/include/
bbitmap_test_LDADD= -lpthread ../src/libcdada.la

list_test_SOURCES= list_test.c list_custom.cc
list_test_CPPFLAGS= -I$(top_srcdir)/include/
list_test_LDADD= -lpthread ../src/libcdada.la

map_test_SOURCES= map_test.c map_custom.cc
map_test_CPPFLAGS= -I$(top_srcdir)/include/
map_test_LDADD= -lpthread ../src/libcdada.la

set_test_SOURCES= set_test.c set_custom.cc
set_test_CPPFLAGS= -I$(top_srcdir)/include/
set_test_LDADD= -lpthread ../src/libcdada.la

combined_test_SOURCES= combined_test.c combined_custom.cc
combined_test_CPPFLAGS= -I$(top_srcdir)/include/
combined_test_LDADD= -lpthread ../src/libcdada.la

str_test_SOURCES= str_test.c
str_test_CPPFLAGS= -I$(top_srcdir)/include/
str_test_LDADD= -lpthread ../src/libcdada.la

stack_test_SOURCES= stack_test.c stack_custom.cc
stack_test_CPPFLAGS= -I$(top_srcdir)/include/
stack_test_LDADD= -lpthread ../src/libcdada.la

benchmark_SOURCES= benchmark.cc
benchmark_CXXFLAGS= -O3
benchmark_CPPFLAGS= -I$(top_srcdir)/include/
benchmark_LDADD= -lpthread ../src/.libs/libcdada.a

#Valgrind
if VALGRIND_ENABLED
TESTS_ENVIRONMENT=valgrind --quiet --trace-children=yes --error-exitcode=1 \
				--dsymutil=yes --leak-check=yes \
				--leak-check-heuristics=all \
				--suppressions=$(top_srcdir)/test/locale.supp
endif
