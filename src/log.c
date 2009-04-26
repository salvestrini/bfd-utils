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

#include <assert.h>
#include <stdlib.h>

#include "debug.h"

int    debugging = 0;
char * banner;

void log_init(char * b)
{
        BUG_ON(b == NULL);

        banner = strdup(b);

        BUG_ON(banner == NULL);
}

void log_level(log_level_t level)
{
}

void log_fini(void)
{
        BUG_ON(banner == NULL);

        free(banner);
}
