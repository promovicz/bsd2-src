#	Makefile	4.1.1 (2.11BSD)	1996/10/23
#
CFLAGS = -O
SEPFLAG= -i

all: lex

lex: lmain.o y.tab.o sub1.o sub2.o header.o
	${CC} ${SEPFLAG} lmain.o y.tab.o sub1.o sub2.o header.o -o lex

smallex:
	${CC} ${SEPFLAG} lmain.o y.tab.o sub1.o sub2.o header.o -o lex

y.tab.c: parser.y
	yacc parser.y
lmain.o:lmain.c ldefs.c once.c
	${CC} -c -O lmain.c
sub1.o: sub1.c ldefs.c
	${CC} -c -O sub1.c
sub2.o: sub2.c ldefs.c
	${CC} -c -O sub2.c
header.o: header.c ldefs.c
	${CC} -c -O header.c

install: all
	-mkdir -p ${DESTDIR}/usr/libdata/lex
	chmod 755 ${DESTDIR}/usr/libdata/lex
	install -s -m 755 lex $(DESTDIR)/usr/bin
	install -c -m 444 ncform $(DESTDIR)/usr/libdata/lex
	install -c -m 444 nrform $(DESTDIR)/usr/libdata/lex

clean:
	rm -f *.o lex y.tab.c
