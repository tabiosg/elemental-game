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
#include <string>
#include <vector>

class Weapon
{
public:
    // weapon names
    static constexpr const char *const STAFF = "Staff";
    static constexpr const char *const SPEAR = "Spear";
    static constexpr const char *const CROSS = "Cross";
    // list
    static constexpr const char *const WEAPON_LIST[] = {
        Weapon::STAFF,
        Weapon::SPEAR,
        Weapon::CROSS};
    static constexpr const int NUM_weaponTypeS = 3;

    Weapon();

    Weapon(
        const std::string &givenName,
        const Element &givenElement,
        const double &givenAttackStrength,
        const double &givenHealingStrength);

    Weapon(
        const std::string &givenName,
        const Element &givenElement);

    // EFFECTS returns weapon's name
    virtual const std::string &getName() const;

    // REQUIRES weapon has an element
    // EFFECTS  returns element of weapon
    virtual Element getElement() const;

    // REQUIRES weapon has an attack strength
    // EFFECTS  returns attack strength of weapon
    virtual double getAttackStrength() const;

    // REQUIRES weapon has a healing strength
    // EFFECTS  returns healing strength of weapon
    virtual double getHealingStrength() const;

    // EFFECTS returns weapon's type
    virtual const std::string getWeaponType() const;

    // REQUIRES weapon has a name
    // EFFECTS  changes name of weapon
    virtual void changeName(const std::string &newName);

    // REQUIRES weapon has an attack strength
    // EFFECTS  changes attack strength of weapon
    virtual void changeAttackStrength(
        const int &changedAttackStrength);

    // REQUIRES weapon has a healing strength
    // EFFECTS  changes healing strength of weapon
    virtual void changeHealingStrength(
        const int &changedHealStrength);

    // Needed to avoid some compiler errors
    virtual ~Weapon();

private:
    std::string name;
    Element element;
    double attackStrength;
    double healingStrength;
    std::string weaponType;
};

// EFFECTS Returns a pointer to a weapon with the given name, element, and type
Weapon *WeaponFactory(
    const std::string &name,
    const Element &element,
    const std::string &weaponType);

// EFFECTS Returns a pointer to a weapon with the given weaponType
Weapon *WeaponFactory(const std::string &weaponType);

// EFFECTS Returns a pointer to a weapon that is copy of copiedWeapon
Weapon *WeaponFactory(const Weapon *copiedWeapon);

// EFFECTS Prints weapon's name to os
std::ostream &operator<<(std::ostream &os, const Weapon &w);

#endif
