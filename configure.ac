m4_include([VERSION]) #Force reconf on VERSION change
AC_INIT(LIBCDADA, m4_esyscmd_s(cat VERSION), marcdevel@gmail.com, libcdada, http://github.com/msune/libcdada)

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_GNU_SOURCE

AC_PROG_INSTALL
AC_PROG_CC
AC_PROG_CXX
AC_PROG_LD
AM_PROG_CC_C_O
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

PKG_PROG_PKG_CONFIG

AUTOCONF_ENV="SHELL=/bin/sh"

LT_INIT
AC_ENABLE_STATIC

# Some useful default flags
CFLAGS="-std=gnu89 -Werror -Wall $CFLAGS"
CXXFLAGS="-Werror -Wall $CXXFLAGS"
AC_DEFINE([__STDC_FORMAT_MACROS], [], [Description])

# Check for Python3
AM_PATH_PYTHON([3],, [:])
AM_CONDITIONAL([HAVE_PYTHON], [test "$PYTHON" != :])

# Debug
m4_include([config_m4/debug.m4])

# Check for profiling mode
m4_include([config_m4/profiling.m4])

# Checking version
m4_include([config_m4/versioning.m4])

# Checking valgrind
m4_include([config_m4/valgrind.m4])

# Checking RDTSC
m4_include([config_m4/rdtsc.m4])

# Tests
m4_include([config_m4/tests.m4])

# Examples
m4_include([config_m4/examples.m4])

# Output files
AC_CONFIG_FILES([
	Makefile
	include/Makefile
	examples/Makefile
	src/Makefile
	test/Makefile
	tools/Makefile
	include/cdada/version.h
])

AC_OUTPUT
