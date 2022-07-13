#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <vector>

#include "header/Brawl.h"
#include "header/Element.h"
#include "header/Fighter.h"
#include "header/Team.h"
#include "header/Weapon.h"

class Game
{
public:
};

int main()
{
	std::cout << std::endl
			  << "\033[2J"
			  << "\033[1;1H";
	std::string name1, name2, name3;

	std::cout << "Welcome to this game! You are a metal-type fighter. What is your name?" << std::endl;
	std::cin >> name1;

	Fighter *fighter1;
	while (true)
	{
		std::cout << "Would you like a staff, cross, or a spear? Please enter \"Staff\", \"Cross\", or \"Spear\"." << std::endl;
		std::string response;
		std::cin >> response;
		if (response == "Staff")
		{
			fighter1 = Fighter_factory(name1, Element(Element::ELE_METAL),
									   Weapon::WEAPON_STAFF, Fighter::FIGHTER_HUMAN);
			break;
		}
		if (response == "Cross")
		{
			fighter1 = Fighter_factory(name1, Element(Element::ELE_METAL),
									   Weapon::WEAPON_CROSS, Fighter::FIGHTER_HUMAN);
			break;
		}
		if (response == "Spear")
		{
			fighter1 = Fighter_factory(name1, Element(Element::ELE_METAL),
									   Weapon::WEAPON_SPEAR, Fighter::FIGHTER_HUMAN);
			break;
		}
		std::cout << "You did not put in a valid output. Please try again. " << std::endl;
	}

	std::cout << std::endl
			  << "\033[2J"
			  << "\033[1;1H";

	std::cout << "A fire-type fighter and wood-type fighter ran up to you to form a party with you "
			  << "as the leader.";
	std::cout << "They both have spears! You gladly allow them to join your party. " << std::endl;

	std::cout << "Choose the name of the fire-type fighter." << std::endl;
	std::cin >> name2;
	std::cout << "Choose the name of the wood-type fighter." << std::endl;
	std::cin >> name3;

	Fighter *fighter2 = Fighter_factory(name2, Element(Element::ELE_FIRE),
										Weapon::WEAPON_SPEAR, Fighter::FIGHTER_WARRIOR);
	Fighter *fighter3 = Fighter_factory(name3, Element(Element::ELE_WOOD),
										Weapon::WEAPON_SPEAR, Fighter::FIGHTER_WARRIOR);

	Team GoodTeam;

	GoodTeam.add_member(fighter1);
	GoodTeam.add_member(fighter2);
	GoodTeam.add_member(fighter3);

	std::cout << std::endl
			  << "\033[2J"
			  << "\033[1;1H";

	std::cout << "Three enemies looking to start a fight showed up." << std::endl
			  << std::endl;
	std::cout << "You ask " << name1 << ", " << name2 << ", and " << name3 << " if they've heard of these enemies, but they have not! " << std::endl;
	std::cout << "The only thing you know about them is that they are all earth-type fighters. " << std::endl;
	std::cout << "One has a cross, one has a staff, and one has a spear." << std::endl;
	std::cout << "In order to lead your team to victory, you should first give the enemies some names." << std::endl;
	std::string name4, name5, name6;
	std::cout << std::endl
			  << "Choose the name of the first enemy." << std::endl;
	std::cin >> name4;
	std::cout << std::endl
			  << "Choose the name of the second enemy." << std::endl;
	std::cin >> name5;
	std::cout << std::endl
			  << "Choose the name of the third enemy." << std::endl;
	std::cin >> name6;

	Fighter *enemy1 = Fighter_factory(name4, Element(Element::ELE_EARTH),
									  Weapon::WEAPON_CROSS, Fighter::FIGHTER_WARRIOR);
	Fighter *enemy2 = Fighter_factory(name5, Element(Element::ELE_EARTH),
									  Weapon::WEAPON_STAFF, Fighter::FIGHTER_WARRIOR);
	Fighter *enemy3 = Fighter_factory(name6, Element(Element::ELE_EARTH),
									  Weapon::WEAPON_SPEAR, Fighter::FIGHTER_WARRIOR);

	Team EvilTeam;
	EvilTeam.add_member(enemy1);
	EvilTeam.add_member(enemy2);
	EvilTeam.add_member(enemy3);

	Brawl myBrawl(GoodTeam, EvilTeam);

	std::cout << std::endl
			  << "\033[2J"
			  << "\033[1;1H";

	std::cout << name4 << " threw a rock at your face, but you dodged it! Now your party is mad. " << std::endl;

	std::cout << "Now it's time to fight! Let the brawl begin!" << std::endl
			  << std::endl;

	myBrawl.startBrawl();

	delete fighter1;
	delete fighter2;
	delete fighter3;
	delete enemy1;
	delete enemy2;
	delete enemy3;
}
