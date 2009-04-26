/*
 * Copyright (C) 2008 Francesco Salvestrini
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <bfd.h>
#include <assert.h>

#include "elf-lib.h"
#include "log.h"

struct callback_data {
	bfd * abfd;
};

void callback(bfd * bfd_in, asection * sect, void * obj)
{
	bfd * bfd_out;

	assert(obj);
	bfd_out = ((struct callback_data *) obj)->abfd;

	debug("  Copying section %d %s",
	      sect->index, bfd_section_name(abfd, sect));
}

int main(int argc, char * argv[])
{
	bfd *                bfd_in;
	bfd *                bfd_out;
	char *               filename_in;
	char *               filename_out;
	int                  index_from;
	int                  index_to;
	asection *           section_from;
	asection *           section_to;
	struct callback_data data;

        log_init(PROGRAM_NAME);
	log_level(LOG_DEBUG);

	if (argc != 5) {
		fatal("Wrong parameters count");
	}

	filename_in = argv[1];
	if (!filename_in) {
		fatal("Missing input filename");
	}
	filename_out = argv[2];
	if (!filename_out) {
		fatal("Missing output filename");
	}
	index_from = atoi(argv[3]);
	if (index_from < 0) {
		fatal("Wrong index from");
	}
	index_to = atoi(argv[4]);
	if (index_to < 0) {
		fatal("Wrong index to");
	}
	if (index_from == index_to) {
		warning("Index from and index to are equal");
	}

	bfd_init();

	debug("Reading input file %s", filename_in);
	bfd_in = bfd_openr(filename_in, NULL);
	if (!bfd_in) {
		fatal("Cannot open input file %s (%s)",
		      filename_in, BFD_strerror());
	}
	if (!bfd_check_format(bfd_in, bfd_object)) {
		fatal("Wrong input file format (not an object)");
	}

	section_from = BFD_find(bfd_in, index_from);
	if (!section_from) {
		fatal("Cannot find section number %d", index_from);
	}
	debug("Section %d is %s",
	      index_from, bfd_section_name(bfd_in, section_from));

	section_to = BFD_find(bfd_in, index_to);
	if (!section_to) {
		fatal("Cannot find section number %d", index_to);
	}
	debug("Section %d is %s",
	      index_to, bfd_section_name(bfd_in, section_to));

	bfd_out = bfd_openw(filename_out, NULL);
	if (!bfd_out) {
		fatal("Cannot open output file %s (%s)",
		      filename_out, BFD_strerror());
	}

	debug("Generating output file %s", filename_out);
	bfd_set_format(bfd_out, bfd_get_format(bfd_in));

	if (bfd_copy_private_header_data(bfd_in, bfd_out) == FALSE) {
		fatal("Cannot copy private header data (%s)",
		      BFD_strerror())
	}

	data.abfd = bfd_out;
	bfd_map_over_sections(bfd_in, callback, &data);

	bfd_close(bfd_in);
	bfd_close(bfd_out);

	exit(0);
}
