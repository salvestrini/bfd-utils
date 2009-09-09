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

##
## Maintainer related targets
##
URL_AA = "http://git.savannah.gnu.org/cgit/autoconf-archive.git/plain/m4"
URL_BU = "http://github.com/salvestrini/build-utils/tree/master/m4"

EXTERNAL =					\
	$(URL_BU)/ax_split_version.m4		\
	$(URL_AA)/ax_compare_version.m4		\
	$(URL_AA)/ax_missing_prog.m4		\
	$(URL_AA)/ax_path_missing.m4		\
	$(URL_AA)/ax_with_prog.m4

INTERNAL =					\
	ax_prog_devtodo_version.m4

MACROS =					\
	$(INTERNAL)				\
	$(EXTERNAL)

update-local: Makefile
	rm -r -f fetch-dir && \
	mkdir fetch-dir && \
	for i in $(EXTERNAL) ; do \
	        URL="$$i" ; \
	        NAME=`echo "$$i" | $(SED) -e 's,^.*/,,'` ; \
	        $(FETCH) $$URL?raw=true fetch-dir/$$NAME && \
	        mv fetch-dir/$$NAME $$NAME || { \
	                rm -f fetch-dir/$$NAME ; \
	                exit 1 ; \
	        } \
	done && \
	rm -r -f fetch-dir

maintainer-check-local: Makefile
