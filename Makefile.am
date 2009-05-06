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

ACLOCAL_AMFLAGS = -I tools/autotools/m4

SUBDIRS =					\
	tools					\
	src					\
	tests					\
	man					\
	site

##
## NOTE:
##     Options listed in AUTOMAKE_OPTIONS variable are applied on a
##     per-`Makefile' basis.
##
AUTOMAKE_OPTIONS = check-news

##
## NOTE:
##     Makefile.sub is automatically distributed by automake rules
##
EXTRA_DIST =						\
	TODO NEWS 					\
	BUGS README COPYING AUTHORS INSTALL THANKS	\
	bootstrap					\
	configure.ac.in					\
	perl.af						\
	.todo

##
## Maintainer related targets
##

MAINTAINERCLEANFILES =

DNT_DB     = $(top_builddir)/.dnt.db
DEVTODO_DB = $(top_srcdir)/.todo
DNT_FLAGS  = --database=$(DNT_DB) --mono

$(DNT_DB): $(DEVTODO_DB)
	$(DEVTODO_TO_DNT)			\
		--input=$(DEVTODO_DB)		\
		--output=$(DNT_DB)		\
		--force || {			\
		rm -f $(DNT_DB) ;		\
		exit 1 ;			\
	}

TODO: $(DNT_DB)
	$(DNT) $(DNT_FLAGS)			\
	       show				\
	       --filter=not-done		\
	       --line-format="* %t"		\
	       --width=0			\
	       --indent-fill=""			\
	       --unindent-fill=""		\
	       --level-fill=""			\
	       --output=TODO || {		\
		rm -f TODO ;			\
		exit 1 ;			\
	}
MAINTAINERCLEANFILES += TODO

NEWS: $(DNT_DB)
	echo "${PACKAGE_VERSION}:" > NEWS
	script="$(GITTAG_TO_DATE)";				\
	r_head="";						\
	d_head="";						\
	r_tail="";						\
	d_tail="";						\
	for i in `$$script | sed -e 's/\ /:/g' | sort -r -k 2`;	\
	do							\
		if test "x$$r_head" = "x"; then			\
			r_head="`echo $$i | sed 's/^.*://'`";	\
			d_head="`echo $$i | sed 's/:.*$$//'`";	\
			continue;				\
		else						\
			if test "x$$d_head" = "x"; then		\
				rm -f NEWS;			\
				exit 1;				\
			fi;					\
		fi;						\
		r_tail="`echo $$i | sed 's/^.*://'`";		\
		d_tail="`echo $$i | sed 's/:.*$$//'`";		\
		echo "$$r_head:" >> NEWS;			\
		echo "* $$d_tail -> $$d_head" >> NEWS;		\
		r_head="$$r_tail";				\
		d_head="$$d_tail";				\
	done || {						\
		rm -f NEWS ;					\
		exit 1;						\
	};							\
	d_tail="1970-01-01";					\
	echo "$$r_head:" >> NEWS;				\
	echo "* $$d_tail -> $$d_head" >> NEWS
MAINTAINERCLEANFILES += NEWS

AUTHORS:
	rm -f AUTHORS                       &&                                  \
	touch AUTHORS                       &&                                  \
	cat $(srcdir)/AUTHORS.in >> AUTHORS &&                                  \
	$(GITLOG_TO_COMMITTERS) | $(SED) -e 's,\(.*\),  \1,' >> AUTHORS &&      \
	echo "" >> AUTHORS                  || {                                \
	        rm -f AUTHORS ;                                                 \
	        exit 1 ;                                                        \
	}
MAINTAINERCLEANFILES += AUTHORS

ChangeLog:
	$(GITLOG_TO_CHANGELOG) > ChangeLog || {	\
		rm -f ChangeLog ;		\
		exit 1 ;			\
	}
MAINTAINERCLEANFILES += ChangeLog

dist-hook: NEWS TODO ChangeLog

dist-gpg: dist
	gpg --yes -b --use-agent					   \
		-o $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz.sig	   \
		$(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz          &&   \
	gpg --verify $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz.sig || { \
		rm -f $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz.sig ;   \
		exit 1 ;						   \
	}
MAINTAINERCLEANFILES += $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz.sig

dist-upload: dist-gpg
	chmod 644 $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz     &&	\
	chmod 644 $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz.sig &&	\
	scp $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz		\
	    $${USER}@dl.sv.nongnu.org:/releases/grmrextractors     &&	\
	scp $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.gz.sig		\
	    $${USER}@dl.sv.nongnu.org:/releases/grmrextractors     || {	\
		exit 1 ;						\
	}

announcement:
	$(ANNOUNCE_GEN)				\
	  --release-type=alpha			\
	  --package=$(PACKAGE_TARNAME)		\
	  --prev=$(PACKAGE_VERSION).test	\
	  --curr=$(PACKAGE_VERSION)		\
	  --gpg-key-id=TEST			\
	  --url-dir=TEST

site: all
	(cd site && $(MAKE) $(AM_MAKEFLAGS) site)

HOST = "http://git.savannah.gnu.org/gitweb/?p=gnulib.git;a=blob_plain;hb=HEAD;f="

update-download:
	rm -r -f fetch-dir && \
	mkdir fetch-dir && \
	$(FETCH) $(HOST)doc/INSTALL fetch-dir/INSTALL && \
	chmod a+r fetch-dir/INSTALL && \
	chmod u+w fetch-dir/INSTALL && \
	$(FETCH) $(HOST)doc/COPYINGv2 fetch-dir/COPYING && \
	chmod a+r fetch-dir/COPYING && \
	chmod u+w fetch-dir/COPYING && \
	mv -f fetch-dir/* ./ || { \
		rm -r -f fetch-dir ; \
		exit 1 ; \
	} && \
	rm -r -f fetch-dir

update-local: Makefile update-download 

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
