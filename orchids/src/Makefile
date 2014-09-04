SRCDIR = src
OBJDIR = obj
BINDIR = bin
HDRDIR = hdr

LSSDIR = $(sort $(dir $(wildcard ${HDRDIR}/*/)))
SUBDIR = $(LSSDIR:$(HDRDIR)/%=%)

HDRSUBDIR = $(addprefix $(HDRDIR)/, $(SUBDIR))
OBJSUBDIR = $(addprefix $(OBJDIR)/, $(SUBDIR))

CC		= clang++
CFLAGS  = -Wall -pedantic -g
LDFLAGS =
INCLUDE = $(foreach d, $(HDRSUBDIR), -I $d)
EXEC	= tskm

SRC	= $(wildcard $(SRCDIR)/**/*.cpp)
OBJ	= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LDFLAGS) 

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $< $(LDFLAGS)

leak:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes $(BINDIR)/$(EXEC)

.PHONY: all clean makedirs

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(BINDIR)
	@rm -f **/*~ # Remove tempory files

makedirs:
	@mkdir -p $(OBJSUBDIR)
	@mkdir -p $(BINDIR)
