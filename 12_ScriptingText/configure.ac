AC_PREREQ([2.69])
AC_INIT([hashtext], [0.0], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_HEADERS([config.h])
AM_PATH_GLIB_2_0()


AC_PROG_CC
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

define(DATE, `date`)dnl
define(COM, [\/\* COMMENT:: AC_PACKAGE_NAME, AC_PACKAGE_VERSION: DATE \*\/])dnl
define(SEDSTR, [1 s/^\/\* COMMENT::.*\*\//COM/; t; 1 s/^/COM\n/;])dnl
define(SEDOPT, ["SEDSTR"])dnl

sed -i -s SEDOPT *.{c,h}
