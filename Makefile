CFLAGS+=-Wall -ggdb3 -std=gnu99


.PHONY: all clean clean-rabin

all: fastrabin

rabin.o: rabin.c rabin.h

fastrabin: main.o rabin.o
	$(CC) $(CFLAGS) -o $@ $^

clean: clean-rabin

clean-rabin:
	rm -f rabin.o main.o fastrabin
