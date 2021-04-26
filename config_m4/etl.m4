AC_MSG_CHECKING([for ETL git submodule presence])

if test -d $ac_abs_confdir/libs/etl/include/etl; then
	AC_MSG_RESULT(yes)
else
	AC_MSG_RESULT(no)
	AC_MSG_ERROR(ETL git submodule not found in libs/etl/. Did you run autogen.sh?)
fi

#Include libs/etl/include in the include path
CFLAGS="-I$ac_abs_confdir/libs/etl/include $CFLAGS"
CXXFLAGS="-I$ac_abs_confdir/libs/etl/include $CXXFLAGS"
