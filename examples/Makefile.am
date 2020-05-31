MAINTAINERCLEANFILES = Makefile.in

noinst_PROGRAMS = bbitmap list_u32 map_struct custom_gen custom_macro str

list_u32_SOURCES = list_u32.c
list_u32_CPPFLAGS = -I$(top_srcdir)/include/ -D__CDADA_INTERNAL_INCLUDE
list_u32_LDADD = ../src/.libs/libcdada.a -lstdc++

map_struct_SOURCES = map_struct.c
map_struct_CPPFLAGS = -I$(top_srcdir)/include/ -D__CDADA_INTERNAL_INCLUDE
map_struct_LDADD = ../src/.libs/libcdada.a -lstdc++

custom_gen_SOURCES = custom-gen/my_program_gen.c custom-gen/cdada.cc
custom_gen_CPPFLAGS = -I$(top_srcdir)/include/
custom_gen_LDADD = ../src/.libs/libcdada.a -lstdc++

custom_macro_SOURCES = custom-macro/my_program.c custom-macro/cdada.cc
custom_macro_CPPFLAGS = -I$(top_srcdir)/include/
custom_macro_LDADD = ../src/.libs/libcdada.a -lstdc++

str_SOURCES = str.c
str_CPPFLAGS = -I$(top_srcdir)/include/
str_LDADD = ../src/.libs/libcdada.a -lstdc++

bbitmap_SOURCES = bbitmap.c
bbitmap_CPPFLAGS = -I$(top_srcdir)/include/
bbitmap_LDADD = ../src/.libs/libcdada.a -lstdc++
