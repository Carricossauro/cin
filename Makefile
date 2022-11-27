CC := gcc
SCRDIR := src
INCDIR := include
BUILDDIR := build
CFLAGS := -g
LIB := -L lib
INC := -I $(INCDIR)

all: cin.o
	@echo "Linking..."
	@echo "$(CC) $(LIB) $(BUILDDIR)/cin.o -o bin/cin"; $(CC) $(LIB) $(BUILDDIR)/cin.o -o bin/cin 

cin.o: $(SCRDIR)/cin.c
	@echo "Building cin..."
	@echo "$(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/cin.c -o build/cin.o"; $(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/cin.c -o build/cin.o

clean:
	@echo "Cleaning..."; 
	@echo "$(RM) -r $(BUILDDIR)/*"; $(RM) -r $(BUILDDIR)/*