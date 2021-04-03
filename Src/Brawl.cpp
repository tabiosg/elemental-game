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
#include <cassert>

class Brawl {
public:
	Brawl(const Team given_team1, const Team given_team2) : team1(given_team1),
		team2(given_team2), total_dropped_weapons(0), team_1_turn(0),
		team_2_turn(0), is_team_1_turn(true) {
	}

	//EFFECTS start the entire brawl until one team loses all members.
	void startBrawl() {
		team1.enter_brawl();
		team2.enter_brawl();
		int team1_size = team1.get_in_combat_size();
		int team2_size = team2.get_in_combat_size();
		assert(team1_size != 0 && team2_size != 0);
		while (team1_size != 0 && team2_size != 0) {
			team1_size = team1.get_in_combat_size();
			team2_size = team2.get_in_combat_size();
			if (team_1_turn >= team1_size) {
				team_1_turn = 0;
			}
			if (team_2_turn >= team2_size) {
				team_2_turn = 0;
			}
			
			Fighter* current_fighter;
			if (is_team_1_turn) {
				current_fighter = team1.get_kth_in_combat_fighter(team_1_turn);
				request_and_enact_action(current_fighter, team1, team2);
				++team_1_turn;
			}
			else {
				current_fighter = team2.get_kth_in_combat_fighter(team_2_turn);
				request_and_enact_action(current_fighter, team2, team1);
				++team_2_turn;
			}
		}
		team1_size = team1.get_in_combat_size();
		team2_size = team2.get_in_combat_size();
		if (team1_size == 0) {
			std::cout << "Team 1 wins!" << std::endl;
		}
		else {
			std::cout << "Team 2 wins!" << std::endl;
		}
		team1.exit_brawl();
		team2.exit_brawl();
	}

	//EFFECTS return team one
	const Team get_team_one() const {
		return team1;
	}

	//EFFECTS return team two
	const Team get_team_two() const {
		return team2;
	}

	//REQUIRES 0 <= k < total_dropped_weapons
	//EFFECTS return kth dropped weapon
	Weapon* get_kth_dropped_weapon(const int& k) {
		assert(0 <= k && k < total_dropped_weapons);
		return dropped_weapons[k];
	}

	//REQUIRES 0 <= k < total_dropped_weapons
	//EFFECTS remove kth dropped weapon
	void remove_kth_dropped_weapon(const int& k) {
		assert(0 <= k && k < total_dropped_weapons);
		--total_dropped_weapons;
		delete dropped_weapons[k];
		dropped_weapons.erase(dropped_weapons.begin() + k);
	}

	//EFFECTS add dropped weapon
	void add_dropped_weapon(const Weapon* weapon) {
		++total_dropped_weapons;
		Weapon* added_weapon = Weapon_factory(weapon);
		dropped_weapons.push_back(added_weapon);
	}

	//REQUIRES fighter has an element and fighter must be in combat
	//If player wants to pick up weapon, make sure that there are dropped_weapons.
	//MODIFIES action and target
	//EFFECTS  Ask if fighter wants to attack or heal or grab weapon or skip turn. Do action.
	void request_and_enact_action(Fighter* f, Team& allies, Team& opponents) {
		std::string response = f->request_action(*this);
		if (response == "attack") {
			int target = f->go_attack(opponents);
			Fighter* defender = opponents.get_kth_in_combat_fighter(target);
			if (defender->get_current_health() == 0) {
				std::cout << *defender << " has exited the combat due to lack of health." << std::endl;
				fighter_exits_combat(defender);
			}
		}
		else if (response == "heal") {
			f->go_heal(allies);
		}
		else if (response == "grab") {
			f->go_grab_weapon(allies, opponents, *this);
		}
		else if (response == "skip") {
			std::cout << *f << " skips their turn." << std::endl;
		}
	}

	//REQUIRES fighter health drops to zero
	//EFFECTS if fighter exits combat, change dropped weapons
	void fighter_exits_combat(Fighter* fighter) {
		assert(fighter->get_current_health() == 0);
		fighter->exit_combat();
		int active_weapon = fighter->get_active_weapon();
		Weapon* copied_weapon = fighter->get_k_weapon(active_weapon);
		Weapon* dropped_weapon = Weapon_factory(copied_weapon);
		add_dropped_weapon(dropped_weapon);
	}

	//EFFECTS Prints dropped_weapons to stream as "Dropped Weapon 1: Excalibur" 
	//followed by newline and then "Dropped Weapon 2: Gate of Babylon"
	std::ostream& print_dropped_weapons(std::ostream& os) const {
		for (int i = 0; i < total_dropped_weapons; ++i) {
			os << "Dropped Weapon " << i + 1 << ": " << *dropped_weapons[i] << std::endl;
		}
		return os;
	}

	//EFFECTS delete all dropped weapons
	~Brawl() {
		while (total_dropped_weapons != 0){
			remove_kth_dropped_weapon(0);
		}
	}

private:
	Team team1;
	Team team2;
	std::vector<Weapon*> dropped_weapons;
	int total_dropped_weapons;
	int team_1_turn;
	int team_2_turn;
	bool is_team_1_turn;
};