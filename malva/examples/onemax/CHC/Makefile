MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: MainSeq MainLan

clean:
	rm -f MainLan MainSeq *.o *% *~

MainSeq: CHC.req.o CHC.pro.o MainSeq.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainLan: CHC.req.o CHC.pro.o MainLan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainWan: CHC.req.o CHC.pro.o MainWan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

LAN:
	mpirun -np 10 ./MainLan Config.cfg

WAN:
	mpirun -v -p4pg pgfileWan MainWan

SEQ:
	./MainSeq CHC.cfg instances/onemax10.txt sol.txt