PROGRAM = Warmup
OBJECTS = TryTokenScanner.o Warmup.o

CPPOPTIONS = -IStanfordCPPLib -fvisibility-inlines-hidden
LDOPTIONS = -L.
LIB = -lStanfordCPPLib

# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(PROGRAM)

check: $(PROGRAM)
	@./$(PROGRAM)

$(PROGRAM): $(OBJECTS)
	g++ -o $(PROGRAM) $(LDOPTIONS) $(OBJECTS) $(LIB)

TryTokenScanner.o: TryTokenScanner.cpp TryTokenScanner.h libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) $<

Warmup.o: Warmup.cpp TryTokenScanner.cpp TryTokenScanner.h libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) $<

libStanfordCPPLib.a:
	@rm -f libStanfordCPPLib.a
	(cd StanfordCPPLib; make all)
	ln -s StanfordCPPLib/libStanfordCPPLib.a .


# ***************************************************************
# Standard entries to remove files from the directories
#    tidy  -- eliminate unwanted files
#    clean -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a $(PROGRAM)

