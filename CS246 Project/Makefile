CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = bb7k
OBJECTS = main.o building.o controller.o coopfee.o game.o goosenesting.o gototims.o gym.o needleshall.o osap.o ownable.o player.o residence.o slc.o timsline.o tuition.o view.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
