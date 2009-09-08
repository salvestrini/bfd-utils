# ===========================================================================
#        http://www.nongnu.org/autoconf-archive/ax_split_version.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_SPLIT_VERSION(VERSION, [MAJOR, [MINOR, [MICRO, [EXTRA]]]])
#
# DESCRIPTION
#
#   Splits a version number in the format MAJOR[.MINOR[.MICRO]][-EXTRA] into its
#   separate components. Fills MAJOR, MINOR, MICRO and EXTRA variables.
#   Does not AC_SUBST the passed variables.
#
#   Examples:
#
#     AX_SPLIT_VERSION("1",[MAJOR])
#     AX_SPLIT_VERSION("1-a",[MAJOR],,,[EXTRA])
#     AX_SPLIT_VERSION("1.2",[MAJOR],[MINOR])
#     AX_SPLIT_VERSION("1.2.3",[MAJOR],,[MICRO])
#     AX_SPLIT_VERSION("1.2-alfa",[MAJOR],[MINOR],,[EXTRA])
#     AX_SPLIT_VERSION("1.33.4444",[MAJOR],[MINOR],[MICRO])
#     AX_SPLIT_VERSION("12.44.333111-alfa",[MAJOR])
#     AX_SPLIT_VERSION("12.44.333111-alfa",,[MINOR])
#     AX_SPLIT_VERSION("12.44.333111-alfa",,,[MICRO])
#     AX_SPLIT_VERSION("12.44.333111-alfa",,,,[EXTRA])
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
    AC_MSG_RESULT([$1])

    AS_IF([test -n "$2"],[
        AC_MSG_CHECKING([major])
        $2=`echo "$1" | $SED -n -e 's/^\([[^\.\-]][[^\.\-]]*\).*$/\1/p;'`
        AC_MSG_RESULT(['][$$2]['])
    ])
    AS_IF([test -n "$3"],[
        AC_MSG_CHECKING([minor])
        $3=`echo "$1" | $SED -n -e 's/^[[^\.\-]][[^\.\-]]*\.\([[^\.\-]][[^\.\-]]*\).*$/\1/p;'`
        ax_split_version_temp="$ax_split_version_temp minor='][$$3]['"
        AC_MSG_RESULT(['][$$3]['])
    ])
    AS_IF([test -n "$4"],[
        AC_MSG_CHECKING([micro])
        $4=`echo "$1" | $SED -n -e 's/^[[^\.\-]][[^\.\-]]*\.[[^\.\-]][[^\.\-]]*\.\([[^\.\-]][[^\.\-]]*\).*$/\1/p;'`
        ax_split_version_temp="$ax_split_version_temp micro='][$$4]['"
        AC_MSG_RESULT(['][$$4]['])
    ])
    AS_IF([test -n "$5"],[
        AC_MSG_CHECKING([extra])
        $5=`echo "$1" | $SED -n -e 's/^.*\-\([[^\-]][[^\-]]*\)$/\1/p;'`
        ax_split_version_temp="$ax_split_version_temp extra='][$$5]['"
        AC_MSG_RESULT(['][$$5]['])
    ])
])
