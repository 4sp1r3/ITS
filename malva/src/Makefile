MALVA_DIR=..
include $(MALVA_DIR)/environment

OBJS = States.o netstream.o
LIB = libmallba.a

all: $(OBJS) $(LIB)


%.o : %.cc
	$(CXX) -c $(CPPFLAGS) $< -o $@

	
clean:
	rm -f *.o *~ *% 
	rm -f $(OBJS) $(LIB)

$(LIB): $(OBJS)
	ar -r $(LIB) $(OBJS)
	ranlib $(LIB)
	cp $(LIB) $(MALVA_LIB)

