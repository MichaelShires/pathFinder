all: pathFinder

pathFinder: pathFinder.o
	g++ -g pathFinder.cpp -o pathFinder

clean:
	rm -rf *.o pathFinder *~
