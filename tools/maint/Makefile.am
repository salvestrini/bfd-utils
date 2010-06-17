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
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program; if not, write to the Free Software Foundation, Inc.,
## 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
##

include $(top_srcdir)/Makefile.sub

EXTRA_DIST =					\
	git-version-gen				\
	gitlog-to-changelog			\
	announce-gen

scripts =					\
	fetch					\
	wordwrap-detect				\
	whitespace-detect			\
	gitlog-to-committers			\
	gittag-to-date				\
	releases-to-news			\
	guards-check				\
	$(EXTRA_DIST)

##
## Maintainer related targets
##
URL_BU = "http://github.com/salvestrini/build-utils/raw/master/maint"

EXTERNAL =					\
	$(URL_BU)/fetch.in			\
	$(URL_BU)/wordwrap-detect.in		\
	$(URL_BU)/whitespace-detect.in		\
	$(URL_BU)/gitlog-to-committers.in	\
	$(URL_BU)/gittag-to-date.in		\
	$(URL_BU)/releases-to-news.in		\
	$(URL_BU)/guards-check.in

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

maintainer-check-parameters: Makefile $(scripts)
	for i in $(scripts) ; do \
		echo @ECHO_N@ "Checking standard parameters for $$i... " ; \
		if ( ./$$i -h 2>&1 > /dev/null ) ; then \
			echo "@ECHO_T@ok" ; \
		else \
			echo "@ECHO_T@error" ; \
			exit 1 ; \
		fi ; \
	done

maintainer-check-local: Makefile maintainer-check-parameters
