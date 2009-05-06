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
#include <math.h>
#include <string.h>

#include "utils.h"
#include "log.h"
#include "debug.h"

struct entry {
        struct entry * next;
        char *         name;
        bfd_size_type  size;
};

struct callback_data {
        struct entry * head;
};

void callback(bfd * abfd, asection * sect, void * obj)
{
	struct callback_data * data;
        const char *           name;
        struct entry *         tmp;

	BUG_ON(abfd  == NULL);
	BUG_ON(sect  == NULL);
	BUG_ON(obj   == NULL);

	data = (struct callback_data *) obj;

        name = bfd_section_name(abfd, sect);
        BUG_ON(name == NULL);

        debug("Callback called for `%s'\n", name);

        /* Find the section in our list */
        for (tmp = data->head; tmp != NULL; tmp = tmp->next) {
                debug("Comparing `%s'\n", tmp->name);
                BUG_ON(tmp->name == NULL);
                if (!strcmp(tmp->name, name)) {
                        /* Got it */
                        break;
                }
        }

        if (tmp == NULL) {
                /* Not found ... */
                debug("Building new entry for section `%s'\n", name);

                tmp = (struct entry *) xmalloc(sizeof(tmp));
                tmp->name = xstrdup(name);
                tmp->size = sect->size;
                tmp->next = NULL;

                /* Add it */
                tmp->next  = data->head;
                data->head = tmp;
        } else {
                error("Duplicated `%s' section found\n", name);
        }
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

#define max(A,B) ((A >= B) ? A : B)

void dump(struct callback_data * data)
{
        struct entry * tmp;
        size_t         max_name_length;
        bfd_size_type  size_total;

        debug("Computing starting values\n");

        BUG_ON(data == NULL);

        max_name_length = 0;
        size_total      = 0;
        for (tmp = data->head; tmp != NULL; tmp = tmp->next) {
                max_name_length = max(max_name_length, strlen(tmp->name));
                size_total      = size_total + tmp->size;
        }

        debug("max_name_length = %d\n", max_name_length);
        debug("size_total      = %d\n", size_total);

        BUG_ON(max_name_length == 0);
        BUG_ON(size_total      <= 0);

        debug("Dumping entries\n");

        for (tmp = data->head; tmp != NULL; tmp = tmp->next) {
                message("%-*s  %*d  [ %5.2f ]\n",
                        max_name_length,
                        tmp->name,
                        ((int) log10(size_total)) + 1,
                        tmp->size,
                        (tmp->size / size_total) * 100);
        }
}

static struct callback_data data;

void clear_entries(void)
{
        struct entry * tmp;

        debug("Cleaning-up entries\n");
        for (; data.head != NULL;) {
                tmp       = data.head;
                data.head = data.head->next;

                BUG_ON(tmp == NULL);
                BUG_ON(tmp->name == NULL);

                debug("Removing entry `%s'\n", tmp->name);
                xfree(tmp->name);
                xfree(tmp);
        }
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
                        { "input",        0, 0, 'i' },

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

        data.head  = NULL;
        atexit(clear_entries);

        debug("Iterating sections\n");
        bfd_map_over_sections(bfd_in, callback, &data);

        dump(&data);

        bfd_close(bfd_in);

	exit(EXIT_SUCCESS);
}
