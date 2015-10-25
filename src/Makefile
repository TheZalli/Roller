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
	rm -f Absyn.CPP Absyn.H Test.CPP Parser.CPP Parser.H Lexer.CPP Skeleton.CPP Skeleton.H Printer.CPP Printer.H Makefile Roller.l Roller.y Roller.tex 

TestRoller: ${OBJS} Test.o
	@echo "Linking TestRoller..."
	${CC} ${CCFLAGS} ${OBJS} Test.o -o TestRoller

Absyn.o: Absyn.CPP Absyn.H
	${CC} ${CCFLAGS} -c Absyn.CPP

Lexer.CPP: Roller.l
	${FLEX} -oLexer.CPP Roller.l

Parser.CPP: Roller.y
	${BISON} Roller.y -o Parser.CPP

Lexer.o: Lexer.CPP Parser.H
	${CC} ${CCFLAGS} -c Lexer.CPP 

Parser.o: Parser.CPP Absyn.H
	${CC} ${CCFLAGS} -c Parser.CPP

Printer.o: Printer.CPP Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Printer.CPP

Skeleton.o: Skeleton.CPP Skeleton.H Absyn.H
	${CC} ${CCFLAGS} -c Skeleton.CPP

Test.o: Test.CPP Parser.H Printer.H Absyn.H
	${CC} ${CCFLAGS} -c Test.CPP
