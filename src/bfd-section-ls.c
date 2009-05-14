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
#include <getopt.h>

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

void help(void)
{
        message("%s [OPTION]...\n", PROGRAM_NAME);
        message("\n");
        message("Options:\n");

        message("  -i, --input      specify input filename\n");

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
	char *               filename_in;
	struct callback_data data;

        log_init(PROGRAM_NAME, LOG_MESSAGE);
        atexit(log_fini);

	filename_in = NULL;

        int c;
        // int digit_optind = 0;
        while (1) {
                // int this_option_optind = optind ? optind : 1;
                int option_index       = 0;

                static struct option long_options[] = {
                        { "input",        1, 0, 'i' },

                        { "debug",        0, 0, 'd' },
                        { "verbose",      0, 0, 'v' },
                        { "version",      0, 0, 'V' },
                        { "help",         0, 0, 'h' },
                        { 0,              0, 0, 0   }
                };
                c = getopt_long(argc, argv, "i:dvVh",
                                long_options, &option_index);
                if (c == -1) {
                        break;
                }

                debug("Handling option character '%c'\n", c);

                switch (c) {
                        case 'i':
                                filename_in = optarg;
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
