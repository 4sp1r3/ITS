MALVA_DIR = ../../..
include $(MALVA_DIR)/environment

all: MainSeq

clean:
	rm -f MainSeq *.o *~

MainSeq: newGA.req.o newGA.pro.o MainSeq.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

SEQ:
	./MainSeq config.dat instances/nodes.in nodes.out
