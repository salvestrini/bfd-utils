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
#include <getopt.h>
#include <string.h>

#include "debug.h"
#include "log.h"
#include "utils.h"

struct callback_data {
	bfd * abfd;
};

void callback(bfd * bfd_in, asection * sect, void * obj)
{
	bfd * bfd_out;

	BUG_ON(obj == NULL);
	bfd_out = ((struct callback_data *) obj)->abfd;

	debug("  Copying section %d %s",
	      sect->index, bfd_section_name(abfd, sect));
}

void help(void)
{
        message("%s [OPTION]...\n", PROGRAM_NAME);
        message("\n");
        message("Options:\n");

        message("  -d, --debug      enable debugging traces\n");
        message("  -v, --verbose    verbosely report processing\n");
        message("  -V, --version    print this help, then exit\n");
        message("  -h, --help       print version number, then exit\n");
        message("\n");
        message("Report bugs to <%s>\n", PACKAGE_BUGREPORT);
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

        log_init(PROGRAM_NAME, LOG_MESSAGE);
        atexit(log_fini);

        filename_in  = NULL;
        filename_out = NULL;

        int c;
        // int digit_optind = 0;
        while (1) {
                // int this_option_optind = optind ? optind : 1;
                int option_index       = 0;

                static struct option long_options[] = {
                        { "input",        1, 0, 'i' },
                        { "output",       1, 0, 'o' },

                        { "debug",        0, 0, 'd' },
                        { "verbose",      0, 0, 'v' },
                        { "version",      0, 0, 'V' },
                        { "help",         0, 0, 'h' },
                        { 0,              0, 0, 0   }
                };
                c = getopt_long(argc, argv, "dvVh",
                                long_options, &option_index);
                if (c == -1) {
                        break;
                }

                debug("Handling option character '%c'\n", c);

                switch (c) {
                        case 'i':
                                filename_in = optarg;
                                break;
                        case 'o':
                                filename_out = optarg;
                                break;
                        case 'd':
                                log_level(LOG_DEBUG);
                                break;
                        case 'v':
                                log_level(LOG_VERBOSE);
                                break;
                        case 'V':
                                version(PROGRAM_NAME);
                                return 0;
                        case 'h':
                                help();
                                return 0;
                        case '?':
                                hint(PROGRAM_NAME, "Unrecognized option");
                                return 1;
                        default:
                                BUG();
                                return 1;
                }
        }

	if (!filename_in) {
		fatal("Missing input filename\n");
                exit(EXIT_FAILURE);
	}
	if (!filename_out) {
		fatal("Missing output filename\n");
                exit(EXIT_FAILURE);
	}
        /* XXX FIXME: Use stat instead of strcmp */
        if (!strcmp(filename_in, filename_out)) {
		fatal("Input and output are the same file\n");
                exit(EXIT_FAILURE);
        }

	index_from = atoi(argv[3]);
	if (index_from < 0) {
		fatal("Wrong index from\n");
                exit(EXIT_FAILURE);
	}
	index_to = atoi(argv[4]);
	if (index_to < 0) {
		fatal("Wrong index to\n");
                exit(EXIT_FAILURE);
	}
	if (index_from == index_to) {
		warning("Index from and index to are equal\n");
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
		fatal("Wrong input file format (not an object)\n");
                exit(EXIT_FAILURE);
	}

	section_from = BFD_find(bfd_in, index_from);
	if (!section_from) {
		fatal("Cannot find section number %d", index_from);
                exit(EXIT_FAILURE);
	}
	debug("Section %d is %s",
	      index_from, bfd_section_name(bfd_in, section_from));

	section_to = BFD_find(bfd_in, index_to);
	if (!section_to) {
		fatal("Cannot find section number %d", index_to);
                exit(EXIT_FAILURE);
	}
	debug("Section %d is %s",
	      index_to, bfd_section_name(bfd_in, section_to));

	bfd_out = bfd_openw(filename_out, NULL);
	if (!bfd_out) {
		fatal("Cannot open output file %s (%s)",
		      filename_out, BFD_strerror());
                exit(EXIT_FAILURE);
	}

	debug("Generating output file %s", filename_out);
	bfd_set_format(bfd_out, bfd_get_format(bfd_in));

	if (bfd_copy_private_header_data(bfd_in, bfd_out) == FALSE) {
		fatal("Cannot copy private header data (%s)",
		      BFD_strerror());
                exit(EXIT_FAILURE);
        }

	data.abfd = bfd_out;
	bfd_map_over_sections(bfd_in, callback, &data);

	bfd_close(bfd_in);
	bfd_close(bfd_out);

	exit(EXIT_SUCCESS);
}
