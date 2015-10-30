CC=g++
CCFLAGS=-g -W -Wall

FLEX=flex
FLEX_OPTS=-PRoller

BISON=bison
BISON_OPTS=-t -pRoller

OBJS=Absyn.o Lexer.o Parser.o Printer.o

.PHONY: clean distclean

all: TestRoller

clean:
	rm -f *.o TestRoller Roller.aux Roller.log Roller.pdf Roller.dvi Roller.ps Roller

distclean: clean
	rm -f Absyn.C Absyn.H Test.C Parser.C Parser.H Lexer.C Skeleton.C Skeleton.H Printer.C Printer.H Makefile Roller.l Roller.y Roller.tex 

TestRoller: ${OBJS} Test.o
	@echo "Linking TestRoller..."
	${CC} ${CCFLAGS} ${OBJS} Test.o -o TestRoller

Absyn.o: Absyn.C Absyn.H
	${CC} ${CCFLAGS} -c Absyn.C

Lexer.C: Roller.l
	${FLEX} -oLexer.C Roller.l

Parser.C: Roller.y
	${BISON} Roller.y -o Parser.C

Lexer.o: Lexer.C Parser.H
	${CC} ${CCFLAGS} -c Lexer.C 

Parser.o: Parser.C Absyn.H
	${CC} ${CCFLAGS} -c Parser.C

Printer.o: Printer.C Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.C

Skeleton.o: Skeleton.C Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -c Skeleton.C

Test.o: Test.C Parser.H Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Test.C
