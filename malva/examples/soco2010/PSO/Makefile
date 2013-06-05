MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: clean MainSeq MainLan

clean:
	rm -f  MainLan MainSeq MainWan core.* *.o *% *~ *.out

MainSeq: MainSeq.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -lm -o $@

MainLan: MainLan.o
	 g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -lgcj -o $@

MainWan: MainWan.o
	 g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

LAN:
	mpirun -v -p4pg pgfileLan MainLan

WAN:
	mpirun -v -p4pg pgfileWan MainWan

SEQ:
	./MainSeq PSO.cfg 500 19 results.txt # execution order, config file, problem dimension, number of SOCO 2010 function, results file