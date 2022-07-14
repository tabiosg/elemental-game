#ifndef TEAM_H
#define TEAM_H
/* Team.h
 *
 * Team
 *
 * by Guthrie Tabios
 * tabiosg
 * 2021-04-01
 */
#include "Fighter.h"
#include <string>
#include <vector>

class Team
{
public:
	Team();

	Team(const Team &other);

	Team &operator=(const Team &rhs);

	// EFFECTS return total size of team
	int get_total_size() const;

	// EFFECTS return true if team is in brawl, returns false otherwise.
	bool get_brawl_status() const;

	// REQUIRES 0 < k <= inCombat_Fighters in team
	// EFFECTS return the kth  inCombat fighter.
	Fighter *get_kth_fighter(const int &k) const;

	// EFFECTS return all fighters
	std::vector<Fighter *> getAllFighters();

	// REQUIRES team is in combat
	// EFFECTS return true if all members are out of combat.
	bool all_members_died() const;

	// EFFECTS Prints all fighters to stream as "Fighter 1: Alex"
	// followed by newline and then "Fighter 2: Harry"
	std::ostream &printAllFighters(std::ostream &os);

	// REQUIRES team is in combat
	// EFFECTS return size of team in combat
	int get_inCombat_size() const;

	// EFFECTS Prints in combat fighters to stream as "Fighter 1: Alex"
	// followed by newline and then "Fighter 2: Harry"
	std::ostream &print_inCombat_fighters(std::ostream &os) const;

	// REQUIRES team is not in combat
	// EFFECTS makes the team enter a brawl. changes inCombat_fighters
	void enterBrawl();

	// REQUIRES team is in combat and member is exiting combat due to lack of health.
	// EFFECTS makes a member exit combat
	// This changes inCombat_fighters
	// and changes inCombat_size.
	void memberExitsCombat(const int &k);

	// REQUIRES team is in combat
	// EFFECTS makes the team exit a brawl.
	// changes inCombat_fighters and out_of_combat_fighters.
	void exitBrawl();

	// REQUIRES team is not in combat
	// EFFECTS add fighter to team
	void add_member(Fighter *fighter);

	// REQUIRES team is not in combat
	// EFFECTS remove fighter from team
	void remove_member(int &fighter_index);

	~Team();

private:
	int total_size;
	bool in_brawl;
	std::vector<Fighter *> all_fighters;
};

#endif
