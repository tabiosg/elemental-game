
CXX ?= g++
CXXFLAGS ?= -Wall -Werror -pedantic --std=c++11 -g

play: src/Element.cpp src/Weapon.cpp src/Fighter.cpp src/Team.cpp src/Brawl.cpp src/World.cpp
	g++ src/Element.cpp src/Weapon.cpp src/Fighter.cpp src/Team.cpp src/Brawl.cpp src/World.cpp -o world.exe
	./world.exe

# disable built-in rules
.SUFFIXES:

# these targets do not create any files
.PHONY: clean
clean:
	rm -vrf *.o *.exe *.gch *.dSYM *.stackdump *.out