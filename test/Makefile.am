MAINTAINERCLEANFILES = Makefile.in
AUTOMAKE_OPTIONS = no-dependencies

#Code generation for cdada-gen

all: list_custom_gen map_custom_gen set_custom_gen stack_custom_gen
.PHONY : all

list_custom_gen:
	$(top_srcdir)/tools/cdada-gen list:test_u552_t list:test_u3552_t -o $(top_builddir)/test/list_custom_gen.cc_
	echo '#include "$(top_srcdir)/test/u552.h"' > $(top_builddir)/test/list_custom_gen.cc
	echo '#include "$(top_srcdir)/test/u3552.h"' >> $(top_builddir)/test/list_custom_gen.cc
	cat $(top_builddir)/test/list_custom_gen.cc_ >> $(top_builddir)/test/list_custom_gen.cc
map_custom_gen:
	$(top_srcdir)/tools/cdada-gen map:test_u552_t map:test_u3552_t -o $(top_builddir)/test/map_custom_gen.cc
set_custom_gen:
	$(top_srcdir)/tools/cdada-gen set:test_u552_t set:test_u3552_t -o $(top_builddir)/test/set_custom_gen.cc
stack_custom_gen:
	$(top_srcdir)/tools/cdada-gen stack:test_u552_t stack:test_u3552_t -o $(top_builddir)/test/stack_custom_gen.cc

#Benchmark is not installable
noinst_PROGRAMS= benchmark

#Tests
check_PROGRAMS= bbitmap_test  \
                list_test     \
                list_gen_test \
                map_test      \
                map_gen_test  \
                set_test      \
                set_gen_test  \
                stack_test    \
                stack_gen_test\
                str_test      \
                combined_test
TESTS = bbitmap_test    \
        list_test       \
        list_gen_test   \
        map_test        \
        map_gen_test    \
        set_test        \
        set_gen_test    \
        stack_test      \
        stack_gen_test  \
        str_test        \
        combined_test

bbitmap_test_SOURCES= bbitmap_test.c
bbitmap_test_CPPFLAGS= -I$(top_srcdir)/include/
bbitmap_test_LDADD= -lpthread ../src/libcdada.la

list_test_SOURCES= list_test.c list_custom.cc
list_test_CPPFLAGS= -I$(top_srcdir)/include/
list_test_LDADD= -lpthread ../src/libcdada.la

list_gen_test_SOURCES= list_test.c $(top_builddir)/test/list_custom_gen.cc
list_gen_test_CPPFLAGS= -I$(top_srcdir)/include/
list_gen_test_LDADD= -lpthread ../src/libcdada.la

map_test_SOURCES= map_test.c map_custom.cc
map_test_CPPFLAGS= -I$(top_srcdir)/include/
map_test_LDADD= -lpthread ../src/libcdada.la

map_gen_test_SOURCES= map_test.c map_custom_gen.cc
map_gen_test_CPPFLAGS= -I$(top_srcdir)/include/
map_gen_test_LDADD= -lpthread ../src/libcdada.la

set_test_SOURCES= set_test.c set_custom.cc
set_test_CPPFLAGS= -I$(top_srcdir)/include/
set_test_LDADD= -lpthread ../src/libcdada.la

set_gen_test_SOURCES= set_test.c set_custom_gen.cc
set_gen_test_CPPFLAGS= -I$(top_srcdir)/include/
set_gen_test_LDADD= -lpthread ../src/libcdada.la

stack_test_SOURCES= stack_test.c stack_custom.cc
stack_test_CPPFLAGS= -I$(top_srcdir)/include/
stack_test_LDADD= -lpthread ../src/libcdada.la

stack_gen_test_SOURCES= stack_test.c stack_custom_gen.cc
stack_gen_test_CPPFLAGS= -I$(top_srcdir)/include/
stack_gen_test_LDADD= -lpthread ../src/libcdada.la

combined_test_SOURCES= combined_test.c combined_custom.cc
combined_test_CPPFLAGS= -I$(top_srcdir)/include/
combined_test_LDADD= -lpthread ../src/libcdada.la

str_test_SOURCES= str_test.c
str_test_CPPFLAGS= -I$(top_srcdir)/include/
str_test_LDADD= -lpthread ../src/libcdada.la

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
