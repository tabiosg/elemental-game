#ifndef BRAWL_H
#define BRAWL_H
/* Brawl.h
 *
 * Brawl
 *
 * by Guthrie Tabios
 * tabiosg
 * 2021-04-01
 */

#include "Element.h"
#include "Team.h"
#include "Weapon.h"
#include "Brawl.h"
#include <string>
#include <vector>

class Brawl
{
public:
	Brawl(const Team teamZero, const Team teamOne);

	// EFFECTS start the entire brawl until one team loses all members.
	void startBrawl();

	// EFFECTS return team one
	const Team getTeamZero() const;

	// EFFECTS return team two
	const Team getTeamOne() const;

	// EFFECTS return team two
	std::vector<Weapon *> getAllDroppedWeapons();

	// REQUIRES 0 <= k < totalDroppedWeapons
	// EFFECTS return kth dropped weapon
	Weapon *getDroppedWeaponK(const int &k);

	// REQUIRES 0 <= k < totalDroppedWeapons
	// EFFECTS remove kth dropped weapon
	void removeDroppedWeaponK(const int &k);

	// EFFECTS add dropped weapon
	void addDroppedWeapon(const Weapon *weapon);

	// REQUIRES fighter has an element and fighter must be in combat
	// If player wants to pick up weapon, make sure that there are droppedWeapons.
	// MODIFIES action and target
	// EFFECTS  Ask if fighter wants to attack or heal or grab weapon or skip turn. Do action.
	void requestAndEnactAction(Fighter *f, Team &allies, Team &opponents);

	// REQUIRES fighter health drops to zero
	// EFFECTS if fighter exits combat, change dropped weapons
	void fighter_exits_combat(Fighter *fighter);

	// EFFECTS Prints droppedWeapons to stream as "Dropped Weapon 1: Excalibur"
	// followed by newline and then "Dropped Weapon 2: Gate of Babylon"
	std::ostream &printDroppedWeapons(std::ostream &os) const;

	// EFFECTS delete all dropped weapons
	~Brawl();

private:
	Team teamZero;
	Team teamOne;
	std::vector<Weapon *> droppedWeapons;
	int totalDroppedWeapons;
	int teamZeroTurn;
	int teamOneTurn;
	bool isTeamZeroTurn;
};

#endif
