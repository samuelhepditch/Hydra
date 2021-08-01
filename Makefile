CXX=g++
CXXFLAGS=-std=c++14 -MMD
OBJECTS=main.o gameplay.o deck.o player.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=hydra

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
