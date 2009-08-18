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
	fetch.in				\
	whitespace-detect.in			\
	gitlog-to-committers.in			\
	gittag-to-date.in			\
						\
	git-version-gen				\
	gitlog-to-changelog			\
	announce-gen

scripts =					\
	fetch					\
	whitespace-detect			\
	gitlog-to-committers			\
	gittag-to-date				\
						\
	git-version-gen				\
	gitlog-to-changelog			\
	announce-gen

##
## Maintainer related targets
##
HOST = "http://git.savannah.gnu.org/gitweb/?p=gnulib.git;a=blob_plain;hb=HEAD;f="

update-local: Makefile
	rm -r -f fetch-dir && \
	mkdir fetch-dir && \
	$(FETCH) $(HOST)build-aux/git-version-gen fetch-dir/git-version-gen && \
	chmod a+rx fetch-dir/git-version-gen && \
	chmod u+w  fetch-dir/git-version-gen && \
	$(FETCH) $(HOST)build-aux/gitlog-to-changelog fetch-dir/gitlog-to-changelog && \
	chmod a+rx fetch-dir/gitlog-to-changelog && \
	chmod u+w  fetch-dir/gitlog-to-changelog && \
	$(FETCH) $(HOST)build-aux/announce-gen fetch-dir/announce-gen && \
	chmod a+rx fetch-dir/announce-gen && \
	chmod u+w  fetch-dir/announce-gen && \
	mv -f fetch-dir/* ./ || { \
		rm -r -f fetch-dir ; \
		exit 1 ; \
	} && \
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
