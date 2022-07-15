#include <string>
#include <vector>
#include <cassert>

#include "Brawl.h"
#include "Team.h"
#include "Weapon.h"

Brawl::Brawl(
	Team givenTeamZero,
	Team givenTeamOne)
	: teamZero(givenTeamZero),
	  teamOne(givenTeamOne),
	  totalDroppedWeapons(0),
	  teamZeroTurn(0),
	  teamOneTurn(0),
	  isTeamZeroTurn(true)
{
}

// EFFECTS start the entire brawl until one team loses all members.
void Brawl::startBrawl()
{
	teamZero.enterBrawl();
	teamOne.enterBrawl();
	std::cout << "Team 0 has entered the brawl! Here are its members:" << std::endl;
	teamZero.printAllFighters(std::cout);
	std::cout << std::endl;
	std::cout << "Team 1 has entered the brawl! Here are its members:" << std::endl;
	teamOne.printAllFighters(std::cout);
	std::cout << std::endl;

	int teamZeroSize = teamZero.getInCombatSize();
	int teamOneSize = teamOne.getInCombatSize();
	assert(teamZeroSize != 0 && teamOneSize != 0);
	while (teamZeroSize != 0 && teamOneSize != 0)
	{

		std::string dummy;
		std::cout << std::endl
				  << "Type anything to see the next move. ";
		std::cin >> dummy;
		std::cout << std::endl
				  << "\033[2J"
				  << "\033[1;1H";

		Fighter *currentFighter;

		if (isTeamZeroTurn)
		{
			std::cout << "Team 0 will send out its fighter! " << std::endl
					  << std::endl;
			currentFighter = teamZero.getFighterK(teamZeroTurn);
			requestAndEnactAction(currentFighter, teamZero, teamOne);
			++teamZeroTurn;
			isTeamZeroTurn = false;
		}

		else
		{
			std::cout << "Team 1 will send out its fighter! " << std::endl
					  << std::endl;
			currentFighter = teamOne.getFighterK(teamOneTurn);
			requestAndEnactAction(currentFighter, teamOne, teamZero);
			++teamOneTurn;
			isTeamZeroTurn = true;
		}
		teamZeroSize = teamZero.getInCombatSize();
		teamOneSize = teamOne.getInCombatSize();

		if (teamZeroTurn >= teamZeroSize)
		{
			teamZeroTurn = 0;
		}
		if (teamOneTurn >= teamOneSize)
		{
			teamOneTurn = 0;
		}

		std::cout << "This is Team 0 and its members now:" << std::endl;
		teamZero.printAllFighters(std::cout);
		std::cout << std::endl;
		std::cout << "This is Team 1 and its members now:" << std::endl;
		teamOne.printAllFighters(std::cout);
	}
	teamZeroSize = teamZero.getInCombatSize();
	teamOneSize = teamOne.getInCombatSize();
	if (teamZeroSize == 0)
	{
		std::cout << "Team 0 wins!" << std::endl
				  << std::endl;
	}
	else
	{
		std::cout << "Team 1 wins!" << std::endl
				  << std::endl;
	}
	teamZero.exitBrawl();
	teamOne.exitBrawl();
}

// EFFECTS return team one
const Team Brawl::getTeamZero() const
{
	return teamZero;
}

// EFFECTS return team two
const Team Brawl::getTeamOne() const
{
	return teamOne;
}

// EFFECTS return team two
std::vector<Weapon *> Brawl::getAllDroppedWeapons()
{
	return droppedWeapons;
}

// REQUIRES 0 <= k < totalDroppedWeapons
// EFFECTS return kth dropped weapon
Weapon *Brawl::getDroppedOfWeaponK(const int &k)
{
	assert(0 <= k && k < totalDroppedWeapons);
	return droppedWeapons[k];
}

// REQUIRES 0 <= k < totalDroppedWeapons
// EFFECTS remove kth dropped weapon
void Brawl::removeDroppedOfWeaponK(const int &k)
{
	assert(0 <= k && k < totalDroppedWeapons);
	--totalDroppedWeapons;
	delete droppedWeapons[k];
	droppedWeapons.erase(droppedWeapons.begin() + k);
}

// EFFECTS add dropped weapon
void Brawl::addDroppedWeapon(const Weapon *weapon)
{
	++totalDroppedWeapons;
	Weapon *addedWeapon = WeaponFactory(weapon);
	droppedWeapons.push_back(addedWeapon);
}

// REQUIRES fighter has an element and fighter must be in combat
// If player wants to pick up weapon, make sure that there are droppedWeapons.
// MODIFIES action and target
// EFFECTS  Ask if fighter wants to attack or heal or grab weapon or skip turn. Do action.
void Brawl::requestAndEnactAction(Fighter *f, Team &allies, Team &opponents)
{
	std::cout << "It is " << *f << "'s turn." << std::endl
			  << std::endl;

	std::vector<Fighter *> allOpponents = opponents.getAllFighters();
	std::vector<Fighter *> allAllies = allies.getAllFighters();

	std::string response = f->requestAction(allAllies, allOpponents, droppedWeapons);
	if (response == "Attack")
	{
		int target = f->goAttack(allOpponents);
		Fighter *defender = opponents.getFighterK(target);
		if (defender->getCurrentHealth() == 0)
		{
			std::cout << *defender << " has exited the combat due to lack of health." << std::endl
					  << std::endl;
			int droppedIndex = defender->getActiveWeapon();
			Weapon *droppedWeapon = defender->getOfWeaponK(droppedIndex);
			std::cout << *defender << " has dropped the " << *droppedWeapon << "." << std::endl
					  << std::endl;
			addDroppedWeapon(droppedWeapon);
			opponents.memberExitsCombat(target);
		}
	}
	else if (response == "Heal")
	{
		f->goHeal(allAllies);
	}
	else if (response == "Grab")
	{
		int target = f->goGrabWeapon(droppedWeapons);
		removeDroppedOfWeaponK(target);
	}
	else if (response == "Skip")
	{
		std::cout << *f << " skips their turn." << std::endl
				  << std::endl;
	}
}

// REQUIRES fighter health drops to zero
// EFFECTS if fighter exits combat, change dropped weapons
void Brawl::fighterExitsCombat(Fighter *fighter)
{
	assert(fighter->getCurrentHealth() == 0);
	fighter->exitCombat();
	int activeWeapon = fighter->getActiveWeapon();
	Weapon *copiedWeapon = fighter->getOfWeaponK(activeWeapon);
	addDroppedWeapon(copiedWeapon);
}

// EFFECTS Prints droppedWeapons to stream as "Dropped Weapon 1: Excalibur"
// followed by newline and then "Dropped Weapon 2: Gate of Babylon"
std::ostream &Brawl::printDroppedWeapons(std::ostream &os) const
{
	for (int i = 0; i < totalDroppedWeapons; ++i)
	{
		os << "Dropped Weapon " << i + 1 << ": " << *droppedWeapons[i] << std::endl;
	}
	return os;
}

// EFFECTS delete all dropped weapons
Brawl::~Brawl()
{
	while (totalDroppedWeapons != 0)
	{
		removeDroppedOfWeaponK(0);
	}
}
