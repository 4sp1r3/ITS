MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: MainLan MainWan MainSeq

clean:
	rm -f MainLan MainSeq MainWan *.o *% *~

MainLan: SA.req.o SA.pro.o newGA.req.o newGA.pro.o newGASA.req.o newGASA.pro.o MainLan.o StopCondition.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainWan: SA.req.o SA.pro.o newGA.req.o newGA.pro.o newGASA.req.o newGASA.pro.o MainWan.o StopCondition.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainSeq: SA.req.o SA.pro.o newGA.req.o newGA.pro.o newGASA.req.o newGASA.pro.o MainSeq.o StopCondition.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

LAN:
	mpirun -v -p4pg pgfileLan1 MainLan

WAN:
	mpirun -v -p4pg pgfileWan1 MainWan

SEQ_1:
	./MainSeq