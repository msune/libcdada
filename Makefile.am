MAINTAINERCLEANFILES = \
	$(top_srcdir)/aclocal.m4 \
	$(top_srcdir)/configure \
	$(top_srcdir)/Makefile.in

SUBDIRS = src test

#Could be improved..
.PHONY: doc
doc:
	@cd doc/ && make doc

install-exec-hook:

uninstall-hook:

maintainer-clean-local:
	rm -rf $(top_srcdir)/m4
	rm -rf $(top_srcdir)/build-aux
