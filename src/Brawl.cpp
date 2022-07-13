#include <string>
#include <vector>
#include <cassert>

#include "header/Brawl.h"
#include "header/Element.h"
#include "header/Team.h"
#include "header/Weapon.h"

Brawl::Brawl(Team given_team1, Team given_team2) : team1(given_team1),
												   team2(given_team2), total_dropped_weapons(0), team_1_turn(0),
												   team_2_turn(0), is_team_1_turn(true)
{
}

// EFFECTS start the entire brawl until one team loses all members.
void Brawl::startBrawl()
{
	team1.enter_brawl();
	team2.enter_brawl();
	std::cout << "Team 1 has entered the brawl! Here are its members:" << std::endl;
	team1.print_all_fighters(std::cout);
	std::cout << std::endl;
	std::cout << "Team 2 has entered the brawl! Here are its members:" << std::endl;
	team2.print_all_fighters(std::cout);
	std::cout << std::endl;

	int team1_size = team1.get_in_combat_size();
	int team2_size = team2.get_in_combat_size();
	assert(team1_size != 0 && team2_size != 0);
	while (team1_size != 0 && team2_size != 0)
	{

		std::string dummy;
		std::cout << std::endl
				  << "Type anything to see the next move. ";
		std::cin >> dummy;
		std::cout << std::endl
				  << "\033[2J"
				  << "\033[1;1H";

		Fighter *current_fighter;

		if (is_team_1_turn)
		{
			std::cout << "Team 1 will send out its fighter! " << std::endl
					  << std::endl;
			current_fighter = team1.get_kth_fighter(team_1_turn);
			request_and_enact_action(current_fighter, team1, team2);
			++team_1_turn;
			is_team_1_turn = false;
		}

		else
		{
			std::cout << "Team 2 will send out its fighter! " << std::endl
					  << std::endl;
			current_fighter = team2.get_kth_fighter(team_2_turn);
			request_and_enact_action(current_fighter, team2, team1);
			++team_2_turn;
			is_team_1_turn = true;
		}
		team1_size = team1.get_in_combat_size();
		team2_size = team2.get_in_combat_size();

		if (team_1_turn >= team1_size)
		{
			team_1_turn = 0;
		}
		if (team_2_turn >= team2_size)
		{
			team_2_turn = 0;
		}

		std::cout << "This is team 1 and its members now:" << std::endl;
		team1.print_all_fighters(std::cout);
		std::cout << std::endl;
		std::cout << "This is team 2 and its members now:" << std::endl;
		team2.print_all_fighters(std::cout);
	}
	team1_size = team1.get_in_combat_size();
	team2_size = team2.get_in_combat_size();
	if (team1_size == 0)
	{
		std::cout << "Team 1 wins!" << std::endl
				  << std::endl;
	}
	else
	{
		std::cout << "Team 2 wins!" << std::endl
				  << std::endl;
	}
	team1.exit_brawl();
	team2.exit_brawl();
}

// EFFECTS return team one
const Team Brawl::get_team_one() const
{
	return team1;
}

// EFFECTS return team two
const Team Brawl::get_team_two() const
{
	return team2;
}

// EFFECTS return team two
std::vector<Weapon *> Brawl::get_all_dropped_weapons()
{
	return dropped_weapons;
}

// REQUIRES 0 <= k < total_dropped_weapons
// EFFECTS return kth dropped weapon
Weapon *Brawl::get_kth_dropped_weapon(const int &k)
{
	assert(0 <= k && k < total_dropped_weapons);
	return dropped_weapons[k];
}

// REQUIRES 0 <= k < total_dropped_weapons
// EFFECTS remove kth dropped weapon
void Brawl::remove_kth_dropped_weapon(const int &k)
{
	assert(0 <= k && k < total_dropped_weapons);
	--total_dropped_weapons;
	delete dropped_weapons[k];
	dropped_weapons.erase(dropped_weapons.begin() + k);
}

// EFFECTS add dropped weapon
void Brawl::add_dropped_weapon(const Weapon *weapon)
{
	++total_dropped_weapons;
	Weapon *added_weapon = Weapon_factory(weapon);
	dropped_weapons.push_back(added_weapon);
}

// REQUIRES fighter has an element and fighter must be in combat
// If player wants to pick up weapon, make sure that there are dropped_weapons.
// MODIFIES action and target
// EFFECTS  Ask if fighter wants to attack or heal or grab weapon or skip turn. Do action.
void Brawl::request_and_enact_action(Fighter *f, Team &allies, Team &opponents)
{
	std::cout << "It is " << *f << "'s turn." << std::endl
			  << std::endl;

	std::vector<Fighter *> all_opponents = opponents.get_all_fighters();
	std::vector<Fighter *> all_allies = allies.get_all_fighters();

	std::string response = f->request_action(all_allies, all_opponents, dropped_weapons);
	if (response == "Attack")
	{
		int target = f->go_attack(all_opponents);
		Fighter *defender = opponents.get_kth_fighter(target);
		if (defender->get_current_health() == 0)
		{
			std::cout << *defender << " has exited the combat due to lack of health." << std::endl
					  << std::endl;
			int drop_index = defender->get_active_weapon();
			Weapon *dropped_weapon = defender->get_k_weapon(drop_index);
			std::cout << *defender << " has dropped the " << *dropped_weapon << "." << std::endl
					  << std::endl;
			add_dropped_weapon(dropped_weapon);
			opponents.member_exits_combat(target);
		}
	}
	else if (response == "Heal")
	{
		f->go_heal(all_allies);
	}
	else if (response == "Grab")
	{
		int target = f->go_grab_weapon(all_allies, all_opponents, dropped_weapons);
		remove_kth_dropped_weapon(target);
	}
	else if (response == "Skip")
	{
		std::cout << *f << " skips their turn." << std::endl
				  << std::endl;
	}
}

// REQUIRES fighter health drops to zero
// EFFECTS if fighter exits combat, change dropped weapons
void Brawl::fighter_exits_combat(Fighter *fighter)
{
	assert(fighter->get_current_health() == 0);
	fighter->exit_combat();
	int active_weapon = fighter->get_active_weapon();
	Weapon *copied_weapon = fighter->get_k_weapon(active_weapon);
	add_dropped_weapon(copied_weapon);
}

// EFFECTS Prints dropped_weapons to stream as "Dropped Weapon 1: Excalibur"
// followed by newline and then "Dropped Weapon 2: Gate of Babylon"
std::ostream &Brawl::print_dropped_weapons(std::ostream &os) const
{
	for (int i = 0; i < total_dropped_weapons; ++i)
	{
		os << "Dropped Weapon " << i + 1 << ": " << *dropped_weapons[i] << std::endl;
	}
	return os;
}

// EFFECTS delete all dropped weapons
Brawl::~Brawl()
{
	while (total_dropped_weapons != 0)
	{
		remove_kth_dropped_weapon(0);
	}
}
