# Defining the compiler to be used
CC=gcc
CFLAGS=-Wall -c

BINDIR=bin
EXECUTABLE=apkg
LIBPKG=package/

all: apkg

apkg: package.o main.o
	$(CC) package.o main.o -o $(BINDIR)/$(EXECUTABLE)

main.o:
	$(CC) $(CFLAGS) main.c

package.o:
	$(CC) $(CFLAGS) $(LIBPKG)package.c

tests: package.o tests.o
	$(CC) package.o tests.o -o test
	./test
	make testsClean

tests.o:
	$(CC) $(CFLAGS) tests/tests.c

clean:
	rm -rf *.o $(BINDIR)/$(EXECUTABLE)
	
testsClean:
	rm -rf package.o tests.o test tests/*.pkg
	
#install:
#	cp $(BINDIR)/$(EXECUTABLE) /bin/$(EXECUTABLE)
	
rebuild: clean all