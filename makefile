#setting consts

CC = gcc
FILENAME = ducky



all:
	${CC} -o ${FILENAME} ./src/${FILENAME}.c
clean:
	rm -rf ./bin/*.o ./*.o