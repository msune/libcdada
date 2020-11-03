MAINTAINERCLEANFILES = Makefile.in

lib_LTLIBRARIES = libcdada.la

libcdada_la_SOURCES = bbitmap.cc \
                      list.cc    \
                      map.cc     \
                      queue.cc   \
                      set.cc     \
                      stack.cc   \
                      str.cc     \
                      utils.c
libcdada_la_CPPFLAGS = -I$(top_builddir)/include/ -I$(top_srcdir)/include/ -D__CDADA_INTERNAL_INCLUDE
libcdada_la_LIBADD =
