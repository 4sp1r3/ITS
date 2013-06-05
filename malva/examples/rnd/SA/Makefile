MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: MainSeq MainLan

clean:
	rm -f MainLan MainSeq MainWan *.o *% *~

MainLan: SA.req.o SA.pro.o StopCondition.o MainLan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainWan: SA.req.o SA.pro.o StopCondition.o MainWan.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainSeq: SA.req.o SA.pro.o StopCondition.o MainSeq.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

LAN:
	mpirun -v -p4pg pgfileLan MainLan

WAN:
	mpirun -v -p4pg pgfileWan MainWan

SEQ:
	./MainSeq SA.cfg instances/rnd149.txt rnd149.sa.seq.txt
