#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "header/Fighter.h"

#include "header/Weapon.h"
#include "header/Element.h"

class Human : public Fighter {
public:

    Human() : name("Angel"), element_type(Element::ELE_WATER),
        number_of_weapons(0), active_weapon(-1), in_combat(false), max_health(200.0),
        current_health(max_health), attack_strength(25.0), 
        healing_strength(25.0), type("Human") {}

    Human(const std::string& given_name, const Element& element) : Human() {
        name = given_name;
        element_type = element;
    }

    Human(const std::string& given_name, const Element& element, 
        const std::string& weapon_type) : Human() {
        name = given_name; 
        element_type = element;
        Weapon* default_weapon;
        if (weapon_type == Weapon::WEAPON_STAFF) {
            default_weapon = Weapon_factory(Weapon::WEAPON_STAFF);
        }
        else if (weapon_type == Weapon::WEAPON_SPEAR) {
            default_weapon = Weapon_factory(Weapon::WEAPON_STAFF);
        }
        else if (weapon_type == Weapon::WEAPON_CROSS) {
            default_weapon = Weapon_factory(Weapon::WEAPON_CROSS);
        }
        else {
            assert(false);
        }
        add_weapon(default_weapon);
    }

    Human(const std::string& given_name, const Element& given_element,
        std::vector<Weapon*> given_weapons, const int& given_number_of_weapons,
        const int& given_active_weapon, const bool& given_in_combat,
        const double& given_max_health, const double& given_current_health,
        const double& given_attack_strength, const double& given_healing_strength,
        std::string& given_type) : name(given_name), element_type(given_element),
        weapons(given_weapons), number_of_weapons(given_number_of_weapons),
        active_weapon(given_active_weapon), in_combat(given_in_combat),
        max_health(given_max_health), current_health(given_current_health),
        attack_strength(given_attack_strength), healing_strength(given_healing_strength),
        type(given_type) {

    }

    Human(const Human& other) {
        name = other.get_name();
        element_type = other.get_element();
        number_of_weapons = other.get_number_of_weapons();
        active_weapon = other.get_active_weapon();
        in_combat = other.get_combat_status();
        max_health = other.get_max_health();
        current_health = other.get_current_health();
        attack_strength = other.get_attack_strength();
        healing_strength = other.get_healing_strength();
        type = other.get_type();

        for (int k = 0; number_of_weapons; ++k) {
            Weapon* additional_weapon = Weapon_factory(other.get_k_weapon(k));
            weapons.push_back(additional_weapon);
        }

    }

    Human& operator=(const Human& rhs) {
        while (number_of_weapons != 0) {
            delete_weapon(0);
        }

        name = rhs.get_name();
        element_type = rhs.get_element();
        number_of_weapons = rhs.get_number_of_weapons();
        active_weapon = rhs.get_active_weapon();
        in_combat = rhs.get_combat_status();
        max_health = rhs.get_max_health();
        current_health = rhs.get_current_health();
        attack_strength = rhs.get_attack_strength();
        healing_strength = rhs.get_healing_strength();
        type = rhs.get_type();

        for (int k = 0; number_of_weapons; ++k) {
            Weapon* additional_weapon = Weapon_factory(rhs.get_k_weapon(k));
            weapons.push_back(additional_weapon);
        }
        return *this;
    }

    // EFFECTS returns fighter's name
    const std::string& get_name() const override {
        return name;
    }

    // EFFECTS returns fighter's type
    const std::string& get_type() const override {
        return type;
    }

    // REQUIRES fighter has an element
    // EFFECTS  returns element of fighter
    Element get_element() const override {
        return element_type;
    }

    // EFFECTS returns number of weapons on fighter
    int get_number_of_weapons() const override {
        return number_of_weapons;
    }

