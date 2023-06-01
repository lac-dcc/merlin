CC = g++
SRC = src
INCLUDE = include
OBJ = obj
BIN = bin
EXE = ${BIN}/main

${BIN}/main: ${OBJ}/PolynomialInterpolation.o ${OBJ}/main.o 
	@mkdir -p ./bin
	$(CC) -g -Wall ${OBJ}/* -o ${BIN}/main

${OBJ}/PolynomialInterpolation.o: ${SRC}/PolynomialInterpolation.cpp
	@mkdir -p ./obj
	$(CC) -c ${SRC}/PolynomialInterpolation.cpp -I ${INCLUDE} -o ${OBJ}/PolynomialInterpolation.o

${OBJ}/main.o: ${SRC}/main.cpp
	$(CC) -c ${SRC}/main.cpp -I ${INCLUDE} -o ${OBJ}/main.o

clean:
	@rm -rf ${OBJ} ${BIN}
