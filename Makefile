CC := gcc
SCRDIR := src
INCDIR := include
BUILDDIR := build
BINDIR := bin
CFLAGS :=
LIB := -L lib
INC := -I $(INCDIR)

all: dirs cin.o files.o history.o
	@echo "Linking..."
	@echo "$(CC) $(LIB) $(BUILDDIR)/cin.o $(BUILDDIR)/files.o $(BUILDDIR)/history.o -o $(BINDIR)/cin"; $(CC) $(LIB) $(BUILDDIR)/cin.o $(BUILDDIR)/files.o $(BUILDDIR)/history.o -o bin/cin

files.o: dirs $(SCRDIR)/files.c
	@echo "Building files..."
	@echo "$(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/files.c -o build/files.o"; $(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/files.c -o build/files.o

history.o: dirs $(SCRDIR)/history.c
	@echo "Building history..."
	@echo "$(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/history.c -o build/history.o"; $(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/history.c -o build/history.o

cin.o: dirs $(SCRDIR)/cin.c
	@echo "Building cin..."
	@echo "$(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/cin.c -o build/cin.o"; $(CC) $(CFLAGS) $(INC) -c $(SCRDIR)/cin.c -o build/cin.o

dirs:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)

clean:
	@echo "Cleaning..."; 
	@echo "$(RM) -r $(BUILDDIR)/*"; $(RM) -r $(BUILDDIR)/*