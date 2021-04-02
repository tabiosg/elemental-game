/* Brawl.cpp
 *
 * Brawl
 *
 * by Guthrie Tabios
 * tabiosg
 * 2021-04-01
 */

#include "Brawl.h"

#include "Element.h"
#include "Team.h"
#include "Weapon.h"
#include <string>
#include <vector>

class Brawl {
public:
	Brawl() {

	}

	Brawl(const Team team1, const Team team2) {

	}

	//EFFECTS start the entire brawl until one team loses all members.
	void startBrawl() {

	}

	//REQUIRES fighter has an element and fighter must be in combat
	//If player wants to pick up weapon, make sure that there are dropped_weapons.
	//MODIFIES action and target
	//EFFECTS  Ask if fighter wants to attack or heal or grab weapon or skip turn. Do action.
	void request_and_enact_action() {

	}

	//REQUIRES fighter wants to attack
	//EFFECTS see who fighter wants to attack
	int request_attack_target() {

	}

	//REQUIRES fighter wants to heal
	//EFFECTS see who fighter wants to heal
	int request_heal_target() {

	}

	//REQUIRES fighter wants to heal or attack
	//EFFECTS see which weapon the fighter wants to use
	int request_heal_weapon() {

	}

	//REQUIRES fighter wants to grab and there are dropped weapons
	//EFFECTS see what weapon the fighter wants to grab
	int request_grab_target() {

	}

	//EFFECTS Enact action requested by fighter
	//make sure to adjust for elemental interactions.
	bool enact_action(const std::string& action) {

	}

	//EFFECTS if fighter exits combat, change dropped weapons
	void fighter_exits_combat() {

	}

	//EFFECTS Prints dropped_weapons to stream as "Dropped Weapon 1: Excalibur" 
	//followed by newline and then "Dropped Weapon 2: Gate of Babylon"
	std::ostream& print_dropped_weapons(std::ostream& os) {

	}

	//EFFECTS delete all dropped weapons
	~Brawl() {

	}

private:
	Team team1;
	Team team2;
	std::vector<Weapon*> dropped_weapons;
	int total_dropped_weapons;
	int team_1_turn;
	int team_2_turn;
	int team_turn;
};