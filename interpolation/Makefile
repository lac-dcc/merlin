SRC:= src
ICL:= include
OBJ:= obj
BIN:= bin
EXE:= ${BIN}/main

${BIN}/main: ${OBJ}/PolynomialInterpolation.o ${OBJ}/main.o 
	c++ -g -pg -Wall ${OBJ}/* -o ${BIN}/main

${OBJ}/PolynomialInterpolation.o: ${SRC}/PolynomialInterpolation.cpp
	c++ -c ${SRC}/PolynomialInterpolation.cpp -I ${ICL} -o ${OBJ}/PolynomialInterpolation.o

${OBJ}/main.o: ${SRC}/main.cpp
	c++ -c ${SRC}/main.cpp -I ${ICL} -o ${OBJ}/main.o

clean:
	rm ${OBJ}/* ${BIN}/*