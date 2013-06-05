MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: MainSeq  MainLan MainWan

clean:
	rm -f MainLan MainSeq MainWan *.o *% *~

MainSeq: PSO.req.o PSO.pro.o MainSeq.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainLan: PSO.req.o PSO.pro.o MainLan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainWan: PSO.req.o PSO.pro.o MainWan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

LAN:
	mpirun -v -p4pg pgfileLan MainLan

WAN:
	mpirun -v -p4pg pgfileWan MainWan

SEQ:
	./MainSeq PSO.cfg instances/onemax10.txt om10.newga.seq.txt