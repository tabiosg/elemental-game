#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Fighter.h"
#include "Team.h"
#include "Weapon.h"
#include "Element.h"
#include "Brawl.h"

class HumanFighter : public Fighter {
public:

    HumanFighter() : name("Default Name"), element_type(Element::ELE_WATER),
        number_of_weapons(0), active_weapon(0), in_combat(false), max_health(200.0),
        current_health(max_health), attack_strength(25.0), 
        healing_strength(25.0) {}

    HumanFighter(const std::string& given_name, const Element& element) : HumanFighter() {
        name = given_name;
        element_type = element;
    }

    HumanFighter(const HumanFighter& other) {
        name = other.get_name();
        element_type = other.get_element();
        number_of_weapons = other.get_number_of_weapons();
        active_weapon = other.get_active_weapon();
        in_combat = other.get_combat_status();
        max_health = other.get_max_health();
        current_health = other.get_current_health();
        attack_strength = other.get_attack_strength();
        healing_strength = other.get_healing_strength();

        for (int k = 0; number_of_weapons; ++k) {
            Weapon* additional_weapon = Weapon_factory(other.get_k_name(k),
                other.get_k_element(k), other.get_k_attack_strength(k), other.get_k_healing_strength(k),
                other.get_k_weapon_type(k));
            weapons.push_back(additional_weapon);
        }

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
    int get_active_weapon() const override {
        return active_weapon;
    }

    //REQUIRES 0 < k <= number_of_weapons
    //EFFECTS returns kth weapons of fighter
    Weapon* get_k_weapon(const int& k) const override {
        assert(get_number_of_weapons() != 0);
        return weapons[k - 1];
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

    //EFFECTS  returns healing_strength of fighter
    double get_healing_strength() const override {
        return healing_strength;
    }

    //REQUIRES fighter wants to add weapon
    //EFFECTS gives fighter the extra weapon
    void add_weapon(Weapon* weapon) override {
        ++number_of_weapons;
        weapons.push_back(weapon);
    }

    //REQUIRES fighter wants to delete a weapon
    //EFFECTS deletes weapon
    void delete_weapon(const int& weapon_index) {
        --number_of_weapons;
        delete weapons[weapon_index];
        weapons.erase(weapons.begin() + weapon_index);
    }

    //REQUIRES 0 < k <= number_of_weapons
    //EFFECTS returns the kth weapon's name
    const std::string& get_k_name(const int& k) const override {
        return weapons[k - 1]->get_name();
    }

    //REQUIRES 0 < k <= number_of_weapons
    //EFFECTS  returns element of the kth weapon
    Element get_k_element(const int& k) const override {
        return weapons[k - 1]->get_element();
    }

    //REQUIRES 0 < k <= number_of_weapons
    //EFFECTS  returns attack strength of the kth weapon
    double get_k_attack_strength(const int& k) const override {
        return weapons[k - 1]->get_attack_strength();
    }

    //REQUIRES 0 < k <= number_of_weapons
    //EFFECTS  returns healing strength of the kth weapon
    double get_k_healing_strength(const int& k) const override {
        return weapons[k - 1]->get_healing_strength();
    }

    //REQUIRES 0 < k <= number_of_weapons
    //EFFECTS returns the kth weapon's type
    const std::string& get_k_weapon_type(const int& k) const override {
        return weapons[k - 1]->get_weapon_type();
    }

    //REQUIRES fighter wants to change name
    //EFFECTS changes fighter name
    void change_name(const std::string& name_change) override {
        name = name_change;
    }

    //EFFECTS changes fighter max health
    void change_max_health(const int& health_change) override {
        max_health = health_change;
    }

    //EFFECTS changes fighter current health
    void change_current_health(const int& health_change) override {
        current_health = health_change;
    }

    //EFFECTS changes fighter attack strength
    void change_attack_strength(const int& strength_change) override {
        attack_strength = strength_change;
    }

    //EFFECTS changes fighter healing strength
    void change_healing_strength(const int& healing_change) override {
        healing_strength = healing_change;
    }

    //REQUIRES fighter wants to heal
    //MODIFIES allies
    //EFFECTS  make fighter heal allies or self
    void go_heal(Team& allies) override {
        assert(get_combat_status);
        int target = request_heal_target(allies);
        active_weapon = request_active_weapon();
        Weapon* current_weapon = get_k_weapon(active_weapon - 1);
        allies.get_kth_in_combat_fighter(target)->receive_healing(current_weapon, this);

        Element weapon_element = current_weapon->get_element();
        if (weapon_element.is_strengthening(element_type)) {
            if (current_health >= 0.2 * max_health) {
                current_health -= 0.1 * max_health;
            }
        }

    }

    //REQUIRES fighter wants to fight
    //MODIFIES opponents
    //EFFECTS  make fighter attack opponents
    void go_attack(Team& opponents) override {
        assert(get_combat_status);
        int target = request_attack_target(opponents);
        active_weapon = request_active_weapon();
        Weapon* current_weapon = get_k_weapon(active_weapon);
        opponents.get_kth_in_combat_fighter(target)->receive_attack(current_weapon, this);
    }

    //REQUIRES fighter wants to fight
    //EFFECTS  make fighter grab weapon
    void go_grab_weapon(Team& allies, Team& opponents, Brawl& brawl) override {
        assert(get_combat_status);
        int target = request_grab_target(brawl);
        Weapon* wanted_weapon = brawl.get_kth_dropped_weapon(target);
        add_weapon(wanted_weapon);
        brawl.remove_kth_dropped_weapon(target);
    }

    //REQUIRES fighter must be in combat
    //EFFECTS  change health based on amount healed
    void receive_healing(const Weapon* healing_weapon, Fighter* healer) override {
        assert(get_combat_status);
        double multiplier = 1.0;
        Element healer_element = healer->get_element();
        int active = healer->get_active_weapon();
        Element weapon_element = healing_weapon->get_element();
        if (weapon_element.is_special_resource(healer_element)) {
            if (weapon_element.is_strengthening(healer_element)) {
                multiplier = multiplier + 0.2;
            }
            else if (!weapon_element.is_strengthening(healer_element)) {
                multiplier = multiplier - 0.2;
            }
        }
        if (element_type.is_special_resource(weapon_element)) {
            if (element_type.is_strengthening(weapon_element)) {
                multiplier = multiplier + 0.2;
            }
            else if (!element_type.is_strengthening(weapon_element)) {
                multiplier = multiplier - 0.2;
            }
        }

        double healing_strength = healing_weapon->get_healing_strength();
        double total_healing = (healing_strength) * multiplier;
        
        current_health += total_healing;
        if (current_health > max_health) {
            current_health = max_health;
        }
    }

    //REQUIRES fighter is focused by enemy
    //EFFECTS  change health based on attack
    void receive_attack(const Weapon* damaging_weapon, const Fighter* attacker) override {
        assert(get_combat_status);
        double multiplier = 1.0;
        Element damaging_element = attacker->get_element();
        int active = attacker->get_active_weapon();
        Element weapon_element = damaging_weapon->get_element();
        if (weapon_element.is_special_strength(damaging_element)) {
            if (weapon_element.is_effective_strength(damaging_element)) {
                multiplier = multiplier + 0.2;
            }
            else if (!weapon_element.is_special_strength(damaging_element)) {
                multiplier = multiplier - 0.2;
            }
        }
        if (element_type.is_special_strength(weapon_element)) {
            if (element_type.is_effective_strength(weapon_element)) {
                multiplier = multiplier + 0.2;
            }
            else if (!element_type.is_effective_strength(weapon_element)) {
                multiplier = multiplier - 0.2;
            }
        }

        double healing_strength = damaging_weapon->get_attack_strength();
        double total_damage = (healing_strength)*multiplier;

        current_health -= total_damage;
        if (current_health <= 0) {
            in_combat = false;
            current_health = 0;
        }
    }

    //EFFECTS: Prints weapons of fighter to os
    std::ostream& print_weapons(std::ostream& os) const override {
        for (int i = 0; i < number_of_weapons; ++i) {
            os << "Weapon " << i << ": " << *weapons[i] << std::endl;
        }
        return os;
    }

    // Needed to avoid some compiler errors
    virtual ~HumanFighter() {
        while (number_of_weapons != 0) {
            delete_weapon(0);
        }
    }

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

    //REQUIRES fighter wants to attack
    //EFFECTS see who fighter wants to attack
    int request_attack_target(const Team& opponents) const {
        std::cout << "These are your opponents: " << std::endl;
        opponents.print_in_combat_fighters(std::cout);
        std::cout << "Choose who to attack: " << std::endl;
        int target;
        std::cin >> target;
        assert(target <= opponents.get_in_combat_size() && target > 0);
        return target;
    }

    //REQUIRES fighter wants to heal
    //EFFECTS see who fighter wants to heal
    int request_heal_target(const Team& allies) const {
        std::cout << "These are your allies: " << std::endl;
        allies.print_in_combat_fighters(std::cout);
        std::cout << "Choose who to heal (0 for self)" << std::endl;
        int target;
        std::cin >> target;
        assert(target <= allies.get_in_combat_size() && target > 0);
        return target;
    }

    //REQUIRES fighter wants to heal or attack
    //EFFECTS see which weapon the fighter wants to use
    int request_active_weapon() {
        std::cout << "These are your weapons: " << std::endl;
        print_weapons(std::cout);
        std::cout << "Choose which weapon to equip by entering a number (0 for same): " << std::endl;
        int target;
        std::cin >> target;
        assert(0 >= target && target <= number_of_weapons);
        if (target != 0) {
            return active_weapon;
        }
        return target;
    }

    //REQUIRES fighter wants to grab and there are dropped weapons
    //EFFECTS see what weapon the fighter wants to grab
    int request_grab_target(const Brawl& brawl) const {
        std::cout << "These are the dropped weapons: " << std::endl;
        brawl.print_dropped_weapons(std::cout);
        std::cout << "Choose which weapon to equip by entering a number: " << std::endl;
        int target;
        return target;
    }
};

//EFFECTS: Returns a pointer to a fighter with the given name and type
Fighter* Fighter_factory(const std::string& name, const Element& element,
    const std::string& type) {
    if (type == "HumanFighter") {
        return new HumanFighter(name, element);
    }
    assert(false);
    return nullptr;
}

//EFFECTS: Prints fighter's name to os
std::ostream& operator<<(std::ostream& os, const Fighter& f) {
    os << f.get_name();
    return os;
}

//EFFECTS: Prints weapons of fighter to os
std::ostream& print_weapons(std::ostream& os, const Fighter& f) {
    f.print_weapons(os);
    return os;
}
