
CXX ?= g++
CXXFLAGS ?= -Wall -Werror -pedantic --std=c++11 -g

play: Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp
	g++ Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp -o world.exe
	./world.exe

world.exe: Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp
	$(CXX) $(CXXFLAGS) Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp -o $@

world: Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp
	g++ Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp -o world.exe

# disable built-in rules
.SUFFIXES:

# these targets do not create any files
.PHONY: clean
clean:
	rm -vrf *.o *.exe *.gch *.dSYM *.stackdump *.out