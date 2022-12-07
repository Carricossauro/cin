include config/config.mk

all: $(OBJECTS)
	@echo "Linking..."
	@echo "$(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c dirs
	@echo "Building..."
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

dirs:
	@echo "Creating directories..."
	@echo "mkdir -p $(BUILDDIR)"; mkdir -p $(BUILDDIR)
	@echo "mkdir -p $(BINDIR)"; mkdir -p $(BINDIR)

clean:
	@echo "Cleaning..."; 
	@echo "$(RM) -r $(BUILDDIR) $(BINDIR)"; $(RM) -r $(BUILDDIR) $(BINDIR)

debug: .dbg all

.dbg:
	$(eval CFLAGS += -g)