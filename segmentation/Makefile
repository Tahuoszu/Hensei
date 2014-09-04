SRCDIR	= src
OBJDIR	= obj
BINDIR	= bin
HDRDIR  = hdr
LIBDIR	= lib

CC		= g++
CFLAGS  = -Wall -pedantic -g -std=c++11
LDFLAGS = -L$(LIBDIR) -lsamplerate
INCLUDE = -I$(HDRDIR)/
EXEC	= Segmentation

SRC	= $(wildcard $(SRCDIR)/*.cpp)
OBJ	= $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LDFLAGS) 

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

leak:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes $(BINDIR)/$(EXEC)

.PHONY: all clean makedirs

clean:
	-@rm -f $(OBJ)
	-@rm -f $(BINDIR)/$(EXEC)
	-@rm -f $(SRCDIR)/*[#~]
	-@rm -f $(OBJDIR)/*[#~]

makedirs:
	-@mkdir -p $(OBJDIR)
	-@mkdir -p $(BINDIR)
