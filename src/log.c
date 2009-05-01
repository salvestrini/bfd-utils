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

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "debug.h"
#include "log.h"
#include "utils.h"

static char *      banner_ = NULL;
static log_level_t level_  = LOG_MESSAGE;

void log_init(const char * banner,
              log_level_t  level)
{
        BUG_ON(banner == NULL);

        banner_ = xstrdup(banner);
        level_  = level;

        BUG_ON(banner_ == NULL);
}

void log_level(log_level_t level)
{
        level_ = level;
}

int log_write(log_level_t  level,
              const char * format,
              ...)
{
        BUG_ON(banner_ == NULL);

        va_list arguments;
        int     i;

        va_start(arguments, format);
        i = 0;
        if (level >= level_) {
                FILE * stream = stdout;
                if (level_ >= LOG_WARNING) {
                        /* Log to stderr if level is ge warning */
                        stream = stderr;
                }
                if (level_ >= LOG_WARNING) {
                        /* Print the banner if level is ge warning */
                        fprintf(stream, "%s: ", banner_);
                }
                i = vfprintf(stream, format, arguments);
                fflush(stream);
        }
        va_end(arguments);

        return i;
}

void log_fini(void)
{
        BUG_ON(banner_ == NULL);

        free(banner_);
}
