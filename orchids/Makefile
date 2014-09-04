SRCDIR = src
OBJDIR = obj
BINDIR = bin
HDRDIR = hdr
LIBDIR = lib

CC		= g++
CFLAGS  = -Wall -pedantic -g
LDFLAGS = -L$(LIBDIR)/
INCLUDE = -I$(HDRDIR)/
EXEC	= Analysis

SRC	= $(wildcard $(SRCDIR)/*.cpp)
OBJ	= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
LIB = -lsdif

all: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LDFLAGS) $(LIB)

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

leak:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes $(BINDIR)/$(EXEC)

.PHONY: all clean makedirs

clean:
	@rm -rf $(OBJ)
	@rm -f $(BINDIR)/$(EXEC)
	@rm -f **/*~

makedirs:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)
