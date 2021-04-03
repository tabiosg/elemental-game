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
        weapon_type(WEAPON_STAFF) {}

    Staff(const std::string& given_name, const Element& given_element) : Staff() {
        name = given_name;
        element = given_element;
    }

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
        return WEAPON_STAFF;
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

    Spear(const std::string& given_name, const Element& given_element) : Spear() {
        name = given_name;
        element = given_element;
    }

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

    Cross(const std::string& given_name, const Element& given_element) : Cross() {
        name = given_name;
        element = given_element;
    }

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

//EFFECTS Returns a pointer to a weapon with the given name, element, and type
Weapon* Weapon_factory(const std::string& name, const Element& element,
    const std::string& weapon_type) {

    if (weapon_type == Weapon::WEAPON_STAFF) {
        return new Staff(name, element);
    }
    else if (weapon_type == Weapon::WEAPON_SPEAR) {
        return new Spear(name, element);
    }
    else if (weapon_type == Weapon::WEAPON_CROSS) {
        return new Cross(name, element);
    }
    assert(false);
    return nullptr;
}

//EFFECTS Returns a pointer to a weapon with the given weapon_type
Weapon* Weapon_factory(const std::string& weapon_type) {
    if (weapon_type == Weapon::WEAPON_STAFF) {
        return new Staff();
    }
    else if (weapon_type == Weapon::WEAPON_SPEAR) {
        return new Spear();
    }
    else if (weapon_type == Weapon::WEAPON_CROSS) {
        return new Cross();
    }
    assert(false);
    return nullptr;
}

//EFFECTS Returns a pointer to a weapon that is copy of copied_weapon
Weapon* Weapon_factory(const Weapon* copied_weapon) {

    std::string name = copied_weapon->get_name();
    Element& element = copied_weapon->get_element();
    double attack_strength = copied_weapon->get_attack_strength();
    double healing_strength = copied_weapon->get_healing_strength();
    std::string weapon_type = copied_weapon->get_weapon_type();

    if (weapon_type == Weapon::WEAPON_STAFF) {
        return new Staff(name, element, attack_strength, healing_strength);
    }
    else if (weapon_type == Weapon::WEAPON_SPEAR) {
        return new Spear(name, element, attack_strength, healing_strength);
    }
    else if (weapon_type == Weapon::WEAPON_CROSS) {
        return new Cross(name, element, attack_strength, healing_strength);
    }
    assert(false);
    return nullptr;
}

//EFFECTS Prints weapon's name to os
std::ostream& operator<<(std::ostream& os, const Weapon& w) {
    os << w.get_name() << "(Type: " << w.get_weapon_type() << ")";
    return os;
}