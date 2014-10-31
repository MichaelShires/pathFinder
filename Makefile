all: pathFinder

pathFinder: pathFinder.c
	gcc -std=c99 pathFinder.c -o pathFinder

clean:
	rm -rf *.o pathFinder *~
