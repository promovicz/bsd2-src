#
#	@(#)Makefile	5.5 (Berkeley) 9/18/85
#
COMFLAGS=-DBSD4_2 -O -DSACREDMEM=256000
SEPFLAG= -i
BIN=${DESTDIR}/usr/ucb

compress: compress.c USERMEM
	${CC} ${SEPFLAG} $(COMFLAGS) -DUSERMEM=`cat USERMEM` -o compress compress.c

# USERMEM may have to be set by hand.  It should contain the amount of
# available user memory in bytes.  Set it to zero, for physical memory
# less than 1 Meg.
USERMEM:
	sh usermem.sh > USERMEM

install: compress
	install -s compress $(BIN)
	rm -f $(BIN)/uncompress $(BIN)/zcat
	ln $(BIN)/compress $(BIN)/uncompress
	ln $(BIN)/compress $(BIN)/zcat

# Temporarily don't delete USERMEM.  When chroot'ed to /nbsd, usermem.sh
# fails totally.
clean:
	rm -f compress core errs
#	rm -f compress USERMEM core errs
