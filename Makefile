CC := gcc
SCRDIR := src
INCDIR := include
BUILDDIR := build
CFLAGS :=
LIB := -L lib
INC := -I $(INCDIR)

all: cin.o files.o history.o
	@echo "Linking..."
	@echo "$(CC) $(LIB) $(BUILDDIR)/cin.o $(BUILDDIR)/files.o $(BUILDDIR)/history.o -o bin/cin"; $(CC) $(LIB) $(BUILDDIR)/cin.o $(BUILDDIR)/files.o $(BUILDDIR)/history.o -o bin/cin

files.o: $(SCRDIR)/files.c
	@echo "Building files..."
	@echo "$(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/files.c -o build/files.o"; $(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/files.c -o build/files.o

history.o: $(SCRDIR)/history.c
	@echo "Building history..."
	@echo "$(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/history.c -o build/history.o"; $(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/history.c -o build/history.o

cin.o: $(SCRDIR)/cin.c
	@echo "Building cin..."
	@echo "$(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/cin.c -o build/cin.o"; $(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/cin.c -o build/cin.o

clean:
	@echo "Cleaning..."; 
	@echo "$(RM) -r $(BUILDDIR)/*"; $(RM) -r $(BUILDDIR)/*