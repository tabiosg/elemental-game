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

class Brawl {
public:
	Brawl();

	Brawl(const Team team1, const Team team2);

	//EFFECTS start the entire brawl until one team loses all members.
	void startBrawl();

	//EFFECTS return team one
	const Team get_team_one() const;

	//EFFECTS return team two
	const Team get_team_two() const;

	//EFFECTS return kth dropped weapon
	Weapon* get_kth_dropped_weapon(const int& k);

	//EFFECTS remove kth dropped weapon
	void remove_kth_dropped_weapon(const int& k);

	//EFFECTS add dropped weapon
	void add_dropped_weapon(const int& k);

	//REQUIRES fighter has an element and fighter must be in combat
	//If player wants to pick up weapon, make sure that there are dropped_weapons.
	//MODIFIES action and target
	//EFFECTS  Ask if fighter wants to attack or heal or grab weapon or skip turn. Do action.
	void request_and_enact_action();

	//EFFECTS Enact action requested by fighter
	//make sure to adjust for elemental interactions.
	bool enact_action(const std::string& action);

	//EFFECTS if fighter exits combat, change dropped weapons
	void fighter_exits_combat();

	//EFFECTS Prints dropped_weapons to stream as "Dropped Weapon 1: Excalibur" 
	//followed by newline and then "Dropped Weapon 2: Gate of Babylon"
	std::ostream& print_dropped_weapons(std::ostream& os) const;

	//EFFECTS delete all dropped weapons
	~Brawl();

private:
	Team team1;
	Team team2;
	std::vector<Weapon*> dropped_weapons;
	int total_dropped_weapons;
	int team_1_turn;
	int team_2_turn;
	int team_turn;
};

#endif