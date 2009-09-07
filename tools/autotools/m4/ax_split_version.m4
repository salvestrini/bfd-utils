# ===========================================================================
#        http://www.nongnu.org/autoconf-archive/ax_split_version.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_SPLIT_VERSION
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
#   Copyright (c) 2009 Alessandro Massignan <ff0000.it@gmail.com>
#   Copyright (c) 2008 Tom Howard <tomhoward@users.sf.net>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.

AC_DEFUN([AX_SPLIT_VERSION],[
    AC_REQUIRE([AC_PROG_SED])

    AC_MSG_CHECKING([version])
    AC_MSG_RESULT([$VERSION])

    AC_MSG_CHECKING([major version])
    AX_MAJOR_VERSION=`echo "$VERSION" | $SED -n -e 's/^\([[0-9]][[0-9A-Za-z]]*\)\(\.[[0-9]][[0-9A-Za-z]]*\)\?\(\.[[0-9]][[0-9A-Za-z]]*\)\?\(\-[[0-9A-Za-z]][[0-9A-Za-z_]]*\)\?$/\1/p;'`
    AS_IF([test -z $AX_MAJOR_VERSION],[
        AC_MSG_RESULT([unknown])
    ],[
        AC_MSG_RESULT([$AX_MAJOR_VERSION])
    ])

    AC_MSG_CHECKING([minor version])
    AX_MINOR_VERSION=`echo "$VERSION" | $SED -n -e 's/^\([[0-9]][[0-9A-Za-z]]*\)\(\.\([[0-9]][[0-9A-Za-z]]*\)\)\(\.[[0-9]][[0-9A-Za-z]]*\)\?\(\-[[0-9A-Za-z]][[0-9A-Za-z_]]*\)\?$/\3/p;'`
    AS_IF([test -z $AX_MINOR_VERSION],[
        AC_MSG_RESULT([unknown])
    ],[
        AC_MSG_RESULT([$AX_MINOR_VERSION])
    ])

    AC_MSG_CHECKING([micro version])
    AX_MICRO_VERSION=`echo "$VERSION" | $SED -n -e 's/^\([[0-9]][[0-9A-Za-z]]*\)\(\.[[0-9]][[0-9A-Za-z]]*\)\(\.\([[0-9]][[0-9A-Za-z]]*\)\)\(\-[[0-9A-Za-z]][[0-9A-Za-z_]]*\)\?$/\4/p;'`
    AS_IF([test -z $AX_MICRO_VERSION],[
        AC_MSG_RESULT([unknown])
    ],[
        AC_MSG_RESULT([$AX_MICRO_VERSION])
    ])

    AC_MSG_CHECKING([extra version])
    AX_EXTRA_VERSION=`echo "$VERSION" | $SED -n -e 's/^\([[0-9A-Za-z]][[0-9A-Za-z]]*\)\(\.[[0-9A-Za-z]][[0-9A-Za-z]]*\)\?\(\.[[0-9A-Za-z]][[0-9A-Za-z]]*\)\?\(\-\([[0-9A-Za-z]][[0-9A-Za-z_]]*\)\)$/\5/p;'`
    AS_IF([test -z $AX_EXTRA_VERSION],[
        AC_MSG_RESULT([unknown])
    ],[
        AC_MSG_RESULT([$AX_EXTRA_VERSION])
    ])
])
