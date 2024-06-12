# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

all	: bin/cb
	@echo -n ""

bin/cb : cyclebreaker_opt.o main_opt.o lib
	$(CC) $(OPTFLAGS)  cyclebreaker_opt.o main_opt.o -ltm_usage -Llib  -o bin/cb
main_opt.o : src/main.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $< -Ilib -o $@
cyclebreaker_opt.o	: src/cyclebreaker.cpp src/cyclebreaker.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<


# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a bin/* lib/*.o

