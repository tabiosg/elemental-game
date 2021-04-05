#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <vector>

#include "Brawl.h"
#include "Element.h"
#include "Fighter.h"
#include "Team.h"
#include "Weapon.h"

class Game {
public:

};

int main() {

	Fighter* Heracles = Fighter_factory("HeraclesPlayer2000", Element(Element::ELE_METAL),
		Weapon::WEAPON_STAFF, Fighter::FIGHTER_HUMAN);
	Fighter* Aeneas = Fighter_factory("Aeneas", Element(Element::ELE_FIRE),
		Weapon::WEAPON_SPEAR, Fighter::FIGHTER_WARRIOR);
	Fighter* Perseus = Fighter_factory("Perseus", Element(Element::ELE_WOOD),
		Weapon::WEAPON_SPEAR, Fighter::FIGHTER_WARRIOR);

	Team GoodTeam;
	
	GoodTeam.add_member(Perseus);
	GoodTeam.add_member(Aeneas);
	GoodTeam.add_member(Heracles);

	Fighter* Hypnus = Fighter_factory("Hypnus", Element(Element::ELE_EARTH),
		Weapon::WEAPON_CROSS, Fighter::FIGHTER_WARRIOR);
	Fighter* Medusa = Fighter_factory("Medusa", Element(Element::ELE_EARTH),
		Weapon::WEAPON_STAFF, Fighter::FIGHTER_WARRIOR);
	Fighter* Cronus = Fighter_factory("Cronus", Element(Element::ELE_EARTH),
		Weapon::WEAPON_SPEAR, Fighter::FIGHTER_WARRIOR);
	
	Team EvilTeam;
	EvilTeam.add_member(Hypnus);
	EvilTeam.add_member(Medusa);
	EvilTeam.add_member(Cronus);

	Brawl myBrawl(GoodTeam, EvilTeam);

	myBrawl.startBrawl();


	delete Heracles;
	delete Aeneas;
	delete Perseus;
	delete Hypnus;
	delete Medusa;
	delete Cronus;

}