WITH_TESTS_DEFAULT=yes
AC_MSG_CHECKING([whether to compile and run tests])
AC_ARG_WITH(tests,
		AS_HELP_STRING([--without-tests], [Do not build and run tests [default=with]]),
			[WITH_TESTS="$withval"],
			[WITH_TESTS="$WITH_TESTS_DEFAULT"]
)

if test x"$WITH_TESTS" = x"yes"; then
	AC_MSG_RESULT(yes)
else
	AC_MSG_RESULT(no)
fi

AM_CONDITIONAL([WITH_TESTS], [test "x$WITH_TESTS" = "xyes"])
