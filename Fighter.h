#ifndef FIGHTER_H
#define FIGHTER_H
/* Fighter.h
 *
 * Fighters
 *
 * by Guthrie Tabios
 * tabiosg
 * 2021-04-01
 */


#include "Element.h"
#include "Team.h"
#include "Weapon.h"
#include <string>
#include <vector>

class Fighter {
public:
    //EFFECTS returns fighter's name
    virtual const std::string & get_name() const = 0;

    //REQUIRES fighter has an element
    //EFFECTS  returns element of fighter
    virtual Element get_element() const = 0;

    //EFFECTS returns number of weapons on fighter
    virtual int get_number_of_weapons() const = 0;

    //REQUIRES fighter has a weapon
    //EFFECTS  returns active weapon of fighter
    virtual int get_active_weapon() const = 0;

    //EFFECTS  returns combat status of fighter
    virtual bool get_combat_status() const = 0;

    //EFFECTS  returns max health of fighter
    virtual double get_max_health() const = 0;

    //EFFECTS  returns current health of fighter
    virtual double get_current_health() const = 0;

    //EFFECTS  returns attack_strength of fighter
    virtual double get_attack_strength() const = 0;

    //REQUIRES fighter wants to add weapon
    //EFFECTS gives fighter the extra weapon
    virtual void add_weapon(Weapon* weapon) = 0;
    
    //REQUIRES fighter wants to delete a weapon
    //EFFECTS deletes weapon
    virtual void delete_weapon(const int& weapon_index) = 0;

    //REQUIRES 0 < k <= number_of_weapons
    //EFFECTS returns the kth weapon's name
    virtual const std::string& get_k_name(const int& k) const = 0;

    //REQUIRES 0 < k <= number_of_weapons
    //EFFECTS  returns element of the kth weapon
    virtual Element get_k_element(const int& k) const = 0;

    ///REQUIRES 0 < k <= number_of_weapons
    //EFFECTS  returns attack strength of the kth weapon
    virtual double get_k_attack_strength(const int& k) const = 0;

    //REQUIRES 0 < k <= number_of_weapons
    //EFFECTS  returns healing strength of the kth weapon
    virtual double get_k_healing_strength(const int& k) const = 0;

    //REQUIRES 0 < k <= number_of_weapons
    //EFFECTS returns the kth weapon's type
    virtual const std::string& get_k_weapon_type(const int& k) const = 0;

    //REQUIRES fighter wants to change name
    //EFFECTS changes fighter name
    virtual void change_name(const std::string& name_change) = 0;

    //EFFECTS changes fighter max health
    virtual void change_max_health(const int& health_change) = 0;

    //EFFECTS changes fighter attack strength
    virtual void change_attack_strength(const int& strength_change) = 0;

    //REQUIRES fighter wants to heal
    //MODIFIES allies
    //EFFECTS  make fighter heal allies or self
    virtual void go_heal(Team* allies) = 0;

    //REQUIRES fighter wants to fight
    //MODIFIES opponents
    //EFFECTS  make fighter attack opponents. print out to terminal who was attacked.
    virtual void go_attack(Team* opponents) const = 0;

    //REQUIRES fighter wants to fight
    //EFFECTS  make fighter grab weapon
    virtual void go_grab_weapon(Team* allies, Team* opponents) = 0;

    //REQUIRES fighter must be in combat
    //EFFECTS  change health based on amount healed
    virtual void receive_healing(const double& healing, const Fighter* healer) = 0;

    //REQUIRES fighter is focused by enemy
    //EFFECTS  change health based on attack
    virtual void receive_attack(const double& damage, const Fighter* attacker) = 0;

    // Needed to avoid some compiler errors
    virtual ~Fighter() {}

private:
    std::string name;
    Element element_type;
    std::vector<Weapon*> weapons;
    int number_of_weapons;
    int active_weapon;
    bool in_combat;
    double max_health;
    double current_health;

    double attack_strength;
};

//EFFECTS Returns a pointer to a fighter with the given name and strategy
Fighter* Fighter_factory(const std::string& name, const std::string& strategy);

//EFFECTS Prints fighter's name to os
std::ostream & operator<<(std::ostream& os, const Fighter& f);

//EFFECTS Prints weapons of fighter to os as "Weapon 1: Excalibur" 
	//followed by newline and then "Weapon 2: Gate of Babylon"
std::ostream& print_weapons(std::ostream& os, const Fighter& f);

#endif
