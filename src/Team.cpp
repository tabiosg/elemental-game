#include <string>
#include <vector>
#include <cassert>
#include <numeric>

#include "header/Team.h"
#include "header/Fighter.h"

Team::Team() : totalSize(0), inBrawl(false)
{
}

Team::Team(const Team &other)
{
	totalSize = other.getTotalSize();
	inBrawl = other.getBrawlStatus();
	for (int i = 0; i < totalSize; ++i)
	{
		Fighter *copiedFighter = other.getFighterK(i);
		Fighter *fighterI = FighterFactory(copiedFighter);
		allFighters.push_back(fighterI);
	}
}

Team &Team::operator=(const Team &rhs)
{
	int one = 1;
	while (totalSize != 0)
	{
		removeMember(one);
	}

	totalSize = rhs.getTotalSize();
	inBrawl = rhs.getBrawlStatus();
	for (int i = 0; i < totalSize; ++i)
	{
		Fighter *copiedFighter = rhs.getFighterK(i);
		Fighter *fighterI = FighterFactory(copiedFighter);
		allFighters.push_back(fighterI);
	}
	std::vector<Fighter *> allFighters;

	std::vector<int> inCombatFighters;

	return *this;
}

// EFFECTS return total size of team
int Team::getTotalSize() const
{
	return totalSize;
}

// EFFECTS return true if team is in brawl, returns false otherwise.
bool Team::getBrawlStatus() const
{
	return inBrawl;
}

// REQUIRES 0 < k <= total fighters in team
// EFFECTS return the kth fighter fighter.
Fighter *Team::getFighterK(const int &k) const
{
	return allFighters[k];
}

// EFFECTS return all fighters
std::vector<Fighter *> Team::getAllFighters()
{
	return allFighters;
}

// REQUIRES team is in combat
// EFFECTS return true if all members are out of combat.
bool Team::areAllMembersDead() const
{
	assert(inBrawl);
	return totalSize == 0;
}

// EFFECTS Prints all fighters to stream as "Fighter 1: Alex"
// followed by newline and then "Fighter 2: Harry"
std::ostream &Team::printAllFighters(std::ostream &os)
{
	for (int i = 0; i < totalSize; ++i)
	{
		os << "Fighter " << i + 1 << ": " << *allFighters[i] << " (Type: " << allFighters[i]->getElement() << ", Current Health: " << allFighters[i]->getCurrentHealth() << ")" << std::endl;
	}
	return os;
}

// REQUIRES team is in combat
// EFFECTS return size of team in combat
int Team::getInCombatSize() const
{
	return totalSize;
}

// EFFECTS Prints in combat fighters to stream as "Fighter 1: Alex"
// followed by newline and then "Fighter 2: Harry"
std::ostream &Team::printInCombatFighters(std::ostream &os) const
{
	for (int i = 0; i < totalSize; ++i)
	{
		Fighter *fighterI = allFighters[i];
		os << "Fighter " << i + 1 << ": " << *fighterI << std::endl;
	}
	return os;
}

// REQUIRES team is not in combat
// EFFECTS makes the team enter a brawl. changes inCombatFighters
void Team::enterBrawl()
{
	assert(!inBrawl);
	inBrawl = true;
	for (int i = 0; i < totalSize; ++i)
	{
		allFighters[i]->enterCombat();
	}
}

// REQUIRES team is in combat and member is exiting combat due to lack of health.
// 0 <= k < inCombatSize. k represents kth person on team starting from 0.
// EFFECTS makes a member exit combat
// This changes inCombatFighters
// and changes inCombatSize.
void Team::memberExitsCombat(const int &k)
{
	assert(0 <= k && k < totalSize);
	delete allFighters[k];
	allFighters.erase(allFighters.begin() + k);
	--totalSize;
}

// REQUIRES team is in combat
// EFFECTS makes the team exit a brawl.
// changes inCombatFighters.
void Team::exitBrawl()
{
	inBrawl = false;
	while (totalSize != 0)
	{
		memberExitsCombat(0);
	}
}

// REQUIRES team is not in combat and fighter is not in combat
// EFFECTS add fighter to team
void Team::addMember(Fighter *fighter)
{
	assert(!inBrawl);
	Fighter *addedMember = FighterFactory(fighter);
	++totalSize;
	allFighters.push_back(addedMember);
}

// REQUIRES team is not in combat
// EFFECTS remove fighter from team
void Team::removeMember(int &fighterIndex)
{
	--totalSize;
	delete allFighters[fighterIndex];
	allFighters.erase(allFighters.begin() + fighterIndex);
}

Team::~Team()
{
	exitBrawl();
}
