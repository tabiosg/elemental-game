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
	int getTotalSize() const;

	// EFFECTS return true if team is in brawl, returns false otherwise.
	bool getBrawlStatus() const;

	// REQUIRES 0 <= k < inCombatFighters in team
	// EFFECTS return the kth  inCombat fighter.
	Fighter *getFighterK(const int &k) const;

	// EFFECTS return all fighters
	std::vector<Fighter *> getAllFighters();

	// REQUIRES team is in combat
	// EFFECTS return true if all members are out of combat.
	bool areAllMembersDead() const;

	// EFFECTS Prints all fighters to stream as "Fighter 1: Alex"
	// followed by newline and then "Fighter 2: Harry"
	std::ostream &printAllFighters(std::ostream &os);

	// REQUIRES team is in combat
	// EFFECTS return size of team in combat
	int getInCombatSize() const;

	// EFFECTS Prints in combat fighters to stream as "Fighter 1: Alex"
	// followed by newline and then "Fighter 2: Harry"
	std::ostream &printInCombatFighters(std::ostream &os) const;

	// REQUIRES team is not in combat
	// EFFECTS makes the team enter a brawl. changes inCombatFighters
	void enterBrawl();

	// REQUIRES team is in combat and member is exiting combat due to lack of health.
	// EFFECTS makes a member exit combat
	// This changes inCombatFighters
	// and changes inCombatSize.
	void memberExitsCombat(const int &k);

	// REQUIRES team is in combat
	// EFFECTS makes the team exit a brawl.
	// changes inCombatFighters.
	void exitBrawl();

	// REQUIRES team is not in combat
	// EFFECTS add fighter to team
	void addMember(Fighter *fighter);

	// REQUIRES team is not in combat
	// EFFECTS remove fighter from team
	void removeMember(int &fighterIndex);

	~Team();

private:
	int totalSize;
	bool inBrawl;
	std::vector<Fighter *> allFighters;
};

#endif
