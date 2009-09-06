# ===========================================================================
#        http://www.nongnu.org/autoconf-archive/ax_split_version.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_SPLIT_VERSION(VERSION)
#
# DESCRIPTION
#
#   Splits a version number in the format MAJOR.MINOR.MICRO-EXTRA into its
#   separate components. MAJOR, MINOR and MICRO are recognized as numbers
#   while EXTRA could be whatever.
#
# LICENSE
#
#   Copyright (c) 2009 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#   Copyright (c) 2008 Tom Howard <tomhoward@users.sf.net>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.

AC_DEFUN([AX_SPLIT_VERSION],[
    AC_REQUIRE([AC_PROG_SED])
    AC_REQUIRE([AC_PROG_GREP])

    AC_MSG_CHECKING([version])
    AC_MSG_RESULT([$1])

    AC_MSG_CHECKING([major version])
    AX_MAJOR_VERSION=`echo "$1" | $SED -e 's/^\([[0-9]][[0-9]]*\).*/\1/'`
    AS_IF([test `echo $AX_MAJOR_VERSION | $GREP '[[0-9]]*'`],[
        AX_MAJOR_VERSION=0
    ])
    AC_MSG_RESULT([$AX_MAJOR_VERSION])

    AC_MSG_CHECKING([minor version])
    AX_MINOR_VERSION=`echo "$1" | $SED -e 's/^[[0-9]][[0-9]]*\.\([[0-9]][[0-9]]*\).*/\1/'`
    AS_IF([test `echo $AX_MINOR_VERSION | $GREP '[[0-9]]*'`],[
        AX_MINOR_VERSION=0
    ])
    AC_MSG_RESULT([$AX_MINOR_VERSION])

    AC_MSG_CHECKING([micro version])
    AX_MICRO_VERSION=`echo "$1" | $SED -e 's/^[[0-9]][[0-9]]*\.[[0-9]][[0-9]]*\.\([[0-9]][[0-9]]*\).*/\1/'`
    AS_IF([test `echo $AX_MICRO_VERSION | $GREP '[[0-9]]*'`],[
        AX_MICRO_VERSION=0
    ])
    AC_MSG_RESULT([$AX_MICRO_VERSION])

    AC_MSG_CHECKING([extra version])
    AX_EXTRA_VERSION=`echo "$1" | $SED -e 's/[[0-9]][[0-9]]*.[[0-9]][[0-9]]*.[[0-9]][[0-9]]*\-\(.*\)/\1/'`
    AC_MSG_RESULT([$AX_EXTRA_VERSION])
])
