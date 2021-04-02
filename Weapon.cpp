/* Weapon.h
 *
 * Weapons
 *
 * by Guthrie Tabios
 * tabiosg
 * 2021-04-01
 */

#include "Element.h"
#include "Weapon.h"
#include <string>
#include <vector>
#include <cassert>

class Staff : public Weapon {
public:

    Staff() : name("Default Name"), element(Element::ELE_WATER),
        attack_strength(40.0), healing_strength(20.0),
        weapon_type("Staff") {}

    Staff(const std::string& given_name, const Element& given_element,
        const double& given_attack_strength, 
        const double& given_healing_strength) : Staff() {
        name = given_name;
        element = given_element;
        attack_strength = given_attack_strength;
        healing_strength = given_healing_strength;
    }

    //EFFECTS returns weapon's name
    const std::string& get_name() const override {
        return name;
    }

    //REQUIRES weapon has an element
    //EFFECTS  returns element of weapon
    Element get_element() const override {
        return element;
    }

    //REQUIRES weapon has an attack strength
    //EFFECTS  returns attack strength of weapon
    double get_attack_strength() const override {
        return attack_strength;
    }

    //REQUIRES weapon has a healing strength
    //EFFECTS  returns healing strength of weapon
    double get_healing_strength() const override {
        return healing_strength;
    }

    //EFFECTS returns weapon's type
    const std::string& get_weapon_type() const override {
        return "Staff";
    }

    //REQUIRES weapon has a name
    //EFFECTS  changes name of weapon
    void change_name(const std::string& name_change) override {
        name = name_change;
    }

    //REQUIRES weapon has an attack strength
    //EFFECTS  changes attack strength of weapon
    void change_attack_strength(const int& changed_attack_strength) override {
        attack_strength = changed_attack_strength;
    }

    //REQUIRES weapon has a healing strength
    //EFFECTS  changes healing strength of weapon
    void change_healing_strength(const int& changed_heal_strength) override {
        healing_strength = healing_strength;
    }

    // Needed to avoid some compiler errors
    ~Staff() {
    }

private:
    std::string name;
    Element element;
    double attack_strength;
    double healing_strength;
    std::string weapon_type;
};

class Spear : public Weapon {
public:

    Spear() : name("Default Name"), element(Element::ELE_WATER),
        attack_strength(50.0), healing_strength(10.0),
        weapon_type("Spear") {}

    Spear(const std::string& given_name, const Element& given_element,
        const double& given_attack_strength,
        const double& given_healing_strength) : Spear() {
        name = given_name;
        element = given_element;
        attack_strength = given_attack_strength;
        healing_strength = given_healing_strength;
    }

    //EFFECTS returns weapon's name
    const std::string& get_name() const override {
        return name;
    }

    //REQUIRES weapon has an element
    //EFFECTS  returns element of weapon
    Element get_element() const override {
        return element;
    }

    //REQUIRES weapon has an attack strength
    //EFFECTS  returns attack strength of weapon
    double get_attack_strength() const override {
        return attack_strength;
    }

    //REQUIRES weapon has a healing strength
    //EFFECTS  returns healing strength of weapon
    double get_healing_strength() const override {
        return healing_strength;
    }

    //EFFECTS returns weapon's type
    const std::string& get_weapon_type() const override {
        return "Spear";
    }

    //REQUIRES weapon has a name
    //EFFECTS  changes name of weapon
    void change_name(const std::string& name_change) override {
        name = name_change;
    }

    //REQUIRES weapon has an attack strength
    //EFFECTS  changes attack strength of weapon
    void change_attack_strength(const int& changed_attack_strength) override {
        attack_strength = changed_attack_strength;
    }

    //REQUIRES weapon has a healing strength
    //EFFECTS  changes healing strength of weapon
    void change_healing_strength(const int& changed_heal_strength) override {
        healing_strength = healing_strength;
    }

    // Needed to avoid some compiler errors
    ~Spear() {
    }

private:
    std::string name;
    Element element;
    double attack_strength;
    double healing_strength;
    std::string weapon_type;
};

class Cross : public Weapon {
public:

    Cross() : name("Default Name"), element(Element::ELE_WATER),
        attack_strength(30.0), healing_strength(50.0),
        weapon_type("Cross") {}

    Cross(const std::string& given_name, const Element& given_element,
        const double& given_attack_strength,
        const double& given_healing_strength) : Cross() {
        name = given_name;
        element = given_element;
        attack_strength = given_attack_strength;
        healing_strength = given_healing_strength;
    }

    //EFFECTS returns weapon's name
    const std::string& get_name() const override {
        return name;
    }

    //REQUIRES weapon has an element
    //EFFECTS  returns element of weapon
    Element get_element() const override {
        return element;
    }

    //REQUIRES weapon has an attack strength
    //EFFECTS  returns attack strength of weapon
    double get_attack_strength() const override {
        return attack_strength;
    }

    //REQUIRES weapon has a healing strength
    //EFFECTS  returns healing strength of weapon
    double get_healing_strength() const override {
        return healing_strength;
    }

    //EFFECTS returns weapon's type
    const std::string& get_weapon_type() const override {
        return "Cross";
    }

    //REQUIRES weapon has a name
    //EFFECTS  changes name of weapon
    void change_name(const std::string& name_change) override {
        name = name_change;
    }

    //REQUIRES weapon has an attack strength
    //EFFECTS  changes attack strength of weapon
    void change_attack_strength(const int& changed_attack_strength) override {
        attack_strength = changed_attack_strength;
    }

    //REQUIRES weapon has a healing strength
    //EFFECTS  changes healing strength of weapon
    void change_healing_strength(const int& changed_heal_strength) override {
        healing_strength = healing_strength;
    }

    // Needed to avoid some compiler errors
    ~Cross() {
    }

private:
    std::string name;
    Element element;
    double attack_strength;
    double healing_strength;
    std::string weapon_type;
};

//EFFECTS Returns a pointer to a weapon with the given weapon type
Weapon* Weapon_factory(const std::string& name, const Element& element,
    const double& attack_strength, const double& healing_strength,
    const std::string& weapon_type) {
    if (weapon_type == "Staff") {
        return new Staff(name, element, attack_strength, healing_strength);
    }
    else if (weapon_type == "Spear") {
        return new Spear(name, element, attack_strength, healing_strength);
    }
    else if (weapon_type == "Cross") {
        return new Cross(name, element, attack_strength, healing_strength);
    }
    assert(false);
    return nullptr;
}

//EFFECTS Prints weapon's name to os
std::ostream& operator<<(std::ostream& os, const Weapon& w) {
    os << w.get_name();
    return os;
}

//EFFECTS Prints weapon to os
std::ostream& print_weapons(std::ostream& os, const Weapon& w) {
    os << w.get_weapon_type();
    return os;
}