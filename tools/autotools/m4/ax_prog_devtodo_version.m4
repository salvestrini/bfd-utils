#
# SYNOPSIS
#
#   AX_PROG_DEVTODO_VERSION([VERSION],[ACTION-IF-TRUE],[ACTION-IF-FALSE])
#
# DESCRIPTION
#
#   Makes sure that devtodo supports the version indicated. If true the shell
#   commands in ACTION-IF-TRUE are executed. If not the shell commands in
#   ACTION-IF-FALSE are run. Note if $DEVTODO is not set (for example by
#   running AC_CHECK_PROG or AC_PATH_PROG) the macro will fail.
#
#   Example:
#
#     AC_PATH_PROG([DEVTODO],[devtodo])
#     AC_PROG_DEVTODO_VERSION([1.2.0],[ ... ],[ ... ])
#
#   This will check to make sure that the devtodo you have supports at least
#   version 1.2.0.
#
#   NOTE: This macro uses the $DEVTODO variable to perform the check.
#   AX_WITH_DEVTODO can be used to set that variable prior to running this
#   macro. The $DEVTODO_VERSION variable will be valorized with the detected
#   version.
#
# LAST MODIFICATION
#
#   2008-04-12
#
# COPYLEFT
#
#   Copyright (c) 2008 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.

AC_DEFUN([AX_PROG_DEVTODO_VERSION],[
    AC_REQUIRE([AC_PROG_SED])
    AC_REQUIRE([AC_PROG_GREP])

    AS_IF([test -n "$DEVTODO"],[
        ax_devtodo_version="$1"

        AC_MSG_CHECKING([for devtodo version])
        changequote(<<,>>)
        devtodo_version=`$DEVTODO --version 2>&1`
        #
        # Some buggy systems have ncurses problems: they output unneeded escape
        # sequences. In order to avoid those escape sequences in the output we
        # must filter the devtodo output.
        #
        devtodo_version="`echo $devtodo_version | $SED 's/^.*\([0-9]\{1,\}\.[0-9]\{1,\}\.[0-9]\{1,\}\)/\1/'`"
        changequote([,])
        AC_MSG_RESULT($devtodo_version)

	AC_SUBST([DEVTODO_VERSION],[$devtodo_version])

        AX_COMPARE_VERSION([$ax_devtodo_version],[le],[$devtodo_version],[
	    :
            $2
        ],[
	    :
            $3
        ])
    ],[
        AC_MSG_WARN([could not find the devtodo program])
        $3
    ])
])
