MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: MainLan MainSeq

clean:
	rm -f MainLan MainSeq MainWan *.o *% *~

MainLan: aco.pro.o aco.req.o MainLan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainWan: aco.pro.o aco.req.o MainWan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainSeq: aco.pro.o aco.req.o MainSeq.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

LAN:
	mpirun -v -p4pg pgfileLan MainLan

WAN:
	mpirun -v -p4pg pgfileWan MainWan

SEQ:
	./MainSeq aco.cfg instances/ftv70.atsp atsp.aco.seq.txt