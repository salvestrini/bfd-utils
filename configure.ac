# Process this file with autoconf to produce a configure script.

#
# configure.ac for bfd-utils
#
# Copyright (C) 2008, 2009 Francesco Salvestrini
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

AC_INIT([BFD-Utils],
        m4_esyscmd([tools/maint/git-version-gen .tarball-version]),
        [salvestrini@gmail.com],
        [bfd-utils],
        [http://github.com/salvestrini/bfd-utils])

# Check for a recent version of autoconf
AC_PREREQ([2.65])

# Place/find all autotools related files in the following directories
AC_CONFIG_AUX_DIR([tools/autotools])
AC_CONFIG_MACRO_DIR([tools/autotools/m4])
AC_CONFIG_SRCDIR([src/bfd-section-stat.c])
AC_CONFIG_HEADERS([src/config.h])

#
# For automake options (AM_INIT_AUTOMAKE options) see Makefile.am
# file, AUTOMAKE_OPTIONS variable
#
AM_INIT_AUTOMAKE([1.11.1 foreign std-options -Wall color-tests])

#
# Build related programs
#
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LN_S
AC_PROG_MKDIR_P
AC_PROG_GREP
AC_PROG_SED

AC_PROG_CPP
AC_PROG_CC
AC_PROG_CC_C_O
AC_PROG_RANLIB

#
# Required libraries
#
AC_CHECK_LIB(bfd,bfd_map_over_sections,[],[
        AC_MSG_ERROR([Your system lacks of libbfd support])
])
AC_CHECK_LIB(m,log10,[],[
        AC_MSG_ERROR([Your system lacks of libm support])
])

#
# gnulib related
#
GNULIB_EARLY
GNULIB_INIT

#
# Build related programs
#
AX_PATH_MISSING([PERL],     [perl])
AX_PATH_MISSING([HELP2MAN], [help2man])
AX_PATH_MISSING([WGET],     [wget])
AX_PATH_MISSING([DNT],      [dnt])
AX_PATH_MISSING([SORT],     [sort])

AX_SPLIT_VERSION($PACKAGE_VERSION, AX_MAJOR_VERSION, AX_MINOR_VERSION, AX_MICRO_VERSION, AX_EXTRA_VERSION)
AX_PACKAGE_API([${AX_MAJOR_VERSION}"."${AX_MINOR_VERSION}])

# XXX FIXME: Replace with proper checks
AC_SUBST(EXTRA_CPPFLAGS, "-Wall -Werror")

AC_CONFIG_FILES([
	Makefile

	src/Makefile
        src/gnulib/Makefile

	man/Makefile

	tests/Makefile

	tools/Makefile
	tools/maint/Makefile
	tools/autotools/Makefile
	tools/autotools/m4/Makefile
])

AC_CONFIG_FILES([tools/maint/fetch],               [chmod +x tools/maint/fetch])
AC_CONFIG_FILES([tools/maint/wordwrap-detect],     [chmod +x tools/maint/wordwrap-detect])
AC_CONFIG_FILES([tools/maint/whitespace-detect],   [chmod +x tools/maint/whitespace-detect])
AC_CONFIG_FILES([tools/maint/gitlog-to-committers],[chmod +x tools/maint/gitlog-to-committers])
AC_CONFIG_FILES([tools/maint/gittag-to-date],      [chmod +x tools/maint/gittag-to-date])
AC_CONFIG_FILES([tools/maint/releases-to-news],    [chmod +x tools/maint/releases-to-news])
AC_CONFIG_FILES([tools/maint/guards-check],        [chmod +x tools/maint/guards-check])

AC_OUTPUT
