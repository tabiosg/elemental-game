#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Fighter.h"
#include "Team.h"
#include "Weapon.h"
#include "Element.h"

class HumanFighter : public Fighter {
public:

    HumanFighter() {

    }

    HumanFighter(const HumanFighter& other) {

    }

    HumanFighter& operator=(const HumanFighter& rhs) {
        return *this;
    }

    //EFFECTS returns fighter's name
    const std::string& get_name() const override {

    }

    //REQUIRES fighter has an element
    //EFFECTS  returns element of fighter
    Element get_element() const override {

    }

    //REQUIRES fighter has a weapon
    //EFFECTS  returns active weapon of fighter
    Weapon* get_active_weapon() const override {

    }

    //EFFECTS  returns combat status of fighter
    virtual bool get_combat_status() const override {

    }

    //EFFECTS  returns max health of fighter
    virtual double get_max_health() const override {

    }

    //EFFECTS  returns current health of fighter
    virtual double get_current_health() const override {

    }

    //EFFECTS  returns attack_strength of fighter
    virtual double get_attack_strength() const override {

    }

    //REQUIRES fighter wants to add weapon
    //EFFECTS gives fighter the extra weapon
    virtual void add_weapon(Weapon* weapon) override {

    }

    //REQUIRES fighter wants to delete a weapon
    //EFFECTS gives fighter the extra weapon
    virtual void delete_weapon(const int& weapon_index) {

    }

    //REQUIRES fighter wants to change name
    //EFFECTS changes fighter name
    virtual void change_name(const std::string& name_change) {

    }

    //EFFECTS changes fighter max health
    virtual void change_max_health(const int& health_change) {

    }

    //EFFECTS changes fighter attack strength
    virtual void change_attack_strength(const int& strength_change) {

    }

    //REQUIRES fighter wants to heal
    //MODIFIES allies
    //EFFECTS  make fighter heal allies or self
    virtual void go_heal(Team* allies) override {

    }

    //REQUIRES fighter wants to fight
    //MODIFIES opponents
    //EFFECTS  make fighter attack opponents
    virtual void go_attack(Team* opponents) const override {

    }

    //REQUIRES fighter wants to fight
    //EFFECTS  make fighter grab weapon
    virtual void go_grab_weapon(Team* allies, Team* opponents) override {

    }

    //REQUIRES fighter must be in combat
    //EFFECTS  change health based on amount healed
    virtual void receive_healing(const double& healing, const Fighter* healer) override {

    }

    //REQUIRES fighter is focused by enemy
    //EFFECTS  change health based on attack
    virtual void receive_attack(const double& damage, const Fighter* attacker) override {

    }

    // Needed to avoid some compiler errors
    virtual ~HumanFighter() {}

private:
    std::string name;
    Element element_type;
    std::vector<Weapon*> weapons;
    Weapon* active_weapon;
    bool in_combat;
    double max_health;
    double current_health;

    double attack_strength;

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
};

//EFFECTS: Returns a pointer to a fighter with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the fight is over
Fighter* Fighter_factory(const std::string& name, const std::string& strategy) {

}

//EFFECTS: Prints fighter's name to os
std::ostream& operator<<(std::ostream& os, const Fighter& f) {
    os << f.get_name();
    return os;
}

//EFFECTS: Prints weapons of fighter to os
std::ostream& print_weapons(std::ostream& os, const Fighter& f) {

}
