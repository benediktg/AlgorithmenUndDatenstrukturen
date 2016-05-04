CC=gcc
CFLAGS=-Wall -std=c99 -pedantic

debug:clean
	$(CC) $(CFLAGS) -g -o ha1_381165 main.c
stable:clean
	$(CC) $(CFLAGS) -o ha1_381165 main.c
clean:
	rm -vfr *~ ha1_381165
plot:
	gnuplot config.plt