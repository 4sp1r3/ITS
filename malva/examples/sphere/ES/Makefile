MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: MainLan MainSeq

clean:
	rm -f MainLan MainSeq MainWan *.o *% *~

MainLan: ES.req.o ES.pro.o MainLan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainWan: ES.req.o ES.pro.o MainWan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainSeq: ES.req.o ES.pro.o MainSeq.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

LAN:
	mpirun -v -p4pg pgfileLan MainLan
WAN:
	mpirun -v -p4pg pgfileWan MainWan

SEQ:
	./MainSeq ES.cfg instances/SPH20.txt sph20.es.seq.txt