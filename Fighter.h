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

#include "Weapon.h"
#include <string>
#include <vector>

class Fighter {
public:
    //fighter types
    static constexpr const char* const FIGHTER_HUMAN = "Human";
    static constexpr const char* const FIGHTER_WARRIOR = "Warrior";
    //list
    static constexpr const char* const FIGHTER_LIST[] = {
      Fighter::FIGHTER_HUMAN,
      Fighter::FIGHTER_WARRIOR
    };
    static constexpr const int NUM_FIGHTER_TYPES = 2;

    //EFFECTS returns fighter's name
    virtual const std::string & get_name() const = 0;

    //EFFECTS returns fighter's type
    virtual const std::string& get_type() const = 0;

    //REQUIRES fighter has an element
    //EFFECTS  returns element of fighter
    virtual Element get_element() const = 0;

    //EFFECTS returns number of weapons on fighter
    virtual int get_number_of_weapons() const = 0;

    //REQUIRES fighter has a weapon
    //EFFECTS  returns active weapon of fighter
    virtual int get_active_weapon() const = 0;

    //EFFECTS returns kth weapons of fighter
    virtual Weapon* get_k_weapon(const int& k) const = 0;

    //EFFECTS  returns combat status of fighter
    virtual bool get_combat_status() const = 0;

    //EFFECTS  returns max health of fighter
    virtual double get_max_health() const = 0;

    //EFFECTS  returns current health of fighter
    virtual double get_current_health() const = 0;

    //EFFECTS  returns attack_strength of fighter
    virtual double get_attack_strength() const = 0;

    //EFFECTS  returns healing_strength of fighter
    virtual double get_healing_strength() const = 0;

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
    virtual const std::string get_k_weapon_type(const int& k) const = 0;

    //REQUIRES fighter wants to change name
    //EFFECTS changes fighter name
    virtual void change_name(const std::string& name_change) = 0;

    //EFFECTS changes fighter max health
    virtual void change_max_health(const int& health_change) = 0;

    //EFFECTS changes fighter current health
    virtual void change_current_health(const int& health_change) = 0;

    //EFFECTS changes fighter attack strength
    virtual void change_attack_strength(const int& strength_change) = 0;

    //EFFECTS changes fighter healing strength
    virtual void change_healing_strength(const int& healing_change) = 0;

    //REQUIRES fighter is currently not in combat
    //EFFECTS make fighter enter combat
    virtual void enter_combat() = 0;

    //REQUIRES fighter is currently in combat
    //EFFECTS make fighter exit combat
    virtual void exit_combat() = 0;

    //EFFECTS request action of fighter. should either be attack heal grab or skip.
    virtual std::string request_action(std::vector<Fighter*> allies, std::vector<Fighter*> opponents,
        const std::vector<Weapon*> dropped_weapons) = 0;

    //REQUIRES fighter wants to heal
    //MODIFIES allies
    //EFFECTS  make fighter heal allies or self
    virtual void go_heal(std::vector<Fighter*> allies) = 0;

    //REQUIRES fighter wants to fight
    //MODIFIES opponents
    //EFFECTS  make fighter attack opponents. return who was attacked
    virtual int go_attack(std::vector<Fighter*> opponents) = 0;

    //REQUIRES fighter wants to fight
    //EFFECTS  make fighter grab weapon
    virtual int go_grab_weapon(std::vector<Fighter*> allies, std::vector<Fighter*> opponents, 
        const std::vector<Weapon*> dropped_weapons) = 0;

    //REQUIRES fighter must be in combat
    //EFFECTS  change health based on amount healed
    virtual void receive_healing(const Weapon* healing_weapon, Fighter* healer) = 0;

    //REQUIRES fighter is focused by enemy
    //EFFECTS  change health based on attack
    //do not change combat status if below 0 hp here.
    virtual void receive_attack(const Weapon* damaging_weapon, const Fighter* attacker) = 0;

    //EFFECTS: Prints weapons of fighter to os
    virtual std::ostream& print_weapons(std::ostream& os) const = 0;

    virtual std::ostream& print_list_of_weapons(std::ostream& os, const std::vector<Weapon*> weapons) const = 0;

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
    double healing_strength;
    std::string type;
};

//EFFECTS Returns a pointer to a fighter with the given name, element, and type
Fighter* Fighter_factory(const std::string& name, const Element& element,
    const std::string& type);

//EFFECTS: Returns a pointer to a fighter with the given name, element, weapon, and type
Fighter* Fighter_factory(const std::string& name, const Element& element,
    const std::string& weapon, const std::string& type);

//EFFECTS Returns a pointer to a fighter that is copy of copied_fighter
Fighter* Fighter_factory(const Fighter* copied_fighter);

//EFFECTS Prints fighter's name to os
std::ostream & operator<<(std::ostream& os, const Fighter& f);

//EFFECTS Prints weapons of fighter to os as "Weapon 1: Excalibur" 
//followed by newline and then "Weapon 2: Gate of Babylon"
std::ostream& print_weapons(std::ostream& os, const Fighter& f);

//EFFECTS Prints fighters to stream as "Fighter 1: Alex" 
//followed by newline and then "Fighter 2: Harry"
std::ostream& print_list_of_fighters(std::ostream& os, std::vector<Fighter*> fighters);

#endif
