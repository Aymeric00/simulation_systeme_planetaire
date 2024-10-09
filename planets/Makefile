OPTIONS = --filter=pandoc-numbering
OPTIONS += --filter=pandoc-crossref

PDFOPTIONS = --highlight-style kate
PDFOPTIONS += --pdf-engine pdflatex
PDFOPTIONS += --number-sections
PDFOPTIONS += --template=./default.latex

HTMLOPTIONS += -t html5
HTMLOPTIONS += -c ../../css/tufte-css/tufte.css
HTMLOPTIONS += --standalone --embed-resources
HTMLOPTIONS += --mathjax=MathJax.js

MD=$(wildcard *.md)
HTML=$(MD:%.md=%.html)
PDF=$(MD:%.md=%.pdf)


all: $(HTML) $(PDF)

%.pdf: %.md Makefile
	pandoc -s $(OPTIONS) $(PDFOPTIONS) -o $@ $<

%.html: %.md Makefile
	pandoc -s $(OPTIONS) $(HTMLOPTIONS) -o $@ $<

clean:
	rm -rf *.html *.pdf
