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
#include <stdio.h>

#ifndef ELF_UTILS_UTILS_H
#define ELF_UTILS_UTILS_H

/* const is forbidden by some bfd_*() prototypes */
void         BFD_dump(bfd * abfd);
const char * BFD_strerror(void);
asection *   BFD_find(bfd * abfd, int index);

void   version(const char * program_name);
void   hint(const char * program_name,
            const char * message);

void * xmalloc(size_t size);
void   xfree(void * p);
char * xstrdup(const char * s);

#define max(A,B) ((A >= B) ? A : B)

#endif /* ELF_UTILS_UTILS_H */
