#ifndef WEAPON_H
#define WEAPON_H
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

class Weapon {
public:
    //EFFECTS returns weapon's name
    virtual const std::string& get_name() const = 0;

    //REQUIRES weapon has an element
    //EFFECTS  returns element of weapon
    virtual Element get_element() const = 0;

    //REQUIRES weapon has an attack strength
    //EFFECTS  returns attack strength of weapon
    virtual double get_attack_strength() const = 0;

    //REQUIRES weapon has a healing strength
    //EFFECTS  returns healing strength of weapon
    virtual double get_healing_strength() const = 0;

    //REQUIRES weapon has a name
    //EFFECTS  changes name of weapon
    virtual void change_name() = 0;

    //REQUIRES weapon has an attack strength
    //EFFECTS  changes attack strength of weapon
    virtual void change_attack_strength() = 0;

    //REQUIRES weapon has a healing strength
    //EFFECTS  changes healing strength of weapon
    virtual void change_healing_strength() = 0;

    // Needed to avoid some compiler errors
    virtual ~Weapon() {}

private:
    std::string name;
    Element element;
    double attack_strength;
    double healing_strength;
};

//EFFECTS Returns a pointer to a weapon with the given name
Weapon* Weapon_factory(const std::string& name, const Element& element);

//EFFECTS Prints weapon's name to os
std::ostream& operator<<(std::ostream& os, const Weapon& w);

//EFFECTS Prints weapon to os
std::ostream& print_weapons(std::ostream& os, const Weapon& w);

#endif

