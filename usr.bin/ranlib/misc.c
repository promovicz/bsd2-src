/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Hugh Smith at The University of Guelph.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if	!defined(lint) && defined(DOSCCS)
static char sccsid[] = "@(#)misc.c	5.2 (Berkeley) 2/26/91";
#endif

#include <sys/param.h>
#include <sys/signal.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "pathnames.h"

extern int errno;
extern char *archive, *malloc();	/* archive name */
void error();
char *tname = "temporary file";		/* temporary file "name" */

tmp()
{
	long set, oset;
	int fd;
	char path[MAXPATHLEN];

	bcopy(_PATH_RANTMP, path, sizeof(_PATH_RANTMP));

	set = sigmask(SIGHUP)|sigmask(SIGINT)|sigmask(SIGQUIT)|sigmask(SIGTERM);
	oset = sigsetmask(set);
	if ((fd = mkstemp(path)) == -1)
		error(tname);
        (void)unlink(path);
	(void)sigsetmask(oset);
	return(fd);
}

void *
emalloc(len)
	int len;
{
	char *p;

	if (!(p = malloc((u_int)len)))
		error(archive);
	return((void *)p);
}

char *
rname(path)
	char *path;
{
	register char *ind;

	return((ind = rindex(path, '/')) ? ind + 1 : path);
}

void
badfmt()
{
	errno = EINVAL;
	error(archive);
}

void
error(name)
	char *name;
{
	(void)fprintf(stderr, "ranlib: %s: %s\n", name, strerror(errno));
	exit(1);
}
