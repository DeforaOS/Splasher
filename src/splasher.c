/* $Id$ */
/* Copyright (c) 2010-2014 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS System Splasher */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#include <string.h>
#include <errno.h>
#ifdef __NetBSD__
# include <sys/ioctl.h>
# include <fcntl.h>
# include <unistd.h>
#endif
#include <System.h>
#include "splasher.h"
#include "../data/Splasher.h"
#include "../config.h"


/* Splasher */
/* public */
/* functions */
/* splasher */
int splasher(AppServerOptions options)
{
	AppServer * appserver;

	if((appserver = appserver_new(NULL, options, PACKAGE, NULL)) == NULL)
	{
		error_print(PACKAGE);
		return 1;
	}
	appserver_loop(appserver);
	appserver_delete(appserver);
	return 0;
}


/* interface */
/* Splasher_enable */
int32_t Splasher_enable(App * app, AppServerClient * asc, uint32_t enabled)
{
	int ret = 0;

#ifdef __NetBSD__
# define WSDISPLAYIO_SSPLASH	0x8004575d
	int fd;
	char const filename[] = "/dev/ttyE0";

	if((fd = open(filename, O_WRONLY)) < 0)
		return -error_set_print(PACKAGE, 1, "%s: %s", filename,
				strerror(errno));;
	if(ioctl(fd, WSDISPLAYIO_SSPLASH, &enabled) < 0)
		ret = -error_set_print(PACKAGE, 1, "%s: %s", filename,
				strerror(errno));
	close(fd);
#else
	/* FIXME implement */
#endif
	return ret;
}


/* Splasher_progress */
int32_t Splasher_progress(App * app, AppServerClient * client,
		uint32_t progress, char const * text)
{
	int ret = 0;

#ifdef __NetBSD__
# define WSDISPLAYIO_PROGRESS	0x8004575e
	int fd;
	char const filename[] = "/dev/ttyE0";

	if(progress > 100)
		return -error_set_print(PACKAGE, 1, "%s", strerror(ERANGE));
	if((fd = open(filename, O_WRONLY)) < 0)
		return -error_set_print(PACKAGE, 1, "%s: %s", filename,
				strerror(errno));;
	if(ioctl(fd, WSDISPLAYIO_PROGRESS, &progress) < 0)
		ret = -error_set_print(PACKAGE, 1, "%s: %s", filename,
				strerror(errno));
	close(fd);
#else
	if(progress > 100)
		return -error_set_print(PACKAGE, 1, "%s", strerror(ERANGE));
	/* FIXME implement */
#endif
	return ret;
}
