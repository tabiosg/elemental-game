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

	Fighter* Guthrie = Fighter_factory("Guthrie", Element(Element::ELE_FIRE),
		Weapon::WEAPON_CROSS, Fighter::FIGHTER_HUMAN);
	Fighter* Bob = Fighter_factory("Bob", Element(Element::ELE_FIRE),
		Weapon::WEAPON_STAFF, Fighter::FIGHTER_WARRIOR);

	Team GuthrieTeam;
	Team BobTeam;

	Brawl myBrawl(GuthrieTeam, BobTeam);
	myBrawl.startBrawl();

}