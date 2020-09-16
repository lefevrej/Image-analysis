EXE=$(BDIR)/addconst $(BDIR)/deriche $(BDIR)/ppm2pgm $(BDIR)/pgm2ppm $(BDIR)/diffimage $(BDIR)/threshold $(BDIR)/normalize $(BDIR)/equalize $(BDIR)/gammac $(BDIR)/inverse
DOC=$(DOCDIR)/tutorialEnglish.html

CCFLAGS = -g -Wall

IDIR = ./include
ODIR = ./obj
BDIR = ./bin
CDIR = ./src/com
LDIR = ./src/lib
DOCDIR = ./doc
CC = cc

# Documentation, if not already comiled, can be compiled thanks to 'make doc'
# You can also do a 'make clean' if you want

all:	$(EXE)
doc:    $(DOC)

# ===============================================================
# shell commands
# ===============================================================

$(BDIR)/addconst:	$(CDIR)/addconst.c $(IDIR)/laddconst.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/laddconst.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/addconst.c $(ODIR)/laddconst.o $(ODIR)/mcimage.o -o $(BDIR)/addconst

$(BDIR)/deriche:	$(CDIR)/deriche.c $(IDIR)/lderiche.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/lderiche.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/deriche.c $(ODIR)/lderiche.o $(ODIR)/mcimage.o -lm -o $(BDIR)/deriche

$(BDIR)/diffimage:   $(CDIR)/diffimage.c $(IDIR)/ldiffimage.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/ldiffimage.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/diffimage.c $(ODIR)/ldiffimage.o $(ODIR)/mcimage.o -lm -o $(BDIR)/diffimage
	
$(BDIR)/threshold:   $(CDIR)/threshold.c $(IDIR)/lthreshold.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/lthreshold.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/threshold.c $(ODIR)/lthreshold.o $(ODIR)/mcimage.o -lm -o $(BDIR)/threshold
	
$(BDIR)/normalize:   $(CDIR)/normalize.c $(IDIR)/lnormalize.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/lnormalize.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/normalize.c $(ODIR)/lnormalize.o $(ODIR)/mcimage.o -lm -o $(BDIR)/normalize
	
$(BDIR)/equalize:   $(CDIR)/equalize.c $(IDIR)/lequalize.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(IDIR)/lnormalize.h $(ODIR)/lnormalize.o $(ODIR)/lequalize.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/equalize.c $(ODIR)/lequalize.o $(ODIR)/mcimage.o $(ODIR)/lnormalize.o -lm -o $(BDIR)/equalize
	
$(BDIR)/gammac:   $(CDIR)/gammac.c $(IDIR)/lgammac.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/lgammac.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/gammac.c $(ODIR)/lgammac.o $(ODIR)/mcimage.o -lm -o $(BDIR)/gammac

$(BDIR)/inverse:   $(CDIR)/inverse.c $(IDIR)/linverse.h $(IDIR)/mcimage.h $(ODIR)/mcimage.o $(ODIR)/linverse.o
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/inverse.c $(ODIR)/linverse.o $(ODIR)/mcimage.o -lm -o $(BDIR)/inverse

# ===============================================================
# Library functions 
# ===============================================================

# Basic ones:
# ===============================================================

$(ODIR)/mcimage.o:	$(LDIR)/mcimage.c $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/mcimage.c -o $(ODIR)/mcimage.o

# Operators:
# ===============================================================

$(ODIR)/laddconst.o:	$(LDIR)/laddconst.c $(IDIR)/laddconst.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/laddconst.c -o $(ODIR)/laddconst.o

$(ODIR)/lderiche.o:	$(LDIR)/lderiche.c $(IDIR)/lderiche.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/lderiche.c -o $(ODIR)/lderiche.o
	
$(ODIR)/ldiffimage.o:	$(LDIR)/ldiffimage.c $(IDIR)/ldiffimage.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/ldiffimage.c -o $(ODIR)/ldiffimage.o	
	
$(ODIR)/lthreshold.o:	$(LDIR)/lthreshold.c $(IDIR)/lthreshold.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/lthreshold.c -o $(ODIR)/lthreshold.o	
	
$(ODIR)/lnormalize.o:	$(LDIR)/lnormalize.c $(IDIR)/lnormalize.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/lnormalize.c -o $(ODIR)/lnormalize.o	
		
$(ODIR)/lequalize.o:	$(LDIR)/lequalize.c $(IDIR)/lequalize.h $(IDIR)/mcimage.h $(IDIR)/lnormalize.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/lequalize.c -o $(ODIR)/lequalize.o
	
$(ODIR)/lgammac.o:	$(LDIR)/lgammac.c $(IDIR)/lgammac.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/lgammac.c -o $(ODIR)/lgammac.o	
	
$(ODIR)/linverse.o:	$(LDIR)/linverse.c $(IDIR)/linverse.h $(IDIR)/mcimage.h
	$(CC) -c $(CCFLAGS) -I$(IDIR) $(LDIR)/linverse.c -o $(ODIR)/linverse.o	

$(BDIR)/ppm2pgm:	$(CDIR)/ppm2pgm.c $(IDIR)/mcimage.h $(LDIR)/mcimage.c
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/ppm2pgm.c  $(ODIR)/mcimage.o -o $(BDIR)/ppm2pgm

$(BDIR)/pgm2ppm:	$(CDIR)/pgm2ppm.c $(IDIR)/mcimage.h $(LDIR)/mcimage.c
	$(CC) $(CCFLAGS) -I$(IDIR) $(CDIR)/pgm2ppm.c $(ODIR)/mcimage.o -o $(BDIR)/pgm2ppm

# Documentation
# ===============================================================
$(DOCDIR)/tutorialEnglish.html: $(DOCDIR)/tutorialEnglish.tex
	cd $(DOCDIR); htlatex ./tutorialEnglish; cd ..

clean:
	rm -rf *~ $(ODIR)/* $(IDIR)/*~ $(CDIR)/*~ $(LDIR)/*~ $(DOCDIR)/*~ 
	cd $(DOCDIR); rm -rf *.4ct *.4tc *.aux *.dvi *.idv *.lg *.log *.tmp *.xref 
