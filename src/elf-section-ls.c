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
#include <math.h>

#include "log.h"
#include "debug.h"
#include "utils.h"

struct callback_data {
        int please_fill_me;
};

void callback(bfd * abfd, asection * sect, void * obj)
{
	struct callback_data * data;

	BUG_ON(obj == NULL);
	data = (struct callback_data *) obj;

        BUG_ON(abfd->section_count <= 0);

	message("%-*d %s\n",
                ((int) log10(abfd->section_count)) + 1,
                sect->index,
                sect->name);
}

int main(int argc, char * argv[])
{
	bfd *                bfd_in;
	char *               filename_in;
	struct callback_data data;

        log_init(PROGRAM_NAME, LOG_MESSAGE);
        atexit(log_fini);

	if (argc != 2) {
		hint(PROGRAM_NAME, "Wrong parameters count");
                exit(EXIT_FAILURE);
	}

	filename_in = argv[1];
	if (!filename_in) {
		hint(PROGRAM_NAME, "Missing input filename");
                exit(EXIT_FAILURE);
	}

	bfd_init();

	debug("Reading input file %s", filename_in);

	bfd_in = bfd_openr(filename_in, NULL);
	if (!bfd_in) {
		fatal("Cannot open input file %s (%s)",
		      filename_in, BFD_strerror());
                exit(EXIT_FAILURE);
	}

	if (!bfd_check_format(bfd_in, bfd_object)) {
		fatal("Wrong input file format (not an object)");
                exit(EXIT_FAILURE);
	}

	debug("Dumping sections");

	bfd_map_over_sections(bfd_in, callback, &data);

	bfd_close(bfd_in);

	exit(EXIT_SUCCESS);
}
