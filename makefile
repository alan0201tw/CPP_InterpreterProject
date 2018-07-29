# Compile Info
CC := g++
SRCEXT := cpp
CFLAGS := -O2 -std=c++11 -pthread -g -Wall
INCDIR := -I include

# Source Info
SRCDIR := src
BINDIR := bin
TARGET := main
SOURCES := $(shell find $(SRCDIR) -type f -iname "*.$(SRCEXT)" ! -iname "$(TARGET).$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BINDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Test Info
TESTSRCDIR := testsrc
TESTBINDIR := testbin
TESTSOURCES := $(shell find $(TESTSRCDIR) -type f -name "*.$(SRCEXT)")
TESTTARGETS := $(patsubst $(TESTSRCDIR)/%,$(TESTBINDIR)/%,$(TESTSOURCES:.$(SRCEXT)=))

# Compile main
$(TARGET): $(OBJECTS) $(BINDIR)/$(TARGET).o
	@echo "Linking..."
	@echo "$(CC) $^ $(CFLAGS) -o $(TARGET) $(LIB)"; $(CC) $^ $(CFLAGS) -o $(TARGET)

$(BINDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BINDIR)
	@echo "$(CC) $(CFLAGS) $(INCDIR) -c -o $@ $<"; $(CC) $(CFLAGS) $(INCDIR) -c -o $@ $<

# Compile testers
tester: $(TESTTARGETS)
	@mkdir -p $(TESTBINDIR)

$(TESTBINDIR)/%: $(TESTBINDIR)/%.o $(OBJECTS)
	@echo "$(CC) $^ $(CFLAGS) $(LIB) -o $@"; $(CC) $^ $(CFLAGS) $(LIB) -o $@

$(TESTBINDIR)/%.o: $(TESTSRCDIR)/%.cpp $(OBJECTS)
	@mkdir -p $(TESTBINDIR)
	@echo "$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@"; $(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

# Clean all binary files
clean:
	@echo " Cleaning..."; 
	@echo "$(RM) -r $(BINDIR) $(TARGET)"; $(RM) -r $(BINDIR) $(TARGET)
	@echo "$(RM) -r $(TESTBINDIR)"; $(RM) -r $(TESTBINDIR)

.PHONY: clean