    // REQUIRES fighter has a weapon
    // EFFECTS  returns active weapon of fighter
    int get_active_weapon() const override {
        return active_weapon;
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS returns kth weapons of fighter
    Weapon* get_k_weapon(const int& k) const override {
        assert(get_number_of_weapons() != 0);
        return weapons[k];
    }

    // EFFECTS  returns combat status of fighter
    bool get_combat_status() const override {
        return in_combat;
    }

    // EFFECTS  returns max health of fighter
    double get_max_health() const override {
        return max_health;
    }

    // EFFECTS  returns current health of fighter
    double get_current_health() const override {
        return current_health;
    }

    // EFFECTS  returns attack_strength of fighter
    double get_attack_strength() const override {
        return attack_strength;
    }

    // EFFECTS  returns healing_strength of fighter
    double get_healing_strength() const override {
        return healing_strength;
    }

    // REQUIRES fighter wants to add weapon
    // EFFECTS gives fighter the extra weapon
    void add_weapon(Weapon* weapon) override {
        ++number_of_weapons;
        Weapon* added_weapon = Weapon_factory(weapon);
        weapons.push_back(added_weapon);
        if (active_weapon == -1) {
            active_weapon = 0;
        }
    }

    // REQUIRES fighter wants to delete a weapon
    // EFFECTS deletes weapon
    void delete_weapon(const int& weapon_index) {
        --number_of_weapons;
        delete weapons[weapon_index];
        weapons.erase(weapons.begin() + weapon_index);
        if (active_weapon >= number_of_weapons) {
            active_weapon = number_of_weapons - 1;
        }
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS returns the kth weapon's name
    const std::string& get_k_name(const int& k) const override {
        return weapons[k]->get_name();
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS  returns element of the kth weapon
    Element get_k_element(const int& k) const override {
        return weapons[k]->get_element();
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS  returns attack strength of the kth weapon
    double get_k_attack_strength(const int& k) const override {
        return weapons[k]->get_attack_strength();
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS  returns healing strength of the kth weapon
    double get_k_healing_strength(const int& k) const override {
        return weapons[k]->get_healing_strength();
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS returns the kth weapon's type
    const std::string get_k_weapon_type(const int& k) const override {
        return weapons[k]->get_weapon_type();
    }

    // REQUIRES fighter wants to change name
    // EFFECTS changes fighter name
    void change_name(const std::string& name_change) override {
        name = name_change;
    }

    // EFFECTS changes fighter max health
    void change_max_health(const int& health_change) override {
        max_health = health_change;
    }

    // EFFECTS changes fighter current health
    void change_current_health(const int& health_change) override {
        current_health = health_change;
    }

    // EFFECTS changes fighter attack strength
    void change_attack_strength(const int& strength_change) override {
        attack_strength = strength_change;
    }

    // EFFECTS changes fighter healing strength
    void change_healing_strength(const int& healing_change) override {
        healing_strength = healing_change;
    }

    // REQUIRES fighter is currently not in combat
    // EFFECTS make fighter enter combat
    void enter_combat() override {
        assert(!in_combat);
        in_combat = true;
    }

    // REQUIRES fighter is currently in combat
    // EFFECTS make fighter exit combat
    void exit_combat() override {
        assert(in_combat);
        in_combat = false;
    }

    // EFFECTS request action of fighter. should either be attack heal grab or skip.
    std::string request_action(std::vector<Fighter*> allies, std::vector<Fighter*> opponents, 
        const std::vector<Weapon*> dropped_weapons) override {
        std::cout << name << ", would you like to attack, heal, grab a weapon, or skip your turn?" <<
            std::endl << "Answer with \"Attack\", \"Heal\", \"Grab\", or \"Skip\": " <<
            std::endl;
        std::string response;
        std::cin >> response;
        std::cout << std::endl;
        if (response != "Attack" && response != "Heal" && response != "Grab" && response != "Skip") {
            std::cout << std::endl << "\033[2J" << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return request_action(allies, opponents, dropped_weapons);
        }
        std::cout << std::endl << "\033[2J" << "\033[1;1H";
        return response;
    }

    // REQUIRES fighter wants to heal
    // MODIFIES allies
    // EFFECTS  make fighter heal allies or self
    void go_heal(std::vector<Fighter*> allies) override {
        assert(get_combat_status());
        int target = request_heal_target(allies);
        active_weapon = request_active_weapon();
        Weapon* current_weapon = get_k_weapon(active_weapon);

        std::cout << *this << " used " << *current_weapon << " to heal " << *allies[target] << std::endl;

        allies[target]->receive_healing(current_weapon, this);

        Element weapon_element = current_weapon->get_element();
        if (weapon_element.is_strengthening(element_type)) {
            if (current_health >= 0.2 * max_health) {
                current_health -= 0.1 * max_health;
            }
        }

    }

    // REQUIRES fighter wants to fight
    // MODIFIES opponents
    // EFFECTS  make fighter attack opponents. return who was attacked
    int go_attack(std::vector<Fighter*> opponents) override {
        assert(get_combat_status());
        int target = request_attack_target(opponents);
        active_weapon = request_active_weapon();
        Weapon* current_weapon = get_k_weapon(active_weapon);

        std::cout << *this << " used " << *current_weapon << " to attack " << *opponents[target] << std::endl;

        opponents[target]->receive_attack(current_weapon, this);

        return target;
    }

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    int go_grab_weapon(std::vector<Fighter*> allies, std::vector<Fighter*> opponents, 
        const std::vector<Weapon*> dropped_weapons) override {
        assert(get_combat_status());
        int target = request_grab_target(dropped_weapons);
        Weapon* wanted_weapon = dropped_weapons[target];
        add_weapon(wanted_weapon);

        std::cout << *this << " has picked up " << *wanted_weapon << "." << std::endl << std::endl;
        return target;
    }

    // REQUIRES fighter must be in combat
    // EFFECTS  change health based on amount healed
    void receive_healing(const Weapon* healing_weapon, Fighter* healer) override {
        assert(get_combat_status());
        double multiplier = 1.0;
        Element healer_element = healer->get_element();
        Element weapon_element = healing_weapon->get_element();
        if (weapon_element.is_special_resource(healer_element)) {
            if (weapon_element.is_strengthening(healer_element)) {
                multiplier = multiplier + 0.2;
                std::cout << *healing_weapon << " was more effective because of " << *healer << "'s element!" << std::endl;
                std::cout << *healer << " lost " << 0.1 * max_health << " when healing!" << std::endl;
            }
            else if (!weapon_element.is_strengthening(healer_element)) {
                multiplier = multiplier - 0.2;
                std::cout << *healing_weapon << " was less effective because of " << *healer << "'s element!" << std::endl;
            }
        }
        if (element_type.is_special_resource(weapon_element)) {
            if (element_type.is_strengthening(weapon_element)) {
                multiplier = multiplier + 0.2;
                std::cout << *healing_weapon << " was more effective because of " << *this << "'s element!" << std::endl;
            }
            else if (!element_type.is_strengthening(weapon_element)) {
                multiplier = multiplier - 0.2;
                std::cout << *healing_weapon << " was less effective because of " << *this << "'s element!" << std::endl;
            }
        }

        double healing_strength = healing_weapon->get_healing_strength();
        double total_healing = (healing_strength) * multiplier;
        
        current_health += total_healing;
        if (current_health > max_health) {
            current_health = max_health;
        }

        std::cout << *this << " received " << total_healing << " healing from " << *healer <<
            "." << std::endl << *this << " now has " << current_health << " health." << std::endl << std::endl;
    }

    // REQUIRES fighter is focused by enemy
    // EFFECTS  change health based on attack.
    //do not change combat status if below 0 hp here.
    void receive_attack(const Weapon* damaging_weapon, const Fighter* attacker) override {
        assert(get_combat_status());
        double multiplier = 1.0;
        Element damaging_element = attacker->get_element();
        Element weapon_element = damaging_weapon->get_element();
        if (weapon_element.is_special_strength(damaging_element)) {
            if (weapon_element.is_effective_strength(damaging_element)) {
                multiplier = multiplier + 0.2;
                std::cout << *damaging_weapon << " was more effective because of " << *attacker << "'s element!" << std::endl;
            }
            else if (!weapon_element.is_special_strength(damaging_element)) {
                multiplier = multiplier - 0.2;
                std::cout << *damaging_weapon << " was less effective because of " << *attacker << "'s element!" << std::endl;
            }
        }
        if (element_type.is_special_strength(weapon_element)) {
            if (element_type.is_effective_strength(weapon_element)) {
                multiplier = multiplier + 0.2;
                std::cout << *damaging_weapon << " was more effective because of " << *this << "'s element!" << std::endl;
            }
            else if (!element_type.is_effective_strength(weapon_element)) {
                multiplier = multiplier - 0.2;
                std::cout << *damaging_weapon << " was less effective because of " << *this << "'s element!" << std::endl;
            }
        }

        double healing_strength = damaging_weapon->get_attack_strength();
        double total_damage = (healing_strength)*multiplier;

        current_health -= total_damage;
        if (current_health <= 0) {
            current_health = 0;
        }

        std::cout << *this << " received " << total_damage << " damage from " << *attacker <<
            "." << std::endl << *this << " now has " << current_health << " health." << std::endl << std::endl;
    }

    // EFFECTS: Prints weapons of fighter to os
    std::ostream& print_weapons(std::ostream& os) const override {
        for (int i = 0; i < number_of_weapons; ++i) {
            os << "Weapon " << i + 1 << ": " << *weapons[i] << std::endl;
        }
        return os;
    }

    // EFFECTS Prints dropped_weapons to stream as "Weapon 1: Excalibur" 
    //followed by newline and then "Weapon 2: Gate of Babylon"
    std::ostream& print_list_of_weapons(std::ostream& os, const std::vector<Weapon*> weapons) const override {
        for (size_t i = 0; i < weapons.size(); ++i) {
            Weapon* ithweapon = weapons[i];
            os << "Weapon " << i + 1 << ": " << *ithweapon << std::endl;
        }
        return os;
    }

    // Needed to avoid some compiler errors
    ~Human() {
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
    std::string type;

    // REQUIRES fighter wants to attack
    // EFFECTS see who fighter wants to attack
    int request_attack_target(std::vector<Fighter*> opponents) const {
        std::cout << "These are your opponents: " << std::endl;
        print_list_of_fighters(std::cout, opponents);
        std::cout << std::endl;
        std::cout << name << ", choose who to attack: " << std::endl;
        int target;
        std::cin >> target;
        std::cout << std::endl;
        if (!((size_t)target <= opponents.size() && target > 0)) {
            std::cout << std::endl << "\033[2J" << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return request_attack_target(opponents);
        }
        std::cout << std::endl << "\033[2J" << "\033[1;1H";
        return target - 1;
    }

    // REQUIRES fighter wants to heal
    // EFFECTS see who fighter wants to heal
    int request_heal_target(std::vector<Fighter*> allies) const {
        std::cout << "These are your allies: " << std::endl;
        print_list_of_fighters(std::cout, allies);
        std::cout << std::endl;
        std::cout << name << ", choose who to heal (0 for self)" << std::endl;
        int target;
        std::cin >> target;
        std::cout << std::endl;
        if (!(target <= allies.size() && target > 0)) {
            std::cout << std::endl << "\033[2J" << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return request_heal_target(allies);
        }
        std::cout << std::endl << "\033[2J" << "\033[1;1H";
        return target - 1;
    }

    // REQUIRES fighter wants to heal or attack
    // EFFECTS see which weapon the fighter wants to use
    int request_active_weapon() {
        std::cout << "These are your weapons: " << std::endl;
        print_weapons(std::cout);
        std::cout << std::endl;
        std::cout << name << ", choose which weapon to equip by entering a number (0 for same): " << std::endl;
        int target;
        std::cin >> target;
        std::cout << std::endl;
        if (!(0 <= target && target <= number_of_weapons)) {
            std::cout << std::endl << "\033[2J" << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return request_active_weapon();
        }
        std::cout << std::endl << "\033[2J" << "\033[1;1H";
        if (target == 0) {
            return active_weapon;
        }
        return target - 1;
    }

    // REQUIRES fighter wants to grab and there are dropped weapons
    // EFFECTS see what weapon the fighter wants to grab
    int request_grab_target(const std::vector<Weapon*> dropped_weapons) const {
        std::cout << "These are the dropped weapons: " << std::endl;
        print_list_of_weapons(std::cout, dropped_weapons);
        std::cout << std::endl;
        std::cout << name << ", choose which weapon to equip by entering a number: " << std::endl;
        int target;
        std::cin >> target;
        std::cout << std::endl;
        if (!(0 <= target && target <= dropped_weapons.size())) {
            std::cout << std::endl << "\033[2J" << "\033[1;1H";
            std::cout << "That was not a valid answer! Please try again. " << std::endl;
            return request_grab_target(dropped_weapons);
        }
        std::cout << std::endl << "\033[2J" << "\033[1;1H";
        return target - 1;
    }
};

class Warrior : public Fighter {
public:

    Warrior() : name("Default Name"), element_type(Element::ELE_WATER),
        number_of_weapons(0), active_weapon(0), in_combat(false), max_health(200.0),
        current_health(max_health), attack_strength(25.0),
        healing_strength(25.0), type("Warrior") {}

    Warrior(const std::string& given_name, const Element& element) : Warrior() {
        name = given_name;
        element_type = element;
    }

    Warrior(const std::string& given_name, const Element& element,
        const std::string& weapon_type) : Warrior() {
        name = given_name;
        element_type = element;
        Weapon* default_weapon;
        if (weapon_type == Weapon::WEAPON_STAFF) {
            default_weapon = Weapon_factory(Weapon::WEAPON_STAFF);
        }
        else if (weapon_type == Weapon::WEAPON_SPEAR) {
            default_weapon = Weapon_factory(Weapon::WEAPON_STAFF);
        }
        else if (weapon_type == Weapon::WEAPON_CROSS) {
            default_weapon = Weapon_factory(Weapon::WEAPON_CROSS);
        }
        else {
            assert(false);
        }
        add_weapon(default_weapon);

    }

    Warrior(const std::string& given_name, const Element& given_element,
        std::vector<Weapon*> given_weapons, const int& given_number_of_weapons,
        const int& given_active_weapon, const bool& given_in_combat,
        const double& given_max_health, const double& given_current_health,
        const double& given_attack_strength, const double& given_healing_strength,
        std::string& given_type) : name(given_name), element_type(given_element),
        weapons(given_weapons), number_of_weapons(given_number_of_weapons),
        active_weapon(given_active_weapon), in_combat(given_in_combat),
        max_health(given_max_health), current_health(given_current_health),
        attack_strength(given_attack_strength), healing_strength(given_healing_strength),
        type(given_type) {
    }

    Warrior(const Warrior& other) {
        name = other.get_name();
        element_type = other.get_element();
        number_of_weapons = other.get_number_of_weapons();
        active_weapon = other.get_active_weapon();
        in_combat = other.get_combat_status();
        max_health = other.get_max_health();
        current_health = other.get_current_health();
        attack_strength = other.get_attack_strength();
        healing_strength = other.get_healing_strength();
        type = other.get_type();

        for (int k = 0; number_of_weapons; ++k) {
            Weapon* additional_weapon = Weapon_factory(other.get_k_weapon(k));
            weapons.push_back(additional_weapon);
        }

    }

    Warrior& operator=(const Warrior& rhs) {
        while (number_of_weapons != 0) {
            delete_weapon(0);
        }

        name = rhs.get_name();
        element_type = rhs.get_element();
        number_of_weapons = rhs.get_number_of_weapons();
        active_weapon = rhs.get_active_weapon();
        in_combat = rhs.get_combat_status();
        max_health = rhs.get_max_health();
        current_health = rhs.get_current_health();
        attack_strength = rhs.get_attack_strength();
        healing_strength = rhs.get_healing_strength();
        type = rhs.get_type();

        for (int k = 0; number_of_weapons; ++k) {
            Weapon* additional_weapon = Weapon_factory(rhs.get_k_weapon(k));
            weapons.push_back(additional_weapon);
        }

        return *this;
    }

    // EFFECTS returns fighter's name
    const std::string& get_name() const override {
        return name;
    }

    // EFFECTS returns fighter's type
    const std::string& get_type() const override {
        return type;
    }

    // REQUIRES fighter has an element
    // EFFECTS  returns element of fighter
    Element get_element() const override {
        return element_type;
    }

    // EFFECTS returns number of weapons on fighter
    int get_number_of_weapons() const override {
        return number_of_weapons;
    }

    // REQUIRES fighter has a weapon
    // EFFECTS  returns active weapon of fighter
    int get_active_weapon() const override {
        return active_weapon;
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS returns kth weapons of fighter
    Weapon* get_k_weapon(const int& k) const override {
        assert(get_number_of_weapons() != 0);
        return weapons[k];
    }

    // EFFECTS  returns combat status of fighter
    bool get_combat_status() const override {
        return in_combat;
    }

    // EFFECTS  returns max health of fighter
    double get_max_health() const override {
        return max_health;
    }

    // EFFECTS  returns current health of fighter
    double get_current_health() const override {
        return current_health;
    }

    // EFFECTS  returns attack_strength of fighter
    double get_attack_strength() const override {
        return attack_strength;
    }

    // EFFECTS  returns healing_strength of fighter
    double get_healing_strength() const override {
        return healing_strength;
    }

    // REQUIRES fighter wants to add weapon
    // EFFECTS gives fighter the extra weapon
    void add_weapon(Weapon* weapon) override {
        ++number_of_weapons;
        Weapon* added_weapon = Weapon_factory(weapon);
        weapons.push_back(added_weapon);
        if (active_weapon == -1) {
            active_weapon = 0;
        }
    }

    // REQUIRES fighter wants to delete a weapon
    // EFFECTS deletes weapon
    void delete_weapon(const int& weapon_index) {
        --number_of_weapons;
        delete weapons[weapon_index];
        weapons.erase(weapons.begin() + weapon_index);
        if (active_weapon >= number_of_weapons) {
            active_weapon = number_of_weapons - 1;
        }
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS returns the kth weapon's name
    const std::string& get_k_name(const int& k) const override {
        return weapons[k]->get_name();
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS  returns element of the kth weapon
    Element get_k_element(const int& k) const override {
        return weapons[k]->get_element();
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS  returns attack strength of the kth weapon
    double get_k_attack_strength(const int& k) const override {
        return weapons[k]->get_attack_strength();
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS  returns healing strength of the kth weapon
    double get_k_healing_strength(const int& k) const override {
        return weapons[k]->get_healing_strength();
    }

    // REQUIRES 0 <= k < number_of_weapons
    // EFFECTS returns the kth weapon's type
    const std::string get_k_weapon_type(const int& k) const override {
        return weapons[k]->get_weapon_type();
    }

    // REQUIRES fighter wants to change name
    // EFFECTS changes fighter name
    void change_name(const std::string& name_change) override {
        name = name_change;
    }

    // EFFECTS changes fighter max health
    void change_max_health(const int& health_change) override {
        max_health = health_change;
    }

    // EFFECTS changes fighter current health
    void change_current_health(const int& health_change) override {
        current_health = health_change;
    }

    // EFFECTS changes fighter attack strength
    void change_attack_strength(const int& strength_change) override {
        attack_strength = strength_change;
    }

    // EFFECTS changes fighter healing strength
    void change_healing_strength(const int& healing_change) override {
        healing_strength = healing_change;
    }

    // REQUIRES fighter is currently not in combat
    // EFFECTS make fighter enter combat
    void enter_combat() override {
        assert(!in_combat);
        in_combat = true;
    }

    // REQUIRES fighter is currently in combat
    // EFFECTS make fighter exit combat
    void exit_combat() override {
        assert(in_combat);
        in_combat = false;
    }

    // EFFECTS request action of fighter. should either be attack heal grab or skip.
    std::string request_action(std::vector<Fighter*> allies, std::vector<Fighter*> opponents,
        const std::vector<Weapon*> dropped_weapons) override {
        std::string response = "Attack";
        return response;
    }

    // REQUIRES fighter wants to heal
    // MODIFIES allies
    // EFFECTS  make fighter heal allies or self
    void go_heal(std::vector<Fighter*> allies) override {
        assert(get_combat_status());
        assert(false);
    }

    // REQUIRES fighter wants to fight
    // MODIFIES opponents
    // EFFECTS  make fighter attack opponents. return who was attacked
    int go_attack(std::vector<Fighter*> opponents) override {
        assert(get_combat_status());
        
        int highest_damage_weapon = 0;
        int highest_damage_amount = weapons[0]->get_attack_strength();
        
        for (int i = 0; i < number_of_weapons; ++i) {
            if (weapons[i]->get_attack_strength() > highest_damage_amount) {
                highest_damage_amount = weapons[i]->get_attack_strength();
                highest_damage_weapon = i;
            }
        }

        active_weapon = highest_damage_weapon;

        Element active_weapon_element = weapons[active_weapon]->get_element();

        int target = 0;
        bool worst_target = true;
        for (size_t i = 0; i < opponents.size(); ++i) {
            Fighter* potential_defender = opponents[i];
            Element opponent_element = potential_defender->get_element();

            if (active_weapon_element.is_special_strength(opponent_element)) {
                if (active_weapon_element.is_effective_strength(opponent_element)) {
                    if (worst_target) {
                        worst_target = false;
                    }
                    target = i;
                }
            }
            else {
                if (worst_target) {
                    worst_target = false;
                    target = i;
                }
            }
        }

        Weapon* current_weapon = get_k_weapon(active_weapon);

        std::cout << *this << " used " << *current_weapon << " to attack " << *opponents[target] << std::endl;

        opponents[target]->receive_attack(current_weapon, this);

        return target;
        
    }

    // REQUIRES fighter wants to fight
    // EFFECTS  make fighter grab weapon
    int go_grab_weapon(std::vector<Fighter*> allies, std::vector<Fighter*> opponents,
        const std::vector<Weapon*> dropped_weapons) override {
        assert(get_combat_status());
        assert(false);
    }

    // REQUIRES fighter must be in combat
    // EFFECTS  change health based on amount healed
    void receive_healing(const Weapon* healing_weapon, Fighter* healer) override {
        assert(get_combat_status());
        double multiplier = 1.0;
        Element healer_element = healer->get_element();
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
        double total_healing = (healing_strength)*multiplier;

        current_health += total_healing;
        if (current_health > max_health) {
            current_health = max_health;
        }
        std::cout << *this << " received " << total_healing << " healing from " << *healer <<
            "." << std::endl << *this << " now has " << current_health << " health." << std::endl << std::endl;
    }

    // REQUIRES fighter is focused by enemy
    // EFFECTS  change health based on attack.
    //do not change combat status if below 0 hp here.
    void receive_attack(const Weapon* damaging_weapon, const Fighter* attacker) override {
        assert(get_combat_status());
        double multiplier = 1.0;
        Element damaging_element = attacker->get_element();
        Element weapon_element = damaging_weapon->get_element();
        if (weapon_element.is_special_strength(damaging_element)) {
            if (weapon_element.is_effective_strength(damaging_element)) {
                multiplier = multiplier + 0.2;
                std::cout << *damaging_weapon << " was more effective because of " << *attacker << "'s element!" << std::endl;
            }
            else if (!weapon_element.is_special_strength(damaging_element)) {
                multiplier = multiplier - 0.2;
                std::cout << *damaging_weapon << " was less effective because of " << *attacker << "'s element!" << std::endl;
            }
        }
        if (element_type.is_special_strength(weapon_element)) {
            if (element_type.is_effective_strength(weapon_element)) {
                multiplier = multiplier + 0.2;
                std::cout << *damaging_weapon << " was more effective because of " << *this << "'s element!" << std::endl;
            }
            else if (!element_type.is_effective_strength(weapon_element)) {
                multiplier = multiplier - 0.2;
                std::cout << *damaging_weapon << " was less effective because of " << *this << "'s element!" << std::endl;
            }
        }

        double healing_strength = damaging_weapon->get_attack_strength();
        double total_damage = (healing_strength)*multiplier;

        current_health -= total_damage;
        if (current_health <= 0) {
            current_health = 0;
        }
        std::cout << *this << " received " << total_damage << " damage from " << *attacker <<
            "." << std::endl << *this << " now has " << current_health << " health." << std::endl << std::endl;
    }

    // EFFECTS: Prints weapons of fighter to os
    std::ostream& print_weapons(std::ostream& os) const override {
        for (int i = 0; i < number_of_weapons; ++i) {
            os << "Weapon " << i + 1 << ": " << *weapons[i] << std::endl;
        }
        return os;
    }

    // EFFECTS Prints dropped_weapons to stream as "Weapon 1: Excalibur" 
    //followed by newline and then "Weapon 2: Gate of Babylon"
    std::ostream& print_list_of_weapons(std::ostream& os, const std::vector<Weapon*> weapons) const override {
        for (size_t i = 0; i < weapons.size(); ++i) {
            Weapon* ithweapon = weapons[i];
            os << "Weapon " << i + 1 << ": " << *ithweapon << std::endl;
        }
        return os;
    }

    // Needed to avoid some compiler errors
    ~Warrior() {
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
    std::string type;
};

// EFFECTS Returns a pointer to a fighter with the given name, element, and type
Fighter* Fighter_factory(const std::string& name, const Element& element,
    const std::string& type) {
    if (type == "Human") {
        return new Human(name, element);
    }
    else if (type == "Warrior") {
        return new Warrior(name, element);
    }
    assert(false);
    return nullptr;
}

// EFFECTS: Returns a pointer to a fighter with the given name, element, weapon, and type
Fighter* Fighter_factory(const std::string& name, const Element& element,
    const std::string& weapon, const std::string& type) {
    if (type == "Human") {
        return new Human(name, element, weapon);
    }
    else if (type == "Warrior") {
        return new Warrior(name, element, weapon);
    }
    assert(false);
    return nullptr;
}

// EFFECTS Returns a pointer to a fighter that is copy of copied_fighter
Fighter* Fighter_factory(const Fighter* copied_fighter) {

    std::string name = copied_fighter->get_name();
    Element element = copied_fighter->get_element();

    int number_of_weapons = copied_fighter->get_number_of_weapons();

    std::vector<Weapon*> weapons;
    for (int i = 0; i < number_of_weapons; ++i) {
        Weapon* ith_weapon = copied_fighter->get_k_weapon(i);
        Weapon* added_weapon = Weapon_factory(ith_weapon);
        weapons.push_back(added_weapon);
    }

    int active_weapon = copied_fighter->get_active_weapon();
    bool in_combat = copied_fighter->get_combat_status();
    double max_health = copied_fighter->get_max_health();
    double current_health = copied_fighter->get_current_health();

    double attack_strength = copied_fighter->get_attack_strength();
    double healing_strength = copied_fighter->get_healing_strength();
    std::string type = copied_fighter->get_type();

    if (type == "Human") {
        return new Human(name, element, weapons, number_of_weapons, active_weapon, 
            in_combat, max_health, current_health, attack_strength, healing_strength, type);
    }
    else if (type == "Warrior") {
        return new Warrior(name, element, weapons, number_of_weapons, active_weapon,
            in_combat, max_health, current_health, attack_strength, healing_strength, type);
    }
    assert(false);
    return nullptr;
}

// EFFECTS: Prints fighter's name to os
std::ostream& operator<<(std::ostream& os, const Fighter& f) {
    os << f.get_name();
    return os;
}

// EFFECTS: Prints weapons of fighter to os
std::ostream& print_weapons(std::ostream& os, const Fighter& f) {
    f.print_weapons(os);
    return os;
}

// EFFECTS Prints fighters to stream as "Fighter 1: Alex" 
//followed by newline and then "Fighter 2: Harry"
std::ostream& print_list_of_fighters(std::ostream& os, std::vector<Fighter*> fighters) {
    for (size_t i = 0; i < fighters.size(); ++i) {
        Fighter* ithfighter = fighters[i];
        os << "Fighter " << i + 1 << ": " << *ithfighter << std::endl;
    }
    return os;
}
