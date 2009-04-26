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
#include <assert.h>

#include "elf-lib.h"
#include "log.h"

struct callback_data {
	unsigned int count;
	const char * symbol;
};

void callback(bfd * abfd, asection * sect, void * obj)
{
	struct callback_data * data;

	assert(obj);
	data = (struct callback_data *) obj;

	if (data->symbol) {
	}

	data->count++;
}

int main(int argc, char * argv[])
{
	bfd *                bfd_in;
	char *               filename_in;
	struct callback_data data;

        log_init(PROGRAM_NAME);
	log_level(LOG_DEBUG);

	if (argc != 3) {
		fatal("Wrong parameters count");
	}

	filename_in = argv[1];
	if (!filename_in) {
		fatal("Missing input filename");
	}

	data.symbol = argv[2];
	if (!data.symbol) {
		fatal("Missing symbol");
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

	debug("Looking for symbol %s into sections", data.symbol);

	data.count  = 0;
	bfd_map_over_sections(bfd_in, callback, &data);
	assert(data.count == bfd_count_sections(bfd_in));

	bfd_close(bfd_in);

	exit(0);
}
