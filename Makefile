flags=-O2 -Wall -std=c2x
ldflags=-lws2_32

all: clean cache run

cache: cache.o
	gcc ${flags} $^ -o $@ ${ldflags}

cache.o: cache.c
	gcc ${flags} -c $^

run:
	@cls
	@.\cache.exe 1567

clean:
	del /Q *.o cache.exe
