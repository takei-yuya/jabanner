#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(jabanner, 0.0.9, takei.yuya _at_ gmail.com)
AM_INIT_AUTOMAKE(jabanner, 0.0.9)
AC_CONFIG_SRCDIR(src/jabanner.cc)
AM_CONFIG_HEADER(config.h)

# Argument
AC_ARG_ENABLE(ncurses,[  --disable-ncurses       do not use ncurses])
AC_ARG_ENABLE(font,[  --enable-font=file      default font[=auto ditect]])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
AC_CHECK_LIB(gd,gdImageStringTTF,,AC_MSG_ERROR(Test for libgd failed.))
if test "$enable_ncurses" != "no"; then
	AC_CHECK_LIB(ncurses,initscr,,AC_MSG_WARN(Test for libncurses failed.))
fi


# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(stdlib.h string.h unistd.h libintl.h)

# Checks for fonts.
AC_MSG_CHECKING(font)
test -z "$enable_font" && enable_font=`find /share/fonts           -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | grep "[[^ -~]]" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /usr/share/fonts       -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | grep "[[^ -~]]" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /usr/local/share/fonts -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | grep "[[^ -~]]" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /Library/Fonts         -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | grep "[[^ -~]]" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /System/Library/Fonts  -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | grep "[[^ -~]]" 2>/dev/null | head -n 1 2>/dev/null`

test -z "$enable_font" && enable_font=`find /share/fonts           -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | grep -i "japan" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /usr/share/fonts       -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | grep -i "japan" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /usr/local/share/fonts -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | grep -i "japan" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /Library/Fonts         -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | grep -i "japan" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /System/Library/Fonts  -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | grep -i "japan" 2>/dev/null | head -n 1 2>/dev/null`

test -z "$enable_font" && enable_font=`find /share/fonts           -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /usr/share/fonts       -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /usr/local/share/fonts -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /Library/Fonts         -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | head -n 1 2>/dev/null`
test -z "$enable_font" && enable_font=`find /System/Library/Fonts  -name "*.ttf" -o -name "*.otf" -o -name "*.dfont" 2>/dev/null | head -n 1 2>/dev/null`
if test -n "$enable_font" ; then
	AC_MSG_RESULT($enable_font)
	AC_DEFINE_UNQUOTED(DEFAULT_FONT,[((char *)"$enable_font")], default font)
else
	AC_MSG_RESULT(no)
	AC_MSG_ERROR(font missing)
fi

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

ALL_LINGUAS="ja"
AM_GNU_GETTEXT
LOCALEDIR='${prefix}/share/locale'
AC_SUBST(LOCALEDIR)

AC_CONFIG_FILES([Makefile po/Makefile.in
		 src/Makefile])
AC_OUTPUT