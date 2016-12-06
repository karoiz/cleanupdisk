CC=gcc
CFLAGS=-Wall -O2 -std=c99
LIBS=
PROGRAM=cleanupdisk
FILES=$(PROGRAM).o

all: $(FILES)
	$(CC) -o $(PROGRAM) $(FILES) $(LIBS)

clean:
	rm -rf $(PROGRAM) $(FILES)
