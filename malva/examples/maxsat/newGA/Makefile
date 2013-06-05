MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: MainLan MainSeq

clean:
	rm -f MainLan MainSeq MainWan *.o *% *~

MainLan: newGA.req.o newGA.pro.o MainLan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainWan: newGA.req.o newGA.pro.o MainWan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainSeq: newGA.req.o newGA.pro.o MainSeq.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

LAN:
	mpirun -v -p4pg pgfileLan MainLan

WAN:
	mpirun -v -p4pg pgfileWan MainWan

SEQ:
	./MainSeq newGA.cfg instances/sat1.txt sat1.newga.seq.txt