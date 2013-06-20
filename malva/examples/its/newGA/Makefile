MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: MainSeq

clean:
	rm -f MainSeq *.o *~

# newGA.req.o 

MainSeq: newGA.pro.o MainSeq.o problem.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

SEQ:
	./MainSeq config.dat instances/nodes.in nodes.out
