##
## Input file for automake
##
## Copyright (C) 2008, 2009 Francesco Salvestrini
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program; if not, write to the Free Software Foundation, Inc.,
## 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
##

include $(top_srcdir)/Makefile.sub

AUTOMAKE_OPTIONS = subdir-objects

SUBDIRS = gnulib

EXTRA_DIST     =

COMMON_CPPFLAGS =
COMMON_CFLAGS   = -I $(srcdir)/gnulib

## Programs

bin_PROGRAMS =					\
	bfd-section-stat			\
	bfd-section-ls				\
	bfd-section-mv				\
	bfd-section-remangle			\
	bfd-section-symbols

common_LDADD =					\
	libcommon.a				\
	gnulib/libgnu.a				\
	-lbfd

bfd_section_stat_SOURCES =			\
	bfd-section-stat.c
bfd_section_stat_CPPFLAGS =			\
	-D 'PROGRAM_NAME="bfd-section-stat"'	\
	$(COMMON_CPPFLAGS)
bfd_section_stat_CFLAGS =			\
	$(COMMON_CFLAGS)
bfd_section_stat_LDADD =			\
	$(common_LDADD)				\
	-lm

bfd_section_ls_SOURCES =			\
	bfd-section-ls.c
bfd_section_ls_CPPFLAGS =			\
	-D 'PROGRAM_NAME="bfd-section-ls"'	\
	$(COMMON_CPPFLAGS)
bfd_section_ls_CFLAGS =				\
	$(COMMON_CFLAGS)
bfd_section_ls_LDADD =				\
	$(common_LDADD)				\
	-lm

bfd_section_mv_SOURCES =			\
	bfd-section-mv.c
bfd_section_mv_CPPFLAGS =			\
	-D 'PROGRAM_NAME="bfd-section-mv"'	\
	$(COMMON_CPPFLAGS)
bfd_section_mv_CFLAGS =				\
	$(COMMON_CFLAGS)
bfd_section_mv_LDADD =				\
	$(common_LDADD)

bfd_section_remangle_SOURCES =			\
	bfd-section-remangle.c
bfd_section_remangle_CPPFLAGS =				\
	-D 'PROGRAM_NAME="bfd-section-remangle"'	\
	$(COMMON_CPPFLAGS)
bfd_section_remangle_CFLAGS =			\
	$(COMMON_CFLAGS)
bfd_section_remangle_LDADD =			\
	$(common_LDADD)

bfd_section_symbols_SOURCES =			\
	bfd-section-symbols.c
bfd_section_symbols_CPPFLAGS =			\
	-D 'PROGRAM_NAME="bfd-section-symbols"'	\
	$(COMMON_CPPFLAGS)
bfd_section_symbols_CFLAGS =			\
	$(COMMON_CFLAGS)
bfd_section_symbols_LDADD =			\
	$(common_LDADD)


## Libraries

noinst_LIBRARIES =				\
	libcommon.a

libcommon_a_SOURCES =				\
	log.c					\
	log.h					\
	utils.c					\
	utils.h
libcommon_a_CFLAGS =				\
	$(COMMON_CFLAGS)
libcommon_a_CPPFLAGS =				\
	$(COMMON_CPPFLAGS)

##
## Maintainer related targets
##
update-local: Makefile

all_SRCS =					\
	$(bfd_section_stat_SOURCES)		\
	$(bfd_section_remangle_SOURCES)		\
	$(bfd_section_ls_SOURCES)		\
	$(bfd_section_mv_SOURCES)

maintainer-check-parameters: Makefile $(bin_PROGRAMS)
	for i in $(bin_PROGRAMS) ; do \
		echo @ECHO_N@ "Checking standard parameters for $$i... " ; \
		if ( ./$$i -h 2>&1 > /dev/null ) ; then \
			echo "@ECHO_T@ok" ; \
		else \
			echo "@ECHO_T@error" ; \
			exit 1 ; \
		fi ; \
	done

maintainer-check-whitespaces: Makefile $(all_SRCS)
	$(WHITESPACE_DETECT) $(all_SRCS)

maintainer-check-guards: Makefile $(all_SRCS)
	$(GUARDS_CHECK) $(all_SRCS)

maintainer-check-local: Makefile maintainer-check-guards maintainer-check-whitespaces maintainer-check-parameters
