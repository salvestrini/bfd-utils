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

SUBDIRS =					\
	in

site-build:
	(cd in && $(MAKE) $(AM_MAKEFLAGS) site)

site-copy:
	if test ! -d out ; then \
		mkdir out ; \
	fi
	cp -R in/.sitetool/site.out/* out

site: all site-build site-copy

##
## Maintainer related targets
##
update-local: Makefile

maintainer-check-local: Makefile
