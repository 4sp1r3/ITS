MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: MainSeq MainLan

clean:
	rm -f MainLan MainSeq MainWan *.o *% *~

MainSeq: CHC.req.o CHC.pro.o MainSeq.o
	g++ $(LDFLAGS) -lstdc++ $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainLan: CHC.req.o CHC.pro.o MainLan.o
	g++ $(LDFLAGS) -lstdc++ $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainWan: CHC.req.o CHC.pro.o MainWan.o
	g++ $(LDFLAGS) -lstdc++ $^ $(LOADLIBES) $(CPPFLAGS) -o $@

LAN:
	mpirun -v -p4pg pgfileLan MainLan

WAN:
	mpirun -v -p4pg pgfileWan MainWan

SEQ:
	./MainSeq CHC.cfg instances/sat1.txt sat1.chc.seq.txt