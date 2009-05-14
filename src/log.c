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
              va_list      arguments)
{
        BUG_ON(banner_ == NULL);
        BUG_ON(format  == NULL);

        int i;

        i = 0;
        if (level >= level_) {
                FILE *  stream;
                //va_list arguments;

                stream = stdout;

                /* Log to stderr from LOG_WARNING on */
                if (level_ >= LOG_WARNING) {
                        stream = stderr;
                }

                /* Print the banner from LOG_WARNING on */
                if (level_ >= LOG_WARNING) {
                        fprintf(stream, "%s: ", banner_);
                }

                //va_start(arguments, format);
                i = vfprintf(stream, format, arguments);
                //va_end(arguments);

                fflush(stream);
        }

        return i;
}

int fatal(const char * format, ...)
{
        int     tmp;
        va_list arguments;

        va_start(arguments, format);
        tmp = log_write(LOG_FATAL, format, arguments);
        va_end(arguments);

        return tmp;
}

int error(const char * format, ...)
{
        int     tmp;
        va_list arguments;

        va_start(arguments, format);
        tmp = log_write(LOG_ERROR, format, arguments);
        va_end(arguments);

        return tmp;
}

int warning(const char * format, ...)
{
        int     tmp;
        va_list arguments;

        va_start(arguments, format);
        tmp = log_write(LOG_WARNING, format, arguments);
        va_end(arguments);

        return tmp;
}

int verbose(const char * format, ...)
{
        int     tmp;
        va_list arguments;

        va_start(arguments, format);
        tmp = log_write(LOG_VERBOSE, format, arguments);
        va_end(arguments);

        return tmp;
}

int message(const char * format, ...)
{
        int     tmp;
        va_list arguments;

        va_start(arguments, format);
        tmp = log_write(LOG_MESSAGE, format, arguments);
        va_end(arguments);

        return tmp;
}

int debug(const char * format, ...)
{
        int     tmp;
        va_list arguments;

        va_start(arguments, format);
        tmp = log_write(LOG_DEBUG, format, arguments);
        va_end(arguments);

        return tmp;
}

void log_fini(void)
{
        BUG_ON(banner_ == NULL);

        free(banner_);
}
