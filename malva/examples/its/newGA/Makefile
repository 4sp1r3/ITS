MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: MainSeq

MainSeq: newGA.pro.o MainSeq.o operators.o problem.o solution.o stats.o stop.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

SEQ:
	./MainSeq config.dat instances/nodes.in nodes.out

clean:
	rm -f MainSeq *.o *~