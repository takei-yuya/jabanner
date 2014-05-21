#!/usr/bin/env sh

aclocal
automake --add-missing --copy
autoheader
autoconf
