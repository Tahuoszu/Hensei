SRCDIR	= src
OBJDIR	= obj
BINDIR	= bin
HDRDIR	= hdr

CC		= g++
CFLAGS  = -Wall -pedantic -g
LDFLAGS =
INCLUDE = -I$(HDRDIR)/
EXEC	= Hensei

SRC	= $(wildcard $(SRCDIR)/*.cpp)
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
	-@rm -f $(OBJ)
	-@rm -f $(BINDIR)/$(EXEC)
	-@rm -f $(SRCDIR)/*[#~]
	-@rm -f $(OBJDIR)/*[#~]

makedirs:
	-@mkdir $(OBJDIR)
	-@mkdir $(BINDIR)
