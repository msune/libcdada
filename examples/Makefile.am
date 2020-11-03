MAINTAINERCLEANFILES = Makefile.in

noinst_PROGRAMS = bbitmap      \
                  list_u32     \
                  map_struct   \
                  custom_gen   \
                  custom_macro \
                  str          \
                  queue_u32    \
                  stack_u32

list_u32_SOURCES = list_u32.c
list_u32_CPPFLAGS = -I$(top_builddir)/include/ -I$(top_srcdir)/include/
list_u32_LDADD = ../src/.libs/libcdada.a -lstdc++

map_struct_SOURCES = map_struct.c
map_struct_CPPFLAGS = -I$(top_builddir)/include/ -I$(top_srcdir)/include/
map_struct_LDADD = ../src/.libs/libcdada.a -lstdc++

custom_gen_SOURCES = custom-gen/my_program_gen.c custom-gen/cdada.cc
custom_gen_CPPFLAGS = -I$(top_builddir)/include/ -I$(top_srcdir)/include/
custom_gen_LDADD = ../src/.libs/libcdada.a -lstdc++

custom_macro_SOURCES = custom-macro/my_program.c custom-macro/cdada.cc
custom_macro_CPPFLAGS = -I$(top_builddir)/include/ -I$(top_srcdir)/include/
custom_macro_LDADD = ../src/.libs/libcdada.a -lstdc++

str_SOURCES = str.c
str_CPPFLAGS = -I$(top_builddir)/include/ -I$(top_srcdir)/include/
str_LDADD = ../src/.libs/libcdada.a -lstdc++

bbitmap_SOURCES = bbitmap.c
bbitmap_CPPFLAGS = -I$(top_builddir)/include/ -I$(top_srcdir)/include/
bbitmap_LDADD = ../src/.libs/libcdada.a -lstdc++

queue_u32_SOURCES = queue_u32.c
queue_u32_CPPFLAGS = -I$(top_builddir)/include/ -I$(top_srcdir)/include/
queue_u32_LDADD = ../src/.libs/libcdada.a -lstdc++

stack_u32_SOURCES = stack_u32.c
stack_u32_CPPFLAGS = -I$(top_builddir)/include/ -I$(top_srcdir)/include/
stack_u32_LDADD = ../src/.libs/libcdada.a -lstdc++
