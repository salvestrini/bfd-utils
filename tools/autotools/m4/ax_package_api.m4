# ===========================================================================
#        http://www.nongnu.org/autoconf-archive/ax_package_api.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_PACKAGE_API(STRING)
#
# DESCRIPTION
#
#   This macro defines some versioned directory names and AC_SUBST them. The
#   versioned directory names depend on PACKAGE (from AC_INIT) and the STRING
#   passed as input parameter.
#
# LICENSE
#
#   Copyright (c) 2009 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.

AC_DEFUN([AX_PACKAGE_API],[
    AC_SUBST([PACKAGE_API],[$1])
    AC_SUBST(pkgvdir,        ["\${datadir}/${PACKAGE}-${PACKAGE_API}"])
    AC_SUBST(pkgvbindir,     ["\${datadir}/${PACKAGE}-${PACKAGE_API}/bin"])
    AC_SUBST(pkgvlibsdir,    ["\${datadir}/${PACKAGE}-${PACKAGE_API}/libs"])
    AC_SUBST(pkgvdatadir,    ["\${datadir}/${PACKAGE}-${PACKAGE_API}/data"])
    AC_SUBST(pkgvincludedir, ["\${includedir}/${PACKAGE}-${PACKAGE_API}"])
    AC_SUBST(pkgvpythondir,  ["\${pythondir}/${PACKAGE}-${PACKAGE_API}"])
])
