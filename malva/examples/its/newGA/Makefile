MALVA_DIR = ..
include $(MALVA_DIR)/environment

all: main

clean:
	rm -f triangulationn *.o *~

main: newGA.req.o newGA.pro.o main.o
	g++ $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

run:
	./main config.dat instances/nodes.in nodes.out