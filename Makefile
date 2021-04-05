
all: Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp
	g++ Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp -o World

game: Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp
	g++ Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp -o World

element: Element.cpp
	g++ Element.cpp -o world.exe

weapon: Element.cpp Weapon.cpp
	g++ Element.cpp Weapon.cpp -o world.exe

fighter: Element.cpp Weapon.cpp Fighter.cpp
	g++ Element.cpp Weapon.cpp Fighter.cpp -o world.exe

team: Element.cpp Weapon.cpp Fighter.cpp Team.cpp
	g++ Element.cpp Weapon.cpp Fighter.cpp Team.cpp -o world.exe

brawl: Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp
	g++ Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp -o world.exe

world: Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp
	g++ Element.cpp Weapon.cpp Fighter.cpp Team.cpp Brawl.cpp World.cpp -o world.exe

clean:
	rm -rvf *.exe *~ *.out *.dSYM *.stackdump