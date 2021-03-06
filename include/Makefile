#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	5.16.1 (2.11BSD GTE) 1997/9/22
#
# Doing a make install builds /usr/include
#
# Define SHARED to indicate whether you want
# symbolic links to the system source (``symlinks''),
# or a separate copy (``copies'').
# (latter useful in environments where it's
# not possible to keep /sys publicly readable)
#
# The ``rm -rf''s used below are safe because rm doesn't
# follow symbolic links.
#
DESTDIR=
SUBDIRS=arpa pascal protocols OLD
STD=	a.out.h ar.h assert.h ctype.h curses.h dbm.h fcntl.h \
	fstab.h grp.h lastlog.h limits.h math.h memory.h mp.h mtab.h ndbm.h \
	netdb.h nlist.h paths.h pcc.h pwd.h ranlib.h regexp.h resolv.h \
	setjmp.h sgtty.h stab.h stdarg.h stddef.h stdio.h stdint.h stdlib.h \
	string.h strings.h struct.h syscall.h sysexits.h time.h ttyent.h \
	tzfile.h unistd.h utmp.h varargs.h vfont.h vmf.h
LINKS=	errno.h signal.h syslog.h
MACHINE=pdp
MACHDEP=${MACHINE} pdpif pdpuba pdpmba vaxuba
NETDIRS=net netimp netinet netns
SYSDIRS=${NETDIRS} ${MACHDEP}
SHARED=symlinks
TAGSFILE=tags

all:

install: mkdirs ${SHARED}
	-for i in ${STD}; do \
		cmp -s $$i ${DESTDIR}/usr/include/$$i || \
		    install -c -m 444 $$i ${DESTDIR}/usr/include/$$i; \
	done
	-for i in ${SUBDIRS}; do \
		mkdir -p ${DESTDIR}/usr/include/$$i; \
		(cd $$i; for j in *.[ih]; do \
			cmp -s $$j ${DESTDIR}/usr/include/$$i/$$j || \
			install -c -m 444 $$j ${DESTDIR}/usr/include/$$i/$$j; \
		done); \
	done
	-cmp -s Makefile.install ${DESTDIR}/usr/include/Makefile || \
	    install -c -m 444 Makefile.install ${DESTDIR}/usr/include/Makefile
	-for i in ${LINKS}; do \
		rm -f ${DESTDIR}/usr/include/$$i; \
		ln -s sys/$$i ${DESTDIR}/usr/include/$$i; \
	done
	rm -f ${DESTDIR}/usr/include/machine
	ln -s ${MACHINE} ${DESTDIR}/usr/include/machine
	rm -f ${DESTDIR}/usr/include/frame.h
	ln -s machine/frame.h ${DESTDIR}/usr/include/frame.h

symlinks: mkdirs
	-for i in ${SYSDIRS}; do \
		rm -rf ${DESTDIR}/usr/include/$$i; \
		if [ ! -s ${DESTDIR}/usr/include/$$i ]; \
		then \
			ln -s ../../sys/$$i ${DESTDIR}/usr/include/$$i; \
		else \
			echo ${DESTDIR}/usr/include/$$i not removed; \
		fi; \
	done
	rm -rf ${DESTDIR}/usr/include/sys
	-if [ ! -s ${DESTDIR}/usr/include/sys ]; \
	then \
		ln -s ../../sys/sys ${DESTDIR}/usr/include/sys; \
	else \
		echo ${DESTDIR}/usr/include/sys not removed; \
	fi

copies: mkdirs
	-for i in ${SYSDIRS}; do \
		rm -rf ${DESTDIR}/usr/include/$$i; \
		cd /sys; \
		tar cf - $$i/*.h | (cd ${DESTDIR}/usr/include; tar xpfB -); \
	done
	rm -rf ${DESTDIR}/usr/include/sys
	-mkdir -p ${DESTDIR}/usr/include/sys
	chmod 775 ${DESTDIR}/usr/include/sys
	-(cd /sys/sys; tar cf - *.h | (cd ${DESTDIR}/usr/include/sys; tar xpfB -))

mkdirs:
	-mkdir -p ${DESTDIR}/usr/include
	-mkdir -p ${DESTDIR}/usr/include/sys

tags:
	cwd=/usr/include; \
	for i in ${STD} ${LINKS}; do \
		ctags -a -f ${TAGSFILE} $$cwd/$$i; \
	done

clean:
	rm -f tags
