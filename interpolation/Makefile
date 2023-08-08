CC = g++
SRC = src
INCLUDE = include
OBJ = obj
BIN = bin
EXE = ${BIN}/main

${BIN}/main: ${OBJ}/interpolator.o ${OBJ}/main.o 
	@mkdir -p ./bin
	$(CC) ${OBJ}/* -o ${BIN}/main

${OBJ}/interpolator.o: ${SRC}/interpolator.cpp
	@mkdir -p ./obj
	$(CC) -c ${SRC}/interpolator.cpp -I ${INCLUDE} -o ${OBJ}/interpolator.o

${OBJ}/main.o: ${SRC}/main.cpp
	$(CC) -c ${SRC}/main.cpp -I ${INCLUDE} -o ${OBJ}/main.o

clean:
	@rm -rf ${OBJ} ${BIN}
