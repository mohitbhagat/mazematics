CXX = g++
CXXFLAGS = -std=c++14 -Wextra -Wpedantic -Wall -Werror=vla -MMD -g
EXEC = maze
OBJECTS = main.o game.o grid.o cell.o puzzles.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}
