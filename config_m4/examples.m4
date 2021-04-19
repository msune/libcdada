WITH_EXAMPLES_DEFAULT=yes
AC_MSG_CHECKING([whether to compile examples])
AC_ARG_WITH(examples,
		AS_HELP_STRING([--without-examples], [Do not build examples [default=with]]),
			[WITH_EXAMPLES="$withval"],
			[WITH_EXAMPLES="$WITH_EXAMPLES_DEFAULT"]
)

if test x"$WITH_EXAMPLES" = x"yes"; then
	AC_MSG_RESULT(yes)
else
	AC_MSG_RESULT(no)
fi

AM_CONDITIONAL([WITH_EXAMPLES], [test "x$WITH_EXAMPLES" = "xyes"])
