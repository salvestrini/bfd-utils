# ===========================================================================
#        http://www.nongnu.org/autoconf-archive/ax_split_version.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_SPLIT_VERSION(VERSION, MAJOR, MINOR, MICRO, EXTRA)
#
# DESCRIPTION
#
#   Splits a version number in the format MAJOR[.MINOR[.MICRO]][-EXTRA] into its
#   separeate components. Fills MAJOR, MINOR, MICRO and EXTRA variables.
#   Does not AC_SUBST the passed variables.
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

    $2=`echo "$1" | $SED -n -e 's/^\([[^\.\-]][[^\.\-]]*\).*$/\1/p;'`
    $3=`echo "$1" | $SED -n -e 's/^[[^\.\-]][[^\.\-]]*\.\([[^\.\-]][[^\.\-]]*\).*$/\1/p;'`
    $4=`echo "$1" | $SED -n -e 's/^[[^\.\-]][[^\.\-]]*\.[[^\.\-]][[^\.\-]]*\.\([[^\.\-]][[^\.\-]]*\).*$/\1/p;'`
    $5=`echo "$1" | $SED -n -e 's/^.*\-\([[^\-]][[^\-]]*\)$/\1/p;'`

    AC_MSG_RESULT([$1 (major=']$$2[', minor=']$$3[', micro=']$$4[', extra=']$$5[')])
])
