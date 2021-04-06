/* Team.cpp
 *
 * Team
 *
 * by Guthrie Tabios
 * tabiosg
 * 2021-04-01
 */
#include <string>
#include <vector>
#include <cassert>
#include <numeric>

#include "Team.h"

#include "Fighter.h"

Team::Team() : total_size(0), in_brawl(false) {
}

Team::Team(const Team& other) {
	total_size = other.get_total_size();
	in_brawl = other.get_brawl_status();
	for (int i = 0; i < total_size; ++i) {
		Fighter* copied_fighter = other.get_kth_fighter(i);
		Fighter* ithfighter = Fighter_factory(copied_fighter);
		all_fighters.push_back(ithfighter);
	}
}

Team& Team::operator=(const Team& rhs) {
	int one = 1;
	while (total_size != 0) {
		remove_member(one);
	}

	total_size = rhs.get_total_size();
	in_brawl = rhs.get_brawl_status();
	for (int i = 0; i < total_size; ++i) {
		Fighter* copied_fighter = rhs.get_kth_fighter(i);
		Fighter* ithfighter = Fighter_factory(copied_fighter);
		all_fighters.push_back(ithfighter);
	}
	std::vector<Fighter*> all_fighters;

	std::vector<int> in_combat_fighters;

	return *this;
}

//EFFECTS return total size of team
int Team::get_total_size() const {
	return total_size;
}

//EFFECTS return true if team is in brawl, returns false otherwise.
bool Team::get_brawl_status() const {
	return in_brawl;
}

//REQUIRES 0 < k <= total_fighters in team
//EFFECTS return the kth fighter fighter.
Fighter* Team::get_kth_fighter(const int& k) const {
	return all_fighters[k];
}

//EFFECTS return all fighters
std::vector<Fighter*> Team::get_all_fighters() {
	return all_fighters;
}

//REQUIRES team is in combat
//EFFECTS return true if all members are out of combat.
bool Team::all_members_died() const {
	assert(in_brawl);
	return total_size == 0;
}

//EFFECTS Prints all fighters to stream as "Fighter 1: Alex" 
//followed by newline and then "Fighter 2: Harry"
std::ostream& Team::print_all_fighters(std::ostream& os) {
	for (int i = 0; i < total_size; ++i) {
		os << "Fighter " << i + 1 << ": " << *all_fighters[i] << 
			" (Type: " << all_fighters[i]->get_element() << 
			", Current Health: " << all_fighters[i]->get_current_health() << ")" <<
			std::endl;
	}
	return os;
}

//REQUIRES team is in combat
//EFFECTS return size of team in combat
int Team::get_in_combat_size() const {
	return total_size;
}

//EFFECTS Prints in combat fighters to stream as "Fighter 1: Alex" 
//followed by newline and then "Fighter 2: Harry"
std::ostream& Team::print_in_combat_fighters(std::ostream& os) const {
	for (int i = 0; i < total_size; ++i) {
		Fighter* ithfighter = all_fighters[i];
		os << "Fighter " << i + 1 << ": " << *ithfighter << std::endl;
	}
	return os;
}

//REQUIRES team is not in combat
//EFFECTS makes the team enter a brawl. changes in_combat_fighters
void Team::enter_brawl() {
	assert(!in_brawl);
	in_brawl = true;
	for (int i = 0; i < total_size; ++i) {
		all_fighters[i]->enter_combat();
	}
}

//REQUIRES team is in combat and member is exiting combat due to lack of health.
// 0 <= k < in_combat_size. k represents kth person on team starting from 0.
//EFFECTS makes a member exit combat
//This changes in_combat_fighters
//and changes in_combat_size.
void Team::member_exits_combat(const int& k) {
	assert(0 <= k && k < total_size);
	delete all_fighters[k];
	all_fighters.erase(all_fighters.begin() + k);
	--total_size;
}

//REQUIRES team is in combat
//EFFECTS makes the team exit a brawl. 
//changes in_combat_fighters and out_of_combat_fighters.
void Team::exit_brawl() {
	in_brawl = false;
	while (total_size != 0) {
		member_exits_combat(0);
	}
}

//REQUIRES team is not in combat and fighter is not in combat
//EFFECTS add fighter to team
void Team::add_member(Fighter* fighter) {
	assert(!in_brawl);
	Fighter* added_member = Fighter_factory(fighter);
	++total_size;
	all_fighters.push_back(added_member);
}

//REQUIRES team is not in combat
//EFFECTS remove fighter from team
void Team::remove_member(int& fighter_index) {
	--total_size;
	delete all_fighters[fighter_index];
	all_fighters.erase(all_fighters.begin() + fighter_index);
}

Team::~Team() {
	exit_brawl();
}