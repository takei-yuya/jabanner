#!/usr/bin/env sh

aclocal
autoheader
automake --add-missing --copy
autoconf
