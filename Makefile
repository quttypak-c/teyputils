CC = gcc
all: cat
cat: src/cat.c
	$(CC) -O2 -s src/cat.c -o cat
clean:
	rm -rf cat src/*.o