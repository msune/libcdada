AC_MSG_CHECKING(whether RDTSC support is available)
AC_LINK_IFELSE([
	AC_LANG_SOURCE(
		[[
			#include <stdio.h>
			int main(){
			unsigned int hi, lo;
			__asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
			printf("%u, %u\n", hi, lo);
			return 0;
			}
		]]
  	)
], [have_rdtsc=yes], [have_rdtsc=no])

if test "$have_rdtsc" = "yes"; then
	AC_DEFINE([HAVE_RDTSC], [], [Define if RDTSC support is detected.])
	AC_MSG_RESULT(yes)
else
	AC_MSG_RESULT(no)
fi
