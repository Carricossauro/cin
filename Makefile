CC := gcc
SCRDIR := src
INCDIR := include
BUILDDIR := build
CFLAGS := 
LIB := -L lib
INC := -I $(INCDIR)

all: lexer.o cin.o
	@echo "Linking..."
	@echo "$(CC) $(LIB) $(BUILDDIR)/lexer.o $(BUILDDIR)/cin.o -o bin/cin"; $(CC) $(LIB) $(BUILDDIR)/lexer.o $(BUILDDIR)/cin.o -o bin/cin

lexer.o: $(SCRDIR)/lexer.c $(INCDIR)/lexer.h
	@echo "Building lexer..."
	@echo "$(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/lexer.c -o build/lexer.o"; $(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/lexer.c -o build/lexer.o

cin.o: $(SCRDIR)/cin.c $(INCDIR)/cin.h
	@echo "Building cin..."
	@echo "$(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/cin.c -o build/cin.o"; $(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/cin.c -o build/cin.o

clean:
	@echo "Cleaning..."; 
	@echo "$(RM) -r $(BUILDDIR)/*"; $(RM) -r $(BUILDDIR)/*