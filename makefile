all:
	gcc -o ./bin/duck.o ./src/duck.c

run:
	./bin/duck
clean:
	rm -rf ./bin/*.*