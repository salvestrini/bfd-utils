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

#ifndef ELF_UTILS_LOG_H
#define ELF_UTILS_LOG_H

typedef enum {
        LOG_DEBUG,
        LOG_VERBOSE,
        LOG_MESSAGE,
        LOG_WARNING,
        LOG_ERROR,
        LOG_FATAL
} log_level_t;

void log_init(const char * banner,
              log_level_t  level);
void log_level(log_level_t level);
int  log_write(log_level_t level, const char * fmt, ...);
void log_fini(void);

#define fatal(FMT,ARGS...)   log_write(LOG_FATAL,   FMT, ##ARGS)
#define error(FMT,ARGS...)   log_write(LOG_ERROR,   FMT, ##ARGS)
#define warning(FMT,ARGS...) log_write(LOG_WARNING, FMT, ##ARGS)
#define verbose(FMT,ARGS...) log_write(LOG_VERBOSE, FMT, ##ARGS)
#define message(FMT,ARGS...) log_write(LOG_MESSAGE, FMT, ##ARGS)
#define debug(FMT,ARGS...)   log_write(LOG_DEBUG,   FMT, ##ARGS)

#endif /* ELF_UTILS_LOG_H */
