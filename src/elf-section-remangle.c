/*
 * Copyright (C) 2008, 2009 Francesco Salvestrini
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

#include "debug.h"
#include "log.h"
#include "utils.h"

#if 0
struct callback_data {
	bfd * abfd;
};

void callback(bfd * bfd_in, asection * sect, void * obj)
{
	bfd * bfd_out;

	BUG_ON(obj == NULL);
	bfd_out = ((struct callback_data *) obj)->abfd;

	debug("  Copying section %d %s\n",
	      sect->index, bfd_section_name(abfd, sect));
}
#endif

int main(int argc, char * argv[])
{
	bfd *                bfd_in;
	bfd *                bfd_out;
	char *               filename_in;
	char *               filename_out;
#if 0
	struct callback_data data;
#endif

        log_init(PROGRAM_NAME, LOG_DEBUG);
        atexit(log_fini);

	if (argc != 3) {
		hint(PROGRAM_NAME, "Wrong parameters count\n");
                exit(EXIT_FAILURE);
	}

	filename_in = argv[1];
	if (!filename_in) {
		fatal("Missing input filename\n");
                exit(EXIT_FAILURE);
	}
	filename_out = argv[2];
	if (!filename_out) {
		fatal("Missing output filename\n");
                exit(EXIT_FAILURE);
	}

	bfd_init();

	debug("Reading input file %s\n", filename_in);
	bfd_in = bfd_openr(filename_in, NULL);
	if (!bfd_in) {
		fatal("Cannot open input file %s (%s)\n",
		      filename_in, BFD_strerror());
                exit(EXIT_FAILURE);
	}
	if (!bfd_check_format(bfd_in, bfd_object)) {
		fatal("Wrong input file format (not an object)\n");
                exit(EXIT_FAILURE);
	}

	bfd_out = bfd_openw(filename_out, NULL);
	if (!bfd_out) {
		fatal("Cannot open output file %s (%s)\n",
		      filename_out, BFD_strerror());
                exit(EXIT_FAILURE);
	}

	debug("Generating output file %s\n", filename_out);
	bfd_set_format(bfd_out, bfd_get_format(bfd_in));

	if (bfd_copy_private_bfd_data(bfd_in, bfd_out) == FALSE) {
		fatal("Cannot copy private bfd data (%s)\n",
		      BFD_strerror());
                exit(EXIT_FAILURE);
        }
	if (bfd_copy_private_header_data(bfd_in, bfd_out) == FALSE) {
		fatal("Cannot copy private header data (%s)\n",
		      BFD_strerror());
                exit(EXIT_FAILURE);
        }

	bfd_close(bfd_in);
	bfd_close(bfd_out);

	exit(EXIT_SUCCESS);
}
