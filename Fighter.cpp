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

    HumanFighter() : name("Default Name"), element_type(Element::ELE_WATER), 
        number_of_weapons(0), in_combat(false), max_health(200.0), 
        current_health(max_health), attack_strength(25.0) {}

    HumanFighter(const HumanFighter& other) {

    }

    HumanFighter& operator=(const HumanFighter& rhs) {
        return *this;
    }

    //EFFECTS returns fighter's name
    const std::string& get_name() const override {
        return name;
    }

    //REQUIRES fighter has an element
    //EFFECTS  returns element of fighter
    Element get_element() const override {
        return element_type;
    }

    //EFFECTS returns number of weapons on fighter
    int get_number_of_weapons() const override {
        return number_of_weapons;
    }

    //REQUIRES fighter has a weapon
    //EFFECTS  returns active weapon of fighter
    Weapon* get_active_weapon() const override {
        return active_weapon;
    }

    //EFFECTS  returns combat status of fighter
    bool get_combat_status() const override {
        return in_combat;
    }

    //EFFECTS  returns max health of fighter
    double get_max_health() const override {
        return max_health;
    }

    //EFFECTS  returns current health of fighter
    double get_current_health() const override {
        return current_health;
    }

    //EFFECTS  returns attack_strength of fighter
    double get_attack_strength() const override {
        return attack_strength;
    }

    //REQUIRES fighter wants to add weapon
    //EFFECTS gives fighter the extra weapon
    void add_weapon(Weapon* weapon) override {
        
    }

    //REQUIRES fighter wants to delete a weapon
    //EFFECTS deletes weapon
    void delete_weapon(const int& weapon_index) {

    }

    //REQUIRES fighter wants to change name
    //EFFECTS changes fighter name
    void change_name(const std::string& name_change) {
        name = name_change;
    }

    //EFFECTS changes fighter max health
    void change_max_health(const int& health_change) {
        max_health = health_change;
    }

    //EFFECTS changes fighter attack strength
    void change_attack_strength(const int& strength_change) {
        attack_strength = strength_change;
    }

    //REQUIRES fighter wants to heal
    //MODIFIES allies
    //EFFECTS  make fighter heal allies or self
    void go_heal(Team* allies) override {

    }

    //REQUIRES fighter wants to fight
    //MODIFIES opponents
    //EFFECTS  make fighter attack opponents
    void go_attack(Team* opponents) const override {

    }

    //REQUIRES fighter wants to fight
    //EFFECTS  make fighter grab weapon
    void go_grab_weapon(Team* allies, Team* opponents) override {

    }

    //REQUIRES fighter must be in combat
    //EFFECTS  change health based on amount healed
    void receive_healing(const double& healing, const Fighter* healer) override {

    }

    //REQUIRES fighter is focused by enemy
    //EFFECTS  change health based on attack
    void receive_attack(const double& damage, const Fighter* attacker) override {

    }

    // Needed to avoid some compiler errors
    virtual ~HumanFighter() {}

private:
    std::string name;
    Element element_type;
    std::vector<Weapon*> weapons;
    int number_of_weapons;
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

class PacifistFighter : public Fighter {
public:

    PacifistFighter() : name("Default Name"), element_type(Element::ELE_WATER),
        number_of_weapons(0), in_combat(false), max_health(100.0),
        current_health(max_health), attack_strength(25.0) {}

    PacifistFighter(const PacifistFighter& other) {

    }

    PacifistFighter& operator=(const PacifistFighter& rhs) {
        return *this;
    }

    //EFFECTS returns fighter's name
    const std::string& get_name() const override {
        return name;
    }

    //REQUIRES fighter has an element
    //EFFECTS  returns element of fighter
    Element get_element() const override {
        return element_type;
    }

    //EFFECTS returns number of weapons on fighter
    int get_number_of_weapons() const override {
        return number_of_weapons;
    }

    //REQUIRES fighter has a weapon
    //EFFECTS  returns active weapon of fighter
    Weapon* get_active_weapon() const override {
        return active_weapon;
    }

    //EFFECTS  returns combat status of fighter
    bool get_combat_status() const override {
        return in_combat;
    }

    //EFFECTS  returns max health of fighter
    double get_max_health() const override {
        return max_health;
    }

    //EFFECTS  returns current health of fighter
    double get_current_health() const override {
        return current_health;
    }

    //EFFECTS  returns attack_strength of fighter
    double get_attack_strength() const override {
        return attack_strength;
    }

    //REQUIRES fighter wants to add weapon
    //EFFECTS gives fighter the extra weapon
    void add_weapon(Weapon* weapon) override {

    }

    //REQUIRES fighter wants to delete a weapon
    //EFFECTS deletes weapon
    void delete_weapon(const int& weapon_index) {

    }

    //REQUIRES fighter wants to change name
    //EFFECTS changes fighter name
    void change_name(const std::string& name_change) {
        name = name_change;
    }

    //EFFECTS changes fighter max health
    void change_max_health(const int& health_change) {
        max_health = health_change;
    }

    //EFFECTS changes fighter attack strength
    void change_attack_strength(const int& strength_change) {
        attack_strength = strength_change;
    }

    //REQUIRES fighter wants to heal
    //MODIFIES allies
    //EFFECTS  make fighter heal allies or self
    void go_heal(Team* allies) override {

    }

    //REQUIRES fighter wants to fight
    //MODIFIES opponents
    //EFFECTS  make fighter attack opponents
    void go_attack(Team* opponents) const override {

    }

    //REQUIRES fighter wants to fight
    //EFFECTS  make fighter grab weapon
    void go_grab_weapon(Team* allies, Team* opponents) override {

    }

    //REQUIRES fighter must be in combat
    //EFFECTS  change health based on amount healed
    void receive_healing(const double& healing, const Fighter* healer) override {

    }

    //REQUIRES fighter is focused by enemy
    //EFFECTS  change health based on attack
    void receive_attack(const double& damage, const Fighter* attacker) override {

    }

    // Needed to avoid some compiler errors
    virtual ~PacifistFighter() {}

private:
    std::string name;
    Element element_type;
    std::vector<Weapon*> weapons;
    int number_of_weapons;
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
