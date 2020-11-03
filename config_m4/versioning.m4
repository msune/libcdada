# Set application version based on the git version

#Default
CDADA_VERSION="$PACKAGE_VERSION" #Unknown (no GIT repository detected)"
FILE_VERSION=`cat $srcdir/VERSION`

AC_CHECK_PROG(ff_git,git,yes,no)

#Normalize
CDADA_VERSION_NORMALIZED=`echo $CDADA_VERSION | sed s/dev//g | sed s/RC.*//g | tr -d v`

#Substs
AC_SUBST([CDADA_VERSION], ["$CDADA_VERSION"])
AC_SUBST([CDADA_VERSION_NORMALIZED], ["$CDADA_VERSION_NORMALIZED"])

AC_MSG_CHECKING([the build version])
AC_MSG_RESULT([$CDADA_VERSION ($CDADA_VERSION_NORMALIZED)])

AC_MSG_CHECKING([the build number])
if test $ff_git = no
then
	AC_MSG_RESULT([git not found!])
else

	if test -d $srcdir/.git ; then
		#Try to retrieve the build number
		_CDADA_GIT_BUILD=`git log -1 --pretty=%H`
		_CDADA_GIT_BRANCH=`git rev-parse --abbrev-ref HEAD`
		_CDADA_GIT_DESCRIBE=`git describe --abbrev=40`

		AC_SUBST([CDADA_BUILD], ["$_CDADA_GIT_BUILD"])
		AC_SUBST([CDADA_BRANCH], ["$_CDADA_GIT_BRANCH"])
		AC_SUBST([CDADA_DESCRIBE], ["$_CDADA_GIT_DESCRIBE"])

	fi

	AC_MSG_RESULT([$_CDADA_GIT_BUILD])
fi

#File version always exists
CDADA_VERSION_MAJOR=`echo $CDADA_VERSION | awk -F "." '{ print $1 }' | sed 's/v//'`
CDADA_VERSION_MINOR=`echo $CDADA_VERSION | awk -F "." '{ print $2 }'`
CDADA_VERSION_PATCH=`echo $CDADA_VERSION | awk -F "." '{ print $3 }'`
AC_SUBST(CDADA_VERSION_MAJOR)
AC_SUBST(CDADA_VERSION_MINOR)
AC_SUBST(CDADA_VERSION_PATCH)
