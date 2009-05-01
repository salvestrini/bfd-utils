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

#include <bfd.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "debug.h"

const char * BFD_strerror(void)
{
	return bfd_errmsg(bfd_get_error());
}

/* const is forbidden by some bfd_*() prototypes */
void BFD_dump(bfd * abfd)
{
	BUG_ON(abfd == NULL);

	debug("Infos:");
	debug("  Generic:");
	debug("    Name:     %s", bfd_get_filename(abfd));
	debug("    Size:     %d", (size_t) bfd_get_size(abfd));
	debug("    Format:   %d", bfd_get_format(abfd));

	if (bfd_get_format(abfd) == bfd_unknown) {
		return;
	}

	debug("  Specific:");
	debug("    Symcount: %d", bfd_get_symcount(abfd));
	debug("    Sections: %d", bfd_count_sections(abfd));
	if (bfd_count_sections(abfd)) {
		struct bfd_section * tmp;
		int                  count;

		debug("  Sections:");

		count = 0;
		for (tmp = abfd->sections; tmp != NULL; tmp = tmp->next) {
			debug("    Id:     %d",
			      tmp->id);
			debug("      Name:   %s",
			      bfd_section_name(bfd, tmp));
			debug("      Size:   %d",
			      (size_t) bfd_section_size(bfd, tmp));
			count++;
		}

		BUG_ON(count != bfd_count_sections(abfd));
	}
}

struct callback_data {
	int index;
};

bfd_boolean callback_find(bfd * abfd, asection * sect, void * obj)
{
	int index;

	index = (* (int *) obj);

	if (sect->index == index) {
		return TRUE;
	}

	return FALSE;
}

asection * BFD_find(bfd * abfd, int index)
{
	BUG_ON(abfd != NULL);

	return bfd_sections_find_if(abfd, callback_find, &index);
}

void hint(const char * program_name,
          const char * message)
{
        BUG_ON(program_name == NULL);

        message("%s: %s\n", program_name, message);
        message("Try `%s --help' for more information.", program_name);
}

void * xmalloc(size_t size)
{
        void * tmp;

        BUG_ON(size == 0);

        tmp = malloc(size);
        if (!tmp) {
                fatal("Cannot allocate %d B of memory\n", size);
                exit(EXIT_FAILURE);
        }

        return tmp;
}

void xfree(void * pointer)
{
        BUG_ON(pointer == NULL);

        free(pointer);
}

char * xstrdup(const char * s)
{
        char * tmp;

        BUG_ON(s == NULL);

        tmp = strdup(s);
        if (!tmp) {
                fatal("Cannot duplicate string `%s'\n", s);
                exit(EXIT_FAILURE);
        }

        return tmp;
}
