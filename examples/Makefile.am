MAINTAINERCLEANFILES = Makefile.in

noinst_PROGRAMS = list_u32 map_struct

list_u32_SOURCES = list_u32.c
list_u32_CPPFLAGS = -I$(top_srcdir)/include/ -D__CDATA_INTERNAL_INCLUDE
list_u32_LDADD = ../src/libcdata.la

map_struct_SOURCES = map_struct.c
map_struct_CPPFLAGS = -I$(top_srcdir)/include/ -D__CDATA_INTERNAL_INCLUDE
map_struct_LDADD = ../src/libcdata.la
