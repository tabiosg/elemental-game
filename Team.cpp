/* Team.cpp
 *
 * Team
 *
 * by Guthrie Tabios
 * tabiosg
 * 2021-04-01
 */

#include "Team.h"

#include "Fighter.h"
#include <string>
#include <vector>
#include <cassert>
#include <numeric>

class Team {
public:
	Team() : total_size(0), in_brawl(false), in_combat_size(0) {
	}

	Team(const Team& other) {
		total_size = other.get_total_size();
		in_brawl = other.get_brawl_status();
		for (int i = 0; i < total_size; ++i) {
			Fighter* ithfighter = Fighter_factory(all_fighters[i]);
			all_fighters.push_back(ithfighter);
		}
		std::vector<Fighter*> all_fighters;

		int in_combat_size;
		std::vector<int> in_combat_fighters;
	}

	Team& operator=(const Team& rhs) {

	}

	//EFFECTS return total size of team
	int get_total_size() const {
		return total_size;
	}

	//EFFECTS return true if team is in brawl, returns false otherwise.
	bool get_brawl_status() const {
		return in_brawl;
	}

	//REQUIRES 0 < k <= in_combat_Fighters in team
	//EFFECTS return the kth  in_combat fighter.
	Fighter* get_kth_in_combat_fighter(const int& k) {
		return all_fighters[in_combat_fighters[k]];
	}

	//REQUIRES team is in combat
	//EFFECTS return true if all members are out of combat.
	bool all_members_died() const {
		assert(in_brawl);
		return in_combat_size == 0;
	}

	//EFFECTS Prints all fighters to stream as "Fighter 1: Alex" 
	//followed by newline and then "Fighter 2: Harry"
	std::ostream& print_all_fighters(std::ostream& os) {
		for (int i = 0; i < total_size; ++i) {
			os << "Fighter " << i + 1 << ": " << *all_fighters[i] << std::endl;
		}
		return os;
	}

	//REQUIRES team is in combat
	//EFFECTS return size of team in combat
	int get_in_combat_size() const {
		return in_combat_size;
	}

	//EFFECTS Prints in combat fighters to stream as "Fighter 1: Alex" 
	//followed by newline and then "Fighter 2: Harry"
	std::ostream& print_in_combat_fighters(std::ostream& os) const {
		for (int i = 0; i < in_combat_size; ++i) {
			Fighter* ithfighter = all_fighters[in_combat_fighters[i]];
			os << "Fighter " << i + 1 << ": " << *ithfighter << std::endl;
		}
		return os;
	}

	//REQUIRES team is not in combat
	//EFFECTS makes the team enter a brawl. changes in_combat_fighters
	void enter_brawl() {
		assert(!in_brawl);
		in_brawl = true;
		in_combat_size = total_size;
		std::vector<int> v(total_size);
		std::iota(std::begin(v), std::end(v), 0);
		in_combat_fighters = v;
		for (int i = 0; i < total_size; ++i) {
			all_fighters[i]->enter_combat();
		}
	}

	//REQUIRES team is in combat and member is exiting combat due to lack of health.
	// 0 <= k < in_combat_size. k represents kth person on team starting from 0.
	//EFFECTS makes a member exit combat
	//This changes in_combat_fighters
	//and changes in_combat_size.
	void member_exits_combat(const int& k) {
		assert(in_brawl);
		assert(0 <= k && k < in_combat_size);
		--in_combat_size;
	}

	//REQUIRES team is in combat
	//EFFECTS makes the team exit a brawl. 
	//changes in_combat_fighters and out_of_combat_fighters.
	void exit_brawl() {
		assert(in_brawl);
		in_brawl = false;
		in_combat_size = 0;
		in_combat_fighters.clear();
	}

	//REQUIRES team is not in combat and fighter is not in combat
	//EFFECTS add fighter to team
	void add_member(Fighter* fighter) {
		assert(!in_brawl);
		++total_size;
		all_fighters.push_back(fighter);
	}

	//REQUIRES team is not in combat
	//EFFECTS remove fighter from team
	void remove_member(int& fighter_index) {
		assert(!in_brawl);
		--total_size;
		all_fighters.erase(all_fighters.begin() + fighter_index);
	}

	~Team() {

	}

private:
	int total_size;
	bool in_brawl;
	std::vector<Fighter*> all_fighters;

	int in_combat_size;
	std::vector<int> in_combat_fighters;
};