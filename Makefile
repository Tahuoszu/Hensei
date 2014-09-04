export CC      = g++
export CFLAGS  = -W -Wall -pedantic -g
export LDFLAGS =
export EXEC    = main

HENSEI	= hensei
ORCHID	= orchids
SEGMEN	= segmentation
TSKM	= tskm
EXECUT	= executable

CLEAN	= clean
MKDIR	= makedirs

all: $(EXEC)
	@(cp $(HENSEI)/bin/Hensei $(EXECUT))
	@(cp $(ORCHID)/bin/Analysis $(EXECUT))
	@(cp $(SEGMEN)/bin/Segmentation $(EXECUT))
	@(cp $(TSKM)/bin/tskm $(EXECUT))

$(EXEC):
	@(cd $(HENSEI) && $(MAKE))
	@(cd $(ORCHID) && $(MAKE))
	@(cd $(SEGMEN) && $(MAKE))
	@(cd $(TSKM)   && $(MAKE))

$(CLEAN):
	@(cd $(HENSEI) && $(MAKE) $(CLEAN))
	@(cd $(ORCHID) && $(MAKE) $(CLEAN))
	@(cd $(SEGMEN) && $(MAKE) $(CLEAN))
	@(cd $(TSKM)   && $(MAKE) $(CLEAN))