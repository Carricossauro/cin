CC := gcc

SRCDIR := src
INCDIR := include
BUILDDIR := build
BINDIR := bin

CFLAGS :=
TARGET := $(BINDIR)/cin

LIB := -L lib
INC := -I $(INCDIR)

SOURCES :=\
	$(SRCDIR)/files.c\
	$(SRCDIR)/history.c\
	$(SRCDIR)/cin.c

OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.c=.o))