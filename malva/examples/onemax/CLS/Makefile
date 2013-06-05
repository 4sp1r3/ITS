MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

BASE    = SA
APP     = onemax
CPPFLAGS	= -I$(MALLBA_INC) -O -Wno-deprecated -g -I$(MALLBA_REP)/$(BASE)/$(APP)/

all: clean Main.seq

clean:
	rm -f *.o *% *~ core Main.seq

Main.seq: Main.o CLS.pro.o CLS.req.o $(MALLBA_REP)/$(BASE)/$(APP)/$(BASE).pro.o $(MALLBA_REP)/$(BASE)/$(APP)/$(BASE).req.o $(MALLBA_REP)/$(BASE)/$(APP)/StopCondition.o

	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

SEQ: Main.seq
	 Main.seq CLS.cfg instances/onemax10.txt  res10.txt