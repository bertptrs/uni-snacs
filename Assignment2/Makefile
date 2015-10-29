CXX=g++
CXXFLAGS=-Wall -Wextra -pedantic -O3 -std=c++11

.PHONY: all clean

all: parser report.pdf

clean:
	$(RM) parser
	$(RM) $(wildcard *.o)

parser: parser.cpp TwitterGraph.o eccentricity.o components.o

report.pdf: report.tex
	latexmk -xelatex $<
