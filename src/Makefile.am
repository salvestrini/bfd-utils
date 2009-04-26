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

EXTRA_DIST =

## Programs

bin_PROGRAMS =					\
	elf-symbol-find				\
	elf-section-stat			\
	elf-section-ls				\
	elf-section-mv

common_LDADD =					\
	libcommon.a				\
	-lbfd

elf_symbol_find_SOURCES =			\
	elf-symbol-find.c
elf_symbol_find_CPPFLAGS =			\
	-D 'PROGRAM_NAME="elf-symbol-find"'	\
	$(EXTRA_CPPFLAGS)
elf_symbol_find_LDADD =				\
	$(common_LDADD)

elf_section_stat_SOURCES =			\
	elf-stat.c
elf_section_stat_CPPFLAGS =			\
	-D 'PROGRAM_NAME="elf-section-stat"'	\
	$(EXTRA_CPPFLAGS)
elf_section_stat_LDADD =			\
	$(common_LDADD)

elf_section_ls_SOURCES =			\
	elf-section-ls.c
elf_section_ls_CPPFLAGS =			\
	-D 'PROGRAM_NAME="elf-section-ls"'	\
	$(EXTRA_CPPFLAGS)
elf_section_ls_LDADD =				\
	$(common_LDADD)

elf_section_mv_SOURCES =			\
	elf-section-mv.c
elf_section_mv_CPPFLAGS =			\
	-D 'PROGRAM_NAME="elf-section-mv"'	\
	$(EXTRA_CPPFLAGS)
elf_section_mv_LDADD =				\
	$(common_LDADD)


## Libraries

noinst_LIBRARIES =				\
	libcommon.a

libcommon_a_SOURCES =				\
	log.c					\
	log.h					\
	elf-lib.c				\
	elf-lib.h
libcommon_a_CPPFLAGS =				\
	$(EXTRA_CPPFLAGS)

##
## Maintainer related targets
##
update-local: Makefile

all_SRCS =					\
	$(elf_stat_SOURCES)			\
	$(elf_symbol_find_SOURCES)		\
	$(elf_section_ls_SOURCES)		\
	$(elf_section_mv_SOURCES)

maintainer-check-local: Makefile
	$(WHITESPACE_DETECT)  $(all_SRCS)
