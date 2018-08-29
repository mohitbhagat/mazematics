CXX = g++
CXXFLAGS = -std=c++14 -Wextra -Wpedantic -Wall -Werror=vla
LINKER_FLAGS = -lSDL2 -lSDL2_image
EXEC = maze
OBJECTS = main.o game.o grid.o cell.o puzzles.o graphicaldisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} ${LINKER_FLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}
