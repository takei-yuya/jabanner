#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([jabanner], [0.1.1], [takei.yuya _at_ gmail.com])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/jabanner.cc])
AC_CONFIG_HEADERS([config.h])

# Argument
AC_ARG_ENABLE(ncurses,[  --disable-ncurses       do not use ncurses])
AC_ARG_ENABLE(font,[  --enable-font=file      default font[=auto ditect]])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB(gd,gdImageStringTTF,,AC_MSG_ERROR(Test for libgd failed.))
if test "$enable_ncurses" != "no"; then
	AC_CHECK_LIB(ncurses,initscr,,AC_MSG_WARN(Test for libncurses failed.))
fi


# Checks for header files.
# AC_HEADER_STDC([foreign])
AC_CHECK_HEADERS([fcntl.h libintl.h stdlib.h string.h sys/ioctl.h termios.h unistd.h])

# Checks for fonts.
AC_MSG_CHECKING(font)
test -z "${enable_font}" && enable_font="`./find_font.sh`"
if test -n "$enable_font" ; then
	# Set AC_ALL to handle UTF-8 filename
	LC_ALL=ja_JP.UTF-8

	AC_MSG_RESULT($enable_font)
	AC_DEFINE_UNQUOTED(DEFAULT_FONT,[((char *)"$enable_font")], [Default font])
else
	AC_MSG_RESULT(no)
	AC_MSG_ERROR(font missing)
fi

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([dup2 setlocale])

AC_CONFIG_FILES([Makefile src/Makefile
                 docker-centos6/Dockerfile
                 docker-centos7/Dockerfile
                 ])
AC_OUTPUT